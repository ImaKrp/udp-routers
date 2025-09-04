#ifndef QUEUE_HANDLER_H
#define QUEUE_HANDLER_H

#include "defs/defs.h"

int insertIntoIncoming(Package package);

int removeFromIncoming(Package *package);

int insertIntoOutgoing(Package package); 

int removeFromOutgoing(Package *package);

#endif