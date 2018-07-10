/*
*  Выполнили: Богатырёв, Филиппов
*  Клиент запускается с тремя параметрами: ID участка авторизации, ID участка  сообщений и ID семафора(набора).
*  Сообщения посылаются каждую секунду серверу и ловятся паралельно
*/

#include "shm_sem_cli.h"

int main(int argv, char *argc[]){
    int i;
    pthread_t tid;

    srand(time(0));

    msgid_auth = atoi( argc[1] );
    msgid_mess = atoi( argc[2] );
    semid = atoi(argc[3]);
    init_set();

    pthread_create( &tid, NULL, send_my_msg, NULL);

    while(1);

    exit(EXIT_FAILURE);
}

void init_set(){

    op_cli[0].sem_num = 0;
    op_cli[0].sem_flg = 0;
    op_cli[0].sem_op = 0;

    op_cli[1].sem_num = 0;
    op_cli[1].sem_flg = 0;
    op_cli[1].sem_op = 1;

    if( (shm_auth = shmat( msgid_auth, NULL, 0 )) == ((void *)-1) ){
        perror("\nSHMAT_AUTH: ");
        exit(EXIT_FAILURE);
    }

    while(1){
        if( semop( semid, op_cli, 2 ) == -1 ){
            perror("\nSEMOP_INIT: ");
            exit(EXIT_FAILURE);
        } else{

            if( shm_auth->type == 0 ){
                shm_auth->type = 1;
                shm_auth->pid = getpid();
            } else{
                if( shm_auth->type == getpid() ){
                    memset( shm_auth, 0, sizeof(struct authorization) );
                    semop( semid, &op_cli[1], 1 );
                    break;
                }
            }
            semop( semid, &op_cli[1], 1 );
        }
    }

    shmdt(shm_auth);
    printf("\nSession is beginning...\n");

    return;
}

void* send_my_msg(void *arg){

    op_cli[0].sem_num = 1;
    op_cli[1].sem_num = 1;

    if( (shm_mess = shmat( msgid_mess, NULL, 0 )) == ((void *)-1) ){
        perror("\nSHMAT_AUTH: ");
        exit(EXIT_FAILURE);
    }

    while(1){
        if( semop( semid, op_cli, 2 ) == -1 ){
            perror("\nSEMOP_INIT: ");
            exit(EXIT_FAILURE);
        } else{
            if( shm_mess->type == 0 ){
                shm_mess->pid_sender = getpid();
                shm_mess->data = rand() % 100;
            } else{
                if( shm_auth->type == getpid() ){
                    if( shm_mess ->data != -1 ){
                        printf("\n%d: %d\n",shm_mess->pid_sender,shm_mess->data);
                        shm_mess->data = -1;
                    }
                }
            }
            /*printf("\n_________________________________shmemory:\n");
            printf("type: %d; sender: %d; data: %d;",shm_mess->type,shm_mess->pid_sender,shm_mess->data);
            printf("\n__________________________________________\n");*/
            sleep(1);
            semop( semid, &op_cli[1], 1 );
        }
    }
}
