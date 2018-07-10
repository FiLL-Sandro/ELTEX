#ifndef _MSG_SERV_H_
#define _MSG_SERV_H_

#define MAS_US_SIZE 20

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>

#include "common_data.h"

int mas_us[MAS_US_SIZE];
int count_us;

void init_set();
void* auth(void *arg);
void* message_ex(void *arg);
void print_mas_us();


#endif
