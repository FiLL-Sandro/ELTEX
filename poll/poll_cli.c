// Выпонил Богатырев, Филиппов
/*
это клиент; в параметре указывается порт сервера и всё(50001-50003)
*/

#include "poll_cli.h"

int main(int argc, char *argv[]){
    struct sockaddr_in sock_dest;
    int fd,i,port;
    char tmp[80];

    port = atoi(argv[1]);

    fd = create_socket( STREAM );

    filling_sockaddr_in(&sock_dest,port); printing_sockaddr_in(&sock_dest);
    wrap_connect(fd,&sock_dest);

    i = 0;
    while(1){
        sprintf(tmp,"%d",i);
        wrap_send(fd,tmp,sizeof(tmp));

        wrap_recv(fd,tmp,sizeof(tmp));
        i = atoi(tmp); printf("\ni: %d\n",i);
        if( i > 50000 ) break;
    }

    close(fd);
    exit(EXIT_FAILURE);
}
