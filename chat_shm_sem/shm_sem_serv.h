#ifndef _SHM_SEM_SERV_H_
#define _SHM_SEM_SERV_H_

#define MAS_US_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>

#include "common_data.h"

int mas_us[MAS_US_SIZE];
int count_us;

struct message_cust *shm_mess;
struct authorization *shm_auth;

struct sembuf op_serv[2];
struct sembuf op_serv_mess[2];

void init_set();
void* auth(void *arg);
void* message_ex(void *arg);
void print_mas_us();


#endif
