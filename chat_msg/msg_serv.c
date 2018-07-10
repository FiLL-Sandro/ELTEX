/*
*  Выполнили: Богатырёв, Филиппов
*  Сервер запускается и занимается рассылкой сообщений, посланных пользователем, остальным пользователям
*
*/

#include "msg_serv.h"

int main(){
    int i;
    pthread_t tid;

    init_set();
    pthread_create( &tid, NULL, auth, NULL );
    pthread_create( &tid, NULL, message_ex, NULL );

    while(1);

    exit(EXIT_FAILURE);
}

void init_set(){
    msgid_auth = msgget( KEY_AUTH, IPC_CREAT | 0666 );
    if( msgid_auth == -1 ){
        perror("\nMSGID_AUTH: ");
        exit(EXIT_FAILURE);
    }
    msgid_mess = msgget( KEY_MESSAGE, IPC_CREAT | 0666 );
    if( msgid_mess == -1 ){
        perror("\nMSGID_MESS: ");
        exit(EXIT_FAILURE);
    }

    return;
}

void* auth(void *arg){
    struct authorization tmp_auth;

    count_us = -1;
    while(1){
        if( msgrcv( msgid_auth, &tmp_auth, sizeof(struct authorization) - sizeof(long), 1, 0 ) == -1){
            perror("\nMSGRCV_AUTH: ");
        } else{
            ++count_us;
            mas_us[count_us] = tmp_auth.pid;
            print_mas_us();

            tmp_auth.type = mas_us[count_us];
            msgsnd( msgid_auth, &tmp_auth, sizeof(struct authorization) - sizeof(long), 0 );
        }
    }
}

void print_mas_us(){
    int i;

    printf("\n_________________________________mas_us:\n");
    for(i = 0; i < MAS_US_SIZE; ++i){
        printf("pid: %d\n", mas_us[i]);
    }
    printf("________________________________________\n");

    return;
}

void* message_ex(void *arg){
    struct message_cust tmp_mess;
    int i;

    while(1){
        if( msgrcv( msgid_mess, &tmp_mess, sizeof(struct message_cust) - sizeof(long), 1, 0 ) == -1){
            perror("\nMSGRCV_MESS: ");
        } else{
            for(i = 0 ; i < count_us; ++i){
                tmp_mess.type = mas_us[i];
                msgsnd( msgid_mess, &tmp_mess, sizeof(struct message_cust) - sizeof(long), 0 );
            }
        }
    }
}
