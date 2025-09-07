#include "../defs.h"

int queue_init(Queue *queue){

    sem_init(&queue->size,0 ,0);
    
    for(int i = 0; i<R_SIZE; i++){
        queue->queue[i].type = -1;
    }
    return 0;
}

int insertIntoQueue(Queue *queue, Package *pkg)
{
    pthread_mutex_lock(&queue->q_mutex);

      if(queue->queue[queue->next].type != -1){
        printMsg("Queue is full... discarding pkg...");
        return -1;
    }

    queue->queue[queue->next] = *pkg;
    queue->next = (queue->next + 1) % R_SIZE;
    pthread_mutex_unlock(&queue->q_mutex);
    sem_post(&queue->size);
    return 0;
}

int removeFromQueue(Queue *queue)
{
    pthread_mutex_lock(&queue->q_mutex);
    queue->queue[queue->first].type = -1;

    Package *p = &queue->queue[queue->first];

    strcpy(p->payload, "");
    strcpy(p->buffer, "");

    p->receiver = -1;
    p->sender = -1;
    p->type = -1;

    queue->first = (queue->first + 1) % R_SIZE;
    pthread_mutex_unlock(&queue->q_mutex);
    
    return 0;
}

int insertIntoIncoming(Package package)
{
    return insertIntoQueue(&in_q, &package);
}

int removeFromIncoming()
{
    return removeFromQueue(&in_q);
}

int insertIntoOutgoing(Package package)
{
    return insertIntoQueue(&out_q, &package);
}

int removeFromOutgoing()
{
    return removeFromQueue(&out_q);
}
