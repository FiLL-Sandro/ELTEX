#ifndef _SHM_SEM_CLI_H_
#define _SHM_SEM_CLI_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <unistd.h>
#include <time.h>

#include "common_data.h"

void init_set();
void* send_my_msg(void *arg);

struct message_cust *shm_mess;
struct authorization *shm_auth;

struct sembuf op_cli[2];

#endif
