#include "../defs.h"

void failedThread(char *type, char *name){
    pthread_mutex_lock(&print_mtx); 
    printf("Exiting... failed to %s %s thread", type, name);
    pthread_mutex_unlock(&print_mtx); 
}

void printMsg(const char *fmt, ...) {
    va_list args;
    pthread_mutex_lock(&print_mtx);
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    pthread_mutex_unlock(&print_mtx);
}
