#ifndef _COMMON_DATA_H_
#define _COMMON_DATA_H_

#define KEY_AUTH 0xaaaaaaaa
#define KEY_MESSAGE 0xbbbbbbbb
#define KEY_SEM 0xcccccccc

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

union semun{
  int val;	//			<= value for SETVAL
  struct semid_ds *buf;	//	<= buffer for IPC_STAT & IPC_SET
  unsigned short int *array;//		<= array for GETALL & SETALL
  struct seminfo *__buf;//		<= buffer for IPC_INFO
};

extern int msgid_auth;
extern int msgid_mess;
extern int semid;

#endif
