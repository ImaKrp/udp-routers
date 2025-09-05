#include "../defs.h"

void exitRouter()
{
    pthread_cancel(thread_receiver);
    pthread_cancel(thread_sender);
    pthread_cancel(thread_handler);

    printMsg("Exiting... \n");
}

void printStatus()
{
    printMsg("--- Status do Roteador ---\n");
    printMsg("ID: %d\n", routerId);
    printMsg("IP: %s\n", ip);
    printMsg("Porta: %d\n", port);
    printMsg("--------------------------\n\n");
}

void sendPackage()
{
    char payload[100];
    printMsg("Type: \n0 - Control\n1 - Data\n\n->");

    char typeC[100];
    fflush(stdout);
    fgets(typeC, sizeof(typeC), stdin);

    int type = atoi(typeC);

    if (type != 0 && type != 1)
    {
        printMsg("Invalid type... expected value 0 || 1\n\n");
        return;
    }

    printMsg("Type the receiver id:\n");
    for (int i = 0; i < R_SIZE; i++)
    {
        if (routers[i].id != routerId && routers[i].id != -1)
        {
            printMsg("%d - %s:%d\n", routers[i].id, routers[i].ip, routers[i].port);
        }
    }
    printMsg("\n->");
    char sendToC[100];
    fflush(stdout);
    fgets(sendToC, sizeof(sendToC), stdin);

    int sendTo = atoi(sendToC);

    if ((sendTo < 0 || sendTo == routerId))
    {
        printMsg("Invalid router...\n\n");
        return;
    }

    Router sendToRouter = routers[sendTo - 1];

    if (sendToRouter.id == -1)
    {
        printMsg("Router not found...\n\n");
        return;
    }

    printMsg("Type the payload: ");
    printMsg("\n->");
    fflush(stdout);
    fgets(payload, sizeof(payload), stdin);

    Package package;

    package.type = type;
    package.receiver = sendTo;
    package.sender = routerId;

    strcpy(package.payload, payload);

    insertIntoOutgoing(package);
}

void showNeighbors()
{
    for (int i = 0; i < R_SIZE; i++)
    {
        if (routers[i].id != routerId && routers[i].id != -1 && neighbors[i] != -1)
        {
            printMsg("Neighbor: %d - %s:%d, cost: %d\n", routers[i].id, routers[i].ip, routers[i].port, neighbors[i]);
        }
    }
    printMsg("\n----------------------\n");
}

void *controller(void *arg)
{
    printMsg("\n\n----------------------\n");

    while (1)
    {
        char optC[100];

        printMsg("\nChoose: \n1 - Send package\n2 - Show status \n3 - Show neighbors\n0 - Exit.\n\nrouter %d -> ", routerId);

        fflush(stdout);
        fgets(optC, sizeof(optC), stdin);

        int opt = atoi(optC);

        if (opt == 0)
        {
            exitRouter();
            break;
        }
        else if (opt == 3)
        {
            showNeighbors();
        }
        else if (opt == 2)
        {
            printStatus();
        }
        else if (opt == 1)
        {
            sendPackage();
        }
    }

    return NULL;
}
