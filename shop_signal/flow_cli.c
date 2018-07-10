/*
*  Выполнил: Богатырёв, Филиппов
*  Запустить программу: создаются потоки с задачами склада и задачами клиента; запас магазинов 1000; пополнение происходит каждые
*  3 секунды, если запас ниже 50; убить процесс можно при отправке SIGUSR1, SIGINT;
*/

#include "flow_cli.h"

pthread_t *flow_cli = NULL;

int random_cust(int N){ return rand()%N; }

int main(){
    int i;
    pthread_t tmp_tid;

    srand(time(0));

    init_demo();
    print_set_shop();
    //pthread_create( &tmp_tid, NULL, storage_step, NULL );

    pthread_mutex_init( &mut_pay, NULL );

    flow_cli = (pthread_t*)malloc( sizeof(pthread_t) * 4 );
    for(i = 0; i < 4; ++i){
        pthread_create( &flow_cli[i], NULL, rout_cli, NULL);
    }

    storage_step(NULL);
    //while(1);

    exit(EXIT_FAILURE);
}

void* rout_cli(void *arg){
    int i;

    while(1){
        i = random_cust(4);

        pthread_mutex_lock( &mut_pay );
        if( set_shop[i].is_empty == 0 ){
            set_shop[i].goods -= random_cust(50) + 1;
            if( set_shop[i].goods <= 50 ) set_shop[i].is_empty = 1;
        }
        pthread_mutex_unlock( &mut_pay );

        printf("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n");
        print_set_shop();
        sleep(1);
    }

    exit(EXIT_FAILURE);
}
