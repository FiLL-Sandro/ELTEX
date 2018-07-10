// Выполнили Богатырев, Филиппов
// Принимает сообщение с RAW сокета и отправляет свое

#include "RAW_tran_cli.h"

int main(){
    int sock;
    struct sockaddr_in addr_cli, addr_ser;
    char buff[32];
    socklen_t size;

    filling_sockaddr_in(&addr_cli,50001);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1){
        perror("\nSOCKET: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nSOCKET: successful\n");
    }
    binding_sockaddr_in(&addr_cli,sock);

    size = sizeof( struct sockaddr_in );

    for(int temp_i = 0; temp_i < 9; temp_i++)
    {
        wrap_recvfrom(sock,buff,&addr_ser,&size);

        printf("\nmsg: %s\n", buff);

        printing_sockaddr_in(&addr_ser);

        strncpy(buff,"Message received\0",sizeof(char)*32);

        wrap_sendto(sock,buff,&addr_ser);
    }

    close(sock);
    exit(EXIT_SUCCESS);
}
