#include "kmp_search.h"

void pthread_search::prefix_function() {
    size_t n = pattern.size();
    prefix.resize(n);

    // в i-м элементе (его индекс i-1) количество совпавших символов в начале и конце для подстроки длины i.
    // prefix[0] = 0 всегда, prefix[1] = 1, если начинается с двух одинаковых
    for (size_t i = 1; i < n; i++) {
        // ищем, какой префикс-суффикс можно расширить
        size_t j = prefix[i - 1]; // длина предыдущего префикса-суффикса, возможно нулевая
        while ((j > 0) && (pattern[i] != pattern[j])) // этот нельзя расширить,
            j = prefix[j - 1];   // берем длину меньшего префикса-суффикса

        if (pattern[i] == pattern[j]) {
            ++j;  // расширяем найденный (возможно пустой) префикс-суффикс
        }
        prefix[i] = j;
    }
}

/*
Функция, которая строит атомат с исключениями, распознающий Σ^∗SΣ^∗.
1. В автомате n + 1 состояние, пронумерованные от 0 до n;
2. Начальным состоянием является 0, а принимающим – n;
3. Изначально есть переходы из k в k + 1 по s_{k+1};
4. Из состояния n все переходы определены и ведут в него же;
5. Из любого состояния k при k > 1 определена ссылка-исключение, ведущая в π(k).
*/
void pthread_search::kmp_make() {
    // Двумерный массив m на n, где - m - мощность алфавита, n - длина шаблона + 1
    prefix_function();
    kmp_state.resize(128, vector<size_t>(pattern.size() + 1));
    int i, j;

    //Из любого состояния k при k > 1 определена ссылка-исключение, ведущая в π(k).
    kmp_state[pattern[0]][0] = 1;
    for (i = 0; i < 128; i++) {
        for (j = 1; j < pattern.size(); j++) {
            if (i == pattern[j]) {
                kmp_state[i][j] = j + 1;
            } else {
                kmp_state[i][j] = kmp_state[i][prefix[j]];
            }
        }
        kmp_state[i][j] = pattern.size();
    }
}

int pthread_search::parcer(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        switch(argv[i][0]) {
            case '-':
                if (argv[i][1] == 't') {
                    string thread_flag = argv[i] + 2; // Нужно передвинуть указатель, чтобы не было ошибок в stoi
                    num_of_threads = stoi(thread_flag);
                } else {
                    current_directory_flag = 1;
                }
                break;
            case '/':
                path = argv[i];
                break;
            case '.':
                break;
            default :
                pattern = argv[i];
                break;
        }
    }
}

int pthread_search::make_queue(const string& current_path) {
    DIR *dir = opendir(current_path.c_str());
    if (dir == NULL) {
        return 0;
    }
    string new_path;
    for (auto rd = readdir(dir); rd != NULL; rd = readdir(dir)) {
        switch (rd->d_type) {
            case DT_REG: // file
                //cout << "File:" << rd->d_name << endl;
                file_names.emplace_back(string(rd->d_name));
                new_path = current_path + "/" + rd->d_name;
                file_paths.push_back(new_path);
                break;
            case DT_DIR: // directory
                //cout << "Directory:" << rd->d_name << endl;
                if ((strcmp(rd->d_name, ".") != 0) && (strcmp(rd->d_name, "..") != 0)) {
                    new_path = current_path + "/" + rd->d_name;
                    make_queue(new_path);
                }
                break;
            default :
                break;
        }
    }
    closedir(dir);
    return 0;
}
int pthread_search::make_queue_for_current_directory() {
    DIR *dir = opendir(path.c_str());
    if (dir == NULL) {
        return 0;
    }
    for (auto rd = readdir(dir); rd != NULL; rd = readdir(dir)) {
        if (rd->d_type == DT_REG) {
            //cout << "File:" << rd->d_name << endl;
            file_names.emplace_back(string(rd->d_name));
            string new_path = path + "/" + rd->d_name;
            file_paths.push_back(new_path);
        }
    }
    closedir(dir);
    return 0;
}
void pthread_search::print() {
    cout << "Path:" << path << endl;
    cout << "Pattern:" << pattern << endl;
    cout << "Num of threads:" << num_of_threads << endl;
    cout << "Current directory:" << current_directory_flag << endl << endl;
    cout << "File names size: " << file_names.size() << endl;
    cout << "File paths size: " << file_paths.size() << endl;
    cout << "Queue:" << endl;
    for (int i = 0; i < file_paths.size(); i++) {
        cout << file_paths[i] << "--> " << file_names[i] << endl;
    }
}

bool pthread_search::row_check(const string& row) {
    size_t current_state = 0;

    for (int i = 0; i < row.size(); i++) {
        if ((row[i] < 128) && (row[i] > -1)) {
            current_state = kmp_state[row[i]][current_state];
        } else {
            current_state = 0;
        }
        if (current_state == pattern.size()) {
            return true;
        }
    }
    return false;
}

void pthread_search::search() {
    while (true) {
        mut.lock();       /* блокировка общей очереди */
        string current_path = file_paths[queue_position];
        size_t current_queue_position = queue_position;

        if (queue_position < file_names.size()) {
            queue_position++;
        } else {
            mut.unlock();  /* разблокирование общей очереди */
            return;
        }
        mut.unlock();  /* разблокирование общей очереди */
        ifstream input(current_path);
        if (input) {
            string line;
            int i = 0;
            while (getline(input, line)) {
                if (row_check(line)) {
                    cout << file_names[current_queue_position] << " " << i << " " << line << endl;
                }
                i++;
            }
            input.close();
        }
    }
}
int pthread_search::manage_threads(int argc, char **argv) {
    // Разбор запроса из командной строки
    parcer(argc, argv);

    // Создание КМП-автомата с исключениями
    kmp_make();

    // Создание очереди файлов
    if (current_directory_flag) {
        make_queue_for_current_directory();
    } else {
        make_queue(path);
    }

    //print();

    for (int i = 0; i < num_of_threads; i++) { // создание потоков в цикле
        threads.emplace_back(thread(&pthread_search::search, this));
    }
    for (int i = 0; i < num_of_threads; i++) {
        threads[i].join();
    }
    search();
    return 0;
}