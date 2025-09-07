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

    queue_init(&out_q);
    queue_init(&in_q);


    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE_NP);

    pthread_mutex_init(&out_q.q_mutex, &attr);

    pthread_mutex_init(&in_q.q_mutex,&attr);

    pthread_mutex_init(&print_mtx,&attr);


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
