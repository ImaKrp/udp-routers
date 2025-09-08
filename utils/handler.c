#include "../defs.h"

void* handler(void* arg) {
    while(1) {
        
        sem_wait(&in_q.size);

        pthread_mutex_lock(&in_q.q_mutex);

        Package pkg = in_q.queue[in_q.first];

        removeFromIncoming(&pkg);

        pthread_mutex_unlock(&in_q.q_mutex);


        printMsg("Received package: from=%d, to=%d, type=%d\n", pkg.sender, pkg.receiver, pkg.type);
        printMsg("%s\n", pkg.payload);


        if(pkg.type == 1){
        Package package;

        package.type = 0;
        package.receiver = pkg.sender;
        package.sender = routerId;

        char buf[256];
        snprintf(package.payload, sizeof(buf), "pkg received by router %d", pkg.receiver);


        insertIntoOutgoing(package);}
    }
    return NULL;
}