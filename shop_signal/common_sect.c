#include "common_sect.h"

struct shop *set_shop = NULL;

void init_demo(){
    int i;
    struct sigaction tmp_action;
    sigset_t tmp_mask;

    memset( &tmp_action, 0, sizeof(struct sigaction) );

    set_shop = (struct shop*)malloc( sizeof(struct shop) * 4 );
    for(i = 0; i < 4; ++i){
        set_shop[i].goods = 1000;
        set_shop[i].is_empty = 0;
    }

    sigfillset( &tmp_mask );
    sigdelset( &tmp_mask, SIGALRM );
    sigdelset( &tmp_mask, SIGUSR1 );
    sigdelset( &tmp_mask, SIGINT );
    sigprocmask( SIG_SETMASK, &tmp_mask, NULL );

    sigemptyset( &tmp_action.sa_mask );

    tmp_action.sa_handler = storage_addict;
    sigaction( SIGALRM, &tmp_action, NULL );

    tmp_action.sa_handler = storage_exit;
    sigaction( SIGUSR1, &tmp_action, NULL );

    return;
}



void print_set_shop(){
    int i;

    printf("\n_______________________Status_of_shops:\n");
    for(i = 0; i < 4; ++i){
        printf("shop %d: %d, ",i,set_shop[i].goods);
    }
    printf("\n_______________________________________\n");
}
