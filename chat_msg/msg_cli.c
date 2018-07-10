/*
*  Выполнили: Богатырёв, Филиппов
*  Клиент запускается с парой параметров: ID очереди авторизации и ID очереди сообщений.
*  Сообщения посылаются каждую секунду серверу и ловятся паралельно
*/

#include "msg_cli.h"

int main(int argv, char *argc[]){
    int i;
    pthread_t tid;

    srand(time(0));

    msgid_auth = atoi( argc[1] );
    msgid_mess = atoi( argc[2] );
    init_set();

    pthread_create( &tid, NULL, send_my_msg, NULL);
    pthread_create( &tid, NULL, recv_my_msg, NULL);

    while(1);

    exit(EXIT_FAILURE);
}

void init_set(){
    struct authorization auth_cli;

    auth_cli.type = 1;
    auth_cli.pid = getpid();

    msgsnd( msgid_auth, &auth_cli, sizeof(struct authorization) - sizeof(long), 0 );
    msgrcv( msgid_auth, &auth_cli, sizeof(struct authorization) - sizeof(long), getpid(), 0 );

    printf("\nSession is beginning...\n");

    return;
}

void* send_my_msg(void *arg){
    struct message_cust tmp_mess;

    while(1){
        tmp_mess.type = 1;
        tmp_mess.pid_sender = getpid();
        tmp_mess.data = rand() % 100;

        msgsnd( msgid_mess, &tmp_mess, sizeof(struct message_cust) - sizeof(long), 0 );
        sleep(1);
    }
}

void* recv_my_msg(void *arg){
    struct message_cust tmp_mess;

    while(1){
        if( msgrcv( msgid_mess, &tmp_mess, sizeof(struct message_cust) - sizeof(long), getpid(), 0 ) == -1){
            perror("\nMSGRCV: ");
        } else{
            printf("\n%d: %d\n",tmp_mess.pid_sender,tmp_mess.data);
        }
    }
}
