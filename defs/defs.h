#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "controller.h"
// #include "receiver.h"
// #include "sender.h"
#include "get_cfg.h"
#include "helper.h"
#include "helper.h"
#include "udp/sender.h"
#include "udp/receiver.h"

#define R_SIZE 10
#define IP_SIZE 15
#define B_LENGTH 512

#define path_els "./configs/enlaces.config"
#define pathRtr "./configs/roteador.config"

typedef struct {
    int id;
    char ip[IP_SIZE];
    int port;
} Router;

typedef struct {
    int type;       // 0 => controle || 1 => dados
    int sender; 
    int receiver;
    char payload[140];
    char buffer[100];  
} Package;

typedef struct {
    Package queue[R_SIZE];
    int first;
    int last; 
    pthread_mutex_t q_mutex;
    sem_t size;
} Queue;



extern Queue in_q;
extern Queue out_q;
extern int neighbors[R_SIZE];
extern int routerId;
extern char ip[IP_SIZE];
extern int port;
extern pthread_t thread_receiver, thread_sender, thread_handler,thread_controller;
extern Router routers[R_SIZE];
extern pthread_mutex_t print_mtx;

#endif
