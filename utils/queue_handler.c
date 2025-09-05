#include "../defs.h"

int insertIntoQueue(Queue *queue, Package *pkg)
{


    
    pthread_mutex_lock(&queue->q_mutex);

    queue->queue[queue->next] = *pkg;
    queue->next = (queue->next + 1) % R_SIZE;
    pthread_mutex_unlock(&queue->q_mutex);
    // pthread_mutex_unlock(&out_q.q_empty);
    return 0;
}

int removeFromQueue(Queue *queue, Package *pkg)
{
    pthread_mutex_lock(&queue->q_mutex);
    memset(&queue->queue[queue->first], 0, sizeof(Package));
    queue->first = (queue->first + 1) % R_SIZE;
    pthread_mutex_unlock(&queue->q_mutex);
    // pthread_mutex_unlock(&queue->q_full);

    if(!&queue->queue[queue->first]){
        // pthread_mutex_lock(&out_q.q_empty);
    }

    
    return 0;
}

int insertIntoIncoming(Package package)
{
    return insertIntoQueue(&in_q, &package);
}

int removeFromIncoming(Package *package)
{
    return removeFromQueue(&in_q, package);
}

int insertIntoOutgoing(Package package)
{
    return insertIntoQueue(&out_q, &package);
}

int removeFromOutgoing(Package *package)
{
    return removeFromQueue(&out_q, package);
}