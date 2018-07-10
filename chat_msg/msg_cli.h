#ifndef _MSG_CLI_H_
#define _MSG_CLI_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

#include "common_data.h"

void init_set();
void* recv_my_msg(void *arg);
void* send_my_msg(void *arg);

#endif
