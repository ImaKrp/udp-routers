
#include "../defs.h"

void die_s(char *s)
{
    perror(s);
    exit(1);
}

int sendPackage_(Package package)
{
    struct sockaddr_in si_other;
    int s, i, slen = sizeof(si_other);
    char buf[B_LENGTH];

    Router sendToRouter = routers[package.receiver - 1];

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die_s("socket");
    }

    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(sendToRouter.port);

    if (inet_aton(sendToRouter.ip, &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    if (sendto(s, &package, sizeof(package), 0, (struct sockaddr *)&si_other, slen) == -1)
    {
        die_s("sendto()");
    }

    close(s);
    return 0;
}

void *sender(void *arg)
{
    int value;

    sem_getvalue(&out_q.size, &value);
     printMsg("%d", value);
    sem_wait(&out_q.size);
    while (1)
    {
        sem_wait(&out_q.size);
        sem_wait(&out_q.size);
        sem_wait(&out_q.size);
        sem_wait(&out_q.size);
        sem_wait(&out_q.size);

        fflush(stdout);

        pthread_mutex_lock(&out_q.q_mutex);

        printMsg("a'e");

        sem_getvalue(&out_q.size, &value);
     printMsg("%d", value);

        // Package pkg = out_q.queue[out_q.first];

        // removeFromOutgoing(&pkg);

        // pthread_mutex_unlock(&out_q.q_mutex);

        // sendPackage_(pkg);
    }
}