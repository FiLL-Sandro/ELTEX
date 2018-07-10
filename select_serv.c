// Выпонил Богатырев, Филиппов
/*
сервер занимает три порта: 1000 -- 1002, включительно, -- а затем начинает ждать обращения клиета
*/


#include "uni_mod.h"
#include "select_serv.h"

int main(int argc, char *argv[]){
    int sfd[3], i, port, amount;
	char tmp[80];
    struct sockaddr_in s_addr[3], cli_addr;
    socklen_t sckl;
    fd_set set_read;

	//Creation of socket_____________________________________________
    for(i = 0; i < 3; ++i){
        sfd[i] = create_socket(GRAM);
    }
    sleep(2);
	//_______________________________________________________________
	//Filling address________________________________________________
    for(i = 0, port = 1000; i < 3; ++i, ++port){
        filling_sockaddr_in( &(s_addr[i]), port ); printing_sockaddr_in( &(s_addr[i]) );
    }
    sleep(2);
	//_______________________________________________________________
	//Binding address________________________________________________
    for(i = 0; i < 3; ++i){
        binding_sockaddr_in( &(s_addr[i]), sfd[i] );
    }
	//_______________________________________________________________
	//Receiving message______________________________________________
    while(1){
        FD_ZERO( &set_read );
        for(i = 0; i < 3; ++i){ FD_SET( sfd[i],&set_read ); }
        select(1020,&set_read,NULL,NULL,NULL);

        for(i = 0; i < 3; ++i){
            if( FD_ISSET( sfd[i], &set_read ) == 0 ) continue;

            sckl = sizeof(struct sockaddr_in);
            wrap_recvfrom( sfd[i], tmp, &cli_addr, &sckl );
            //filling_sockaddr_in(&cli_addr,1003);
            printing_sockaddr_in(&cli_addr);

            amount = atoi(tmp) + 1;
            sprintf(tmp,"%d",amount);
            wrap_sendto( sfd[i], tmp, &cli_addr );
        }
    }
	//_______________________________________________________________
    for(i = 0; i < 3; ++i){
        close(sfd[i]);
    }
	exit(EXIT_SUCCESS);
}
