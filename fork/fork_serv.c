// Выпонил Богатырев, Филиппов
/*
**`Сервер запускается без параметров; максимальное количество клиентов: 3, Параллельность есть, а выхода нет ;)
*/

#include "uni_mod.h"
#include "fork_serv.h"

int main(int argc, char *argv[]){
    int sfd, fd1, i, port, amount;
    char tmp[80];
    struct sockaddr_in s_addr;
    port = 50001;
    //Creation of socket_____________________________________________
        sfd = create_socket( STREAM );
    sleep(2);
    //_______________________________________________________________
    //Filling address________________________________________________
        filling_sockaddr_in( &s_addr, port ); printing_sockaddr_in( &s_addr );
    sleep(2);
    //_______________________________________________________________
    //Binding address________________________________________________
        binding_sockaddr_in( &s_addr, sfd );
    listen(sfd,5);

    //_______________________________________________________________
    //Receiving message______________________________________________
    i = 0;
    while(i < 3){

            fd1 = accept(sfd,NULL,NULL);

            if(fork() == 0)
            {
                while(1)

                {
                    amount = wrap_recv(fd1,tmp,sizeof(tmp));

                    if( amount == 0 ){ close(fd1); break;}

                    amount = atoi(tmp); printf("\n%d\n",amount); ++amount;

                    sprintf(tmp,"%d",amount);
                    wrap_send(fd1,tmp,sizeof(tmp));
                }

                exit(EXIT_SUCCESS);
            }
            i++;
    }

    close(sfd);

    //_______________________________________________________________
    exit(EXIT_SUCCESS);
}
