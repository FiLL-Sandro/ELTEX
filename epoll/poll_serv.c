// Выпонил Богатырев, Филиппов

/*
ну-у-у, тут сервер с потоковыми сокетами на портах 50001-50003(3 шт.)
та же штука, но только с epoll()
*/

#include "poll_serv.h"

int main(){
    struct sockaddr_in sock_lis;
    int fd,fd1,i,port,amount,fd_epoll;
    char tmp[80];
    struct epoll_event event, event_a[3];

    fd_epoll = epoll_create(3);

    for(i = 0, port = 50001; i < 3; ++i, ++port){
        fd = create_socket( STREAM );

        filling_sockaddr_in(&sock_lis,port); printing_sockaddr_in(&sock_lis);
        binding_sockaddr_in(&sock_lis,fd);

        listen(fd,5);

        event.events = EPOLLIN;
        event.data.fd = fd;

        epoll_ctl( fd_epoll, EPOLL_CTL_ADD, fd, &event);
    }

    while(1){
        amount = epoll_wait( fd_epoll, event_a, 3, -1);
        printf("\n$$$$$$$$$$$$$$$$$$$$\n"); sleep(1);

        //if( amount > 0 ){
            for( i = amount - 1; i >=0; --i ){
                    fd1 = accept(event_a[i].data.fd,NULL,NULL);
                    while(1){
                        amount = wrap_recv(fd1,tmp,sizeof(tmp));

                        if( amount == 0 ){ close(fd1); break;}

                        amount = atoi(tmp); printf("\n%d\n",amount); ++amount;

                        sprintf(tmp,"%d",amount);
                        wrap_send(fd1,tmp,sizeof(tmp));
                    }
            }
        //}
    }


    exit(EXIT_FAILURE);
}
