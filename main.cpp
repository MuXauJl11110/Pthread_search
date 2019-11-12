#include "kmp_search.h"

int main(int argc, char **argv) {
    pthread_search searcher;

    searcher.manage_threads(argc, argv);

    return 0;
}