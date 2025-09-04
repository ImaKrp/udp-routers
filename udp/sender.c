
#include "defs/defs.h"

void die(char *s)
{
    perror(s);
    exit(1);
}

int sendPackage(char *ip, int port, Package package)
{
    struct sockaddr_in si_other;
    int s, i, slen = sizeof(si_other);
    char buf[B_LENGTH];

    if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *)&si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(port);

    if (inet_aton(ip, &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    if (sendto(s, &package, sizeof(package), 0, (struct sockaddr *)&si_other, slen) == -1)
    {
        die("sendto()");
    }

    close(s);
    return 0;
}

int sender(){
     while(1) {
        sem_wait(&out_q.size);

        pthread_mutex_lock(&out_q.q_mutex);
        
        sem_post(&out_q.size);

        Package pkg = out_q.queue[out_q.first];

        RemoveFromOutgoing();

        pthread_mutex_unlock(&out_q.q_mutex);

        sendPackageToRouter(pkg);
    }
    return 0;
}