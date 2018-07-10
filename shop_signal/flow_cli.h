#ifndef _FLOW_CLI_H_
#define _FLOW_CLI_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#include "storage.h"

extern pthread_t *flow_cli;
pthread_mutex_t mut_pay;

void* rout_cli(void *arg);

#endif
