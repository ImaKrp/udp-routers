#include "defs/defs.h"
 
int showMenu();
void exitRouter();
void printStatus();
void sendPackage();
void showNeighbors();

void* controller(void* arg) {
    printMsg("\n\n----------------------\n");

    while(1) {
        int buffer = showMenu();

        if (buffer == 0) {
            exitRouter();
            break;

        } else if (buffer == 3) {
            showNeighbors();

        } else if (buffer == 2) {
            printStatus();

        } else if (buffer == 1)  {
            sendPackage();
            
        }
    }

    return NULL;
}

int showMenu() {
    int opt;

    printMsg("\nDigite: \n1 - Enviar pacote.\n2 - Exibir status. \n3 - Mostrar vizinhos.\n0 - Sair.\n\nrouter %d -> ", routerId);
    scanf("%d", opt);

    return opt;
}

void exitRouter() {
    pthread_cancel(thread_receiver);
    pthread_cancel(thread_sender);
    pthread_cancel(thread_handler);

    printMsg("Exiting... \n");
}

void printStatus() {
    printMsg("--- Status do Roteador ---\n");
    printMsg("ID: %d\n", routerId);
    printMsg("IP: %s\n", ip);
    printMsg("Porta: %d\n", port);
    printMsg("--------------------------\n\n");
}

void sendPackage() {
    char type[100], sendTo[100], payload[100];
    printMsg("Digite o tipo do pacote: \n0 - Controle\n1 - Dados\n\n->");
    scanf("%s", type);

    if(!strcmp(type, "0") == 0 && !strcmp(type, "1") == 0) {
        printMsg("Tipo inválido!\n\n");
        return;
    }

    printMsg("Digite o numero do roteador que deseja enviar o pacote:\n");
    for (int i = 0; i < R_SIZE; i++) {
        if (routers[i].id != routerId && routers[i].id != -1) {
            printMsg("%d - %s:%d\n", routers[i].id, routers[i].ip, routers[i].port);
        }
    }
    printMsg("\n->");
    scanf("%s", sendTo);

    int sendToId = atoi(sendTo);

    if((sendToId < 0 || sendToId == routerId)) {
        printMsg("Roteador inválido!\n\n");
        return;
    }

    Router sendToRouter = findRouterById(sendToId);

    if(sendToRouter.id == -1) {
        printMsg("Roteador não encontrado!\n\n");
        return;
    }

    printMsg("Digite o payload: ");
    printMsg("\n->");
    scanf("%s", payload);

    char package[B_LENGTH];
    strcpy(package, type);


    char sender[R_SIZE];
    sprintMsg(sender, "%d", routerId);
    strcat(package, sender);

    strcat(package, sendTo);
    strcat(package, payload);

    addToOutboundQueue(package, sendToRouter.port, sendToRouter.ip);
    printQueue(&outbound);
}

void showNeighbors() {
    for (int i = 0; i < R_SIZE; i++) {
        if (routers[i].id != routerId && routers[i].id != -1 && neighbors[i] != -1) {
            printMsg("Vizinho: %d - %s:%d, custo: %d\n", routers[i].id, routers[i].ip, routers[i].port, neighbors[i]);
        }
    }
    printMsg("\n----------------------\n");
}