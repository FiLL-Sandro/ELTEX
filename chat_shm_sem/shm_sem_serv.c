/*
*  Выполнили: Богатырёв, Филиппов
*  Сервер запускается и занимается рассылкой сообщений, посланных пользователем, остальным пользователям
*
*/

#include "shm_sem_serv.h"

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
    union semun semun_tmp;
    int i;

    msgid_auth = shmget( KEY_AUTH, sizeof(struct authorization), IPC_CREAT | 0666 );
    if( msgid_auth == -1 ){
        perror("\nMSGID_AUTH: ");
        exit(EXIT_FAILURE);
    }
    if( (shm_auth = shmat( msgid_auth, NULL, 0 )) == ((void *)-1) ){
        perror("\nSHMAT_AUTH: ");
        exit(EXIT_FAILURE);
    }

    msgid_mess = shmget( KEY_MESSAGE, sizeof(struct message_cust), IPC_CREAT | 0666 );
    if( msgid_mess == -1 ){
        perror("\nMSGID_MESS: ");
        exit(EXIT_FAILURE);
    }
    if( (shm_mess = shmat( msgid_mess, NULL, 0 )) == ((void *)-1) ){
        perror("\nSHMAT_MESS: ");
        exit(EXIT_FAILURE);
    }

    memset( shm_auth, 0, sizeof(struct authorization) );
    memset( shm_mess, 0, sizeof(struct message_cust) );

    semid = semget( KEY_SEM, 2, IPC_CREAT | 0666 );
    if( semid == -1 ){
        perror("\nMSGID_MESS: ");
        exit(EXIT_FAILURE);
    }

    //printf("\nlong: %u\nint: %u",sizeof(long),sizeof(int));

    semun_tmp.val = 0;
    if( semctl( semid, 0, SETVAL, semun_tmp) == -1){
        perror("\nSEMCTL_INIT: ");
        exit(EXIT_FAILURE);
    }
    if( semctl( semid, 1, SETVAL, semun_tmp) == -1){
        perror("\nSEMCTL_INIT: ");
        exit(EXIT_FAILURE);
    }

    op_serv[0].sem_num = 0;
    op_serv[0].sem_flg = 0;
    op_serv[0].sem_op = -2;

    op_serv[1].sem_num = 0;
    op_serv[1].sem_flg = 0;
    op_serv[1].sem_op = 2;

    printf("\nINIT complete\n");
    printf("\nsem0: %i\n",semctl( semid, 0, GETVAL, semun_tmp ));
    //exit(EXIT_SUCCESS);


    return;
}

void* auth(void *arg){
    union semun semun_tmp;
    int i;

    count_us = -1;
    while(1){
        if( semop( semid, op_serv, 2 ) == -1 ){
            perror("\nSEMOP_INIT: ");
            exit(EXIT_FAILURE);
        } else{
            if( shm_auth->type == 1 ){
                ++count_us;
                mas_us[count_us] = shm_auth->pid;
                print_mas_us();

                shm_auth->type = mas_us[count_us];
            }
            printf("\nsem0: %i\n",semctl( semid, 0, GETVAL, semun_tmp ));
            //sleep(1);
        }
        semop( semid, &op_serv[0], 1 );
        printf("\nsem0: %i\n",semctl( semid, 0, GETVAL, semun_tmp ));
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
    union semun semun_tmp;
    int i, data;

    op_serv_mess[0].sem_num = 1;
    op_serv_mess[0].sem_flg = 0;
    op_serv_mess[0].sem_op = -2;

    op_serv_mess[1].sem_num = 1;
    op_serv_mess[1].sem_flg = 0;
    op_serv_mess[1].sem_op = 2;

    while(1){
        if( semop( semid, op_serv_mess, 2 ) == -1 ){
            perror("\nSEMOP_INIT: ");
            exit(EXIT_FAILURE);
        } else{
            if( shm_auth->type == 0 ){
                data = shm_mess->data;
                for(i = 0 ; i < count_us+1; ++i){
                    shm_mess->type = mas_us[i];
                    while( shm_mess->data != -1 ){
                        semop( semid, &op_serv_mess[0], 1 );
                        semop( semid, op_serv_mess, 2 );
                    }
                    shm_mess->data = data;
                }
                shm_mess->type = 0;
            }
            printf("\nsem0: %i\n",semctl( semid, 1, GETVAL, semun_tmp ));
            //sleep(1);
        }
        semop( semid, &op_serv_mess[0], 1 );
        printf("\nsem0: %i\n",semctl( semid, 1, GETVAL, semun_tmp ));
    }
}
