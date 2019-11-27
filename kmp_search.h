#ifndef INC_2_TASK_KMP_SEARCH_H
#define INC_2_TASK_KMP_SEARCH_H

#include <vector>
#include <string>
#include <iostream>

#include <cstdio>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <cstring>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

class pthread_search {
private:
    // Парсер и создание очереди
    string path = ".", pattern;
    size_t current_directory_flag = 0;
    vector<string> file_paths;
    vector<string> file_names;
    bool parcer(int argc, char **argv);
    int make_queue(const string& current_path);
    int make_queue_for_current_directory();

    // КМП автомат
    vector<size_t> prefix;
    vector<vector<size_t>> kmp_state;
    void prefix_function();
    void kmp_make();
    bool row_check(const string& row);

    // Многопоточный поиск
    size_t num_of_threads = 1; // Количество потоков
    mutex mut; // Блокировка доступа к общей очереди
    vector<thread> threads;
    size_t queue_position = 0; // Позиция в очереди файлов
    void search();

    // Проверка того напечаталось ли что-нибудь на экран
    bool empty_ouput = true;

    // Функция печати для дебагинга
    void print();
public:
    int manage_threads(int argc, char **argv);
};

#endif //INC_2_TASK_KMP_SEARCH_H
