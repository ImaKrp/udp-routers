#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

int insertIntoIncoming(Package package);

int removeFromIncoming();

int insertIntoOutgoing(Package package); 

int removeFromOutgoing();

int queue_init(Queue *queue);

#endif