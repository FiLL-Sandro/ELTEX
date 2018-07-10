#ifndef _COMMON_SECT_H_
#define _COMMON_SECT_H_

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "storage.h"

struct shop{
    int is_empty;
    int goods;
};

extern struct shop *set_shop;

void init_demo();
void print_set_shop();

#endif
