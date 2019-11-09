#include "kmp_search.h"

void pthread_search::prefix_function() {
    size_t n = pattern.size();
    prefix.resize(n);

    // в i-м элементе (его индекс i-1) количество совпавших символов в начале и конце для подстроки длины i.
    // p[0]=0 всегда, p[1]=1, если начинается с двух одинаковых
    for (size_t i = 1; i < n; i++) {
        // ищем, какой префикс-суффикс можно расширить
        size_t j = prefix[i-1]; // длина предыдущего префикса-суффикса, возможно нулевая
        while ((j > 0) && (pattern[i] != pattern[j])) // этот нельзя расширить,
            j = prefix[j-1];   // берем длину меньшего префикса-суффикса

        if (pattern[i] == pattern[j]) {
            ++j;  // расширяем найденный (возможно пустой) префикс-суффикс
        }
        prefix[i] = j;
    }
}

/*
Рассмотрим теперь алгоритм, который строит атомат с исключениями, распознающий Σ ∗ SΣ ∗ .
1. В автомате n + 1 состояние, пронумерованные от 0 до n;
2. Начальным состоянием является 0, а принимающим – n;
3. Изначально есть переходы из k в k + 1 по s k+1 ;
4. Из состояния n все переходы определены и ведут в него же;
5. Из любого состояния k при k > 1 определена ссылка-исключение, ведущая в π(k).
*/
void pthread_search::kmp_make() { // N -количество букв в алфавите
    // Двумерный массив m на n, где - m - мощность алфавита, n - длина шаблона + 1
    prefix_function();
    kmp_state.resize(128, vector<size_t>(pattern.size() + 1));
    int i, j;

    /*cout << "Prefix function is ";
    for (i = 0; i < prefix.size(); i++)
        cout << prefix[i] << " ";
    cout << endl << endl;*/

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
    DIR *dir = opendir(current_path.c_str()); // opendir видит все дириктории, к которым есть доступ
    if (dir == NULL) {
        return 0;
    }
    string new_path;
    for (auto rd = readdir(dir); rd != NULL; rd = readdir(dir)) {
        switch (rd->d_type) {
            case DT_REG: // file
                cout << "File:" << rd->d_name << endl;
                new_path = current_path + "/" + rd->d_name;
                file_paths.push_back(new_path);
                file_names.emplace_back(rd->d_name);
                break;
            case DT_DIR: // directory
                cout << "Directory:" << rd->d_name << endl;
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
            cout << "File:" << rd->d_name << endl;
            string new_path = path + "/" + rd->d_name;
            file_paths.push_back(new_path);
            file_names.emplace_back(rd->d_name);
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
    cout << "Queue:" << endl;
    for (int i = 0; i < file_paths.size(); i++) {
        cout << file_paths[i] << endl;
    }
}

bool pthread_search::row_check(const string& row) {
    size_t current_state = 0;

    for (int i = 0; i < row.size(); i++) {
        current_state = kmp_state[row[i]][current_state];
        if (current_state == pattern.size()) {
            return true;
        }
    }
    return false;
}

void pthread_search::search(){//pthread_search *searcher) {
    //searcher.mut.lock();       /* блокировка общей очереди */
    /*string current_path = searcher.get_path();
    if (!searcher.queue_position_inc()) {
        return;
    }
    searcher.mut.unlock(); */    /* разблокирование общей очереди */

    /*ifstream input(current_path);
    if (input) {
        string line;
        int i = 0;
        while (getline(input, line)) {
            if (searcher.row_check(line)) {
                cout << searcher.get_file_name() << " " << i << " " << line << endl;
                break;
            }
        }
        input.close();
    }*/
}
int pthread_search::manage_threads(int argc, char **argv) {
     /*pthread_search searcher;

     // Разбор запроса из командной строки
     searcher.parcer(argc, argv);

     // Создание кмп автомата
     searcher.kmp_make();

     // Создание очереди файлов
     if (searcher->get_current_directory_flag()) {
         searcher->make_queue_for_current_directory();
     } else {
        searcher->make_queue(searcher->get_path());
     }

     searcher.print();*/

     //threads.resize(num_of_threads);
     thread thr(thread(pthread_search::search));
     /*for (int i = 0; i < num_of_threads; i++) { // создание нитей в цикле
         threads.emplace_back(thread(pthread_search::search));//, searcher)); // У этой функции не должно быть скрытых полей
     }*/
     /*for (int i = 0; i < num_of_threads; i++) {
         threads[i].join();
     }*/
     return 0;
}
/*int manage_threads(int argc, char **argv) {
    pthread_search *searcher;

    // Разбор запроса из командной строки
    searcher->parcer(argc, argv);

    // Создание кмп автомата
    searcher->kmp_make();

    // Создание очереди файлов
    if (searcher->get_current_directory_flag()) {
        searcher->make_queue_for_current_directory();
    } else {
        searcher->make_queue(searcher->get_path());
    }

    searcher->print();

    vector<thread> threads;

    size_t num_of_threads = searcher->get_num_of_threads();
    for (int i = 0; i < num_of_threads; i++) { *//* создание нитей в цикле */
/*   threads.push_back(thread(search, searcher));
}
for (int i = 0; i < num_of_threads; i++) {
   threads[i].join();
}

return 0;
}*/
