#ifndef _COMMON_DATA_H_
#define _COMMON_DATA_H_

#define KEY_AUTH 0xff0110ff
#define KEY_MESSAGE 0xffff1111

#include <stdio.h>
#include <stdlib.h>

struct authorization{
    long type;
    int pid;
};

struct message_cust{
    long type;
    int pid_sender;
    int data;
};

extern int msgid_auth;
extern int msgid_mess;

#endif
