#include "defs.h"

Queue in_q;
Queue out_q;
int neighbors[R_SIZE];
int routerId = -1;
char ip[IP_SIZE];
int port = 0;
pthread_mutex_t print_mtx;
pthread_t thread_receiver, thread_sender, thread_handler, thread_controller;
Router routers[R_SIZE];

int main(int argc, char const *argv[])
{

    sem_init(&out_q.size,0 ,0);
    sem_init(&in_q.size,0 ,0);

    pthread_mutex_init(&out_q.q_mutex, NULL);
    pthread_mutexattr_settype(&out_q.q_mutex, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&in_q.q_mutex, NULL);
    pthread_mutexattr_settype(&in_q.q_mutex, PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&print_mtx, NULL);
    pthread_mutexattr_settype(&print_mtx, PTHREAD_MUTEX_RECURSIVE);

    if (argc != 2)
    {
        printMsg("Exiting... expected use << router [routerId] >> | 1 <= routerID <= 10\n");
        return 1;
    }
    else if ((routerId = atoi(argv[1])) < 1)
    {

        printMsg("Exiting... invalid routerId expected value: 1 <= routerID <= 10\n");
        return 1;
    }

    if (getConfigs() == 1)
        return 1;

    if (pthread_create(&thread_receiver, NULL, &receiver, NULL) != 0)
    {
        failedThread("create", "RECEIVER");
        return -1;
    }

    sleep(1);
    if (pthread_create(&thread_sender, NULL, &sender, NULL) != 0)
    {
        failedThread("create", "SENDER");
        return -1;
    }

    sleep(1);
    if (pthread_create(&thread_controller, NULL, &controller, NULL) != 0)
    {
        failedThread("create", "CONTROLLER");
        return -1;
    }

    if (pthread_join(thread_receiver, NULL) != 0)
    {
        failedThread("join", "RECEIVER");
        return -1;
    }
    if (pthread_join(thread_sender, NULL) != 0)
    {
        failedThread("join", "SENDER");
        return -1;
    }
    if (pthread_join(thread_handler, NULL) != 0)
    {
        failedThread("join", "HANDLER");
        return -1;
    }
    if (pthread_join(thread_controller, NULL) != 0)
    {
        failedThread("join", "CONTROLLER");
        return -1;
    }

    return 0;
}
