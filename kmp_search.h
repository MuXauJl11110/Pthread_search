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
    string path = ".", pattern;
    size_t num_of_threads = 1, current_directory_flag = 0;
    vector<string> file_paths;
    vector<string> file_names;
    size_t queue_position = 0;
    vector<thread> threads;

    // КМП автомат
    vector<size_t> prefix;
    vector<vector<size_t>> kmp_state;
public:
    // КМП автомат
    void prefix_function();
    void kmp_make();
    bool row_check(const string& row);

    int parcer(int argc, char **argv);
    int make_queue(const string& current_path);
    int make_queue_for_current_directory();
    void print();

    /*string get_path() {
        return path;
    }
    string get_pattern() {
        return pattern;
    }
    size_t get_num_of_threads() {
        return num_of_threads;
    }
    size_t get_current_directory_flag () {
        return current_directory_flag;
    }
    string get_row() {
        return file_paths[queue_position];
    }
    bool queue_position_inc() {
        if (queue_position < file_paths.size() - 1) {
            queue_position++;
            return true;
        } else {
            return false;
        }
    }
    string get_file_name() {
        return file_names[queue_position - 1];
    }*/
    int manage_threads(int argc, char **argv);
    static void search();
    mutex mut; // Блокировка доступа к общей очереди
};

//int manage_threads(int argc, char **argv);

#endif //INC_2_TASK_KMP_SEARCH_H
