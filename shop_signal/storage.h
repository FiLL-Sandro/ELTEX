#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "common_sect.h"

void *storage_step(void *arg);
void storage_addict(int arg);
void storage_exit(int arg);

#endif
