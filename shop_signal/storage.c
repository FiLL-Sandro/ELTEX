#include "storage.h"

void* storage_step(void *arg){
    sigset_t curr_mask;
    int sig;
/*
    sigfillset( &curr_mask );
    sigdelset( &curr_mask, SIGALRM );
    sigdelset( &curr_mask, SIGUSR1 );
    sigdelset( &curr_mask, SIGINT );
*/
    /*
    sigemptyset( &curr_mask );
    sigaddset( &curr_mask, SIGALRM );
    sigaddset( &curr_mask, SIGUSR1 );
    sigaddset( &curr_mask, SIGINT );
    */
    while(1){
        //alarm(3);
        sleep(3);
        raise(SIGALRM);
        printf("\n11111111111111111111111111storage_step\n");
        //sleep(1);
        //sigwait( &curr_mask, &sig );
    }

    exit(EXIT_FAILURE);
}

void storage_addict(int arg){
    int i;

    for(i = 0; i < 4; ++i){
        if( set_shop[i].is_empty == 1 ){
            set_shop[i].goods += 1000;
            set_shop[i].is_empty = 0;
        }
    }

    printf("\n\n22222222222222222222222222storage_addict\n\n");
    print_set_shop();
}

void storage_exit(int arg){
    exit(EXIT_SUCCESS);
}
