// Выпонил Богатырев, Филиппов
/*
тестирование клиета проводилось на портах 1003 -- 1005(эти порты занимали сами клиенты)
изначально при запуске требуется ввести два параметра: свой порт и порт, к которому нужно присоединиться
примеры: 1004 1000; 1005 1002
*/

#include "uni_mod.h"

int main(int argc, char *argv[]){
    int sfd, i, port, cfd;
    char tmp[80];
    struct sockaddr_in s_addr, cli_addr;
    socklen_t sckl;

    port = atoi(argv[1]);

    //Creation of socket_____________________________________________
    sfd = create_socket(GRAM);
    //_______________________________________________________________
    //Filling address________________________________________________
    filling_sockaddr_in(&s_addr,port); printing_sockaddr_in(&s_addr);
    //_______________________________________________________________
    //Binding address________________________________________________
    binding_sockaddr_in(&s_addr,sfd);
    //_______________________________________________________________
    //Sending message______________________________________________
    i = 0;
    port = atoi(argv[2]);
    filling_sockaddr_in(&cli_addr,port);
    while(1){
        sprintf(tmp,"%d",i);

        wrap_sendto(sfd,tmp,&cli_addr);
        sckl = sizeof( struct sockaddr_in );
        wrap_recvfrom( sfd, tmp, &cli_addr, &sckl );
        //filling_sockaddr_in(&cli_addr,1000);
        printing_sockaddr_in(&cli_addr);

        i = atoi(tmp);
        printf("\n%d\n",i);
        if( i >= 50000 ) break;
    }
    //_______________________________________________________________
    close(sfd);
    exit(EXIT_SUCCESS);
}
