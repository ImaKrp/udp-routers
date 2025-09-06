#include "../defs.h"

int insertIntoQueue(Queue *queue, Package *pkg)
{
    int cur_size;
    sem_getvalue(&queue->size, &cur_size);

    if(cur_size==R_SIZE){
        printMsg("Queue is full... discarding pkg...");
        return -1;
    }
    
    pthread_mutex_lock(&queue->q_mutex);

    queue->queue[queue->next] = *pkg;
    queue->next = (queue->next + 1) % R_SIZE;
    pthread_mutex_unlock(&queue->q_mutex);
    sem_post(&queue->size);
    return 0;
}

int removeFromQueue(Queue *queue, Package *pkg)
{
    pthread_mutex_lock(&queue->q_mutex);
    memset(&queue->queue[queue->first], 0, sizeof(Package));
    queue->first = (queue->first + 1) % R_SIZE;
    pthread_mutex_unlock(&queue->q_mutex);
    sem_wait(&queue->size);
    
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
