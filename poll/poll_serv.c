// Выпонил Богатырев, Филиппов
/*
ну-у-у, тут сервер с потоковыми сокетами на портах 50001-50003(3 шт.)
и всё
*/

#include "poll_serv.h"

int main(){
    struct sockaddr_in sock_lis;
    int fd,fd1,i,port,amount;
    char tmp[80];
    struct pollfd fd_l[3];

    for(i = 0, port = 50001; i < 3; ++i, ++port){
        fd_l[i].fd = create_socket( STREAM );
        fd_l[i].events = POLLIN;

        filling_sockaddr_in(&sock_lis,port); printing_sockaddr_in(&sock_lis);
        binding_sockaddr_in(&sock_lis,fd_l[i].fd);

        listen(fd_l[i].fd,5);
    }

    while(1){
        amount = poll( fd_l, 3, 0);
        printf("\n$$$$$$$$$$$$$$$$$$$$\n"); sleep(1);

        if( amount > 0 ){
            for(i = 0; i < 3; ++i){
                if( fd_l[i].revents == POLLIN ){
                    fd1 = accept(fd_l[i].fd,NULL,NULL);
                    while(1){
                        amount = wrap_recv(fd1,tmp,sizeof(tmp));

                        if( amount == 0 ){ close(fd1); break;}

                        amount = atoi(tmp); printf("\n%d\n",amount); ++amount;

                        sprintf(tmp,"%d",amount);
                        wrap_send(fd1,tmp,sizeof(tmp));
                    }
                }
            }
        }
    }


    exit(EXIT_FAILURE);
}
