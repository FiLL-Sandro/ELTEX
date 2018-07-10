// Выполнили Богатырев, Филиппов
// Клиент принимает сообщение от raw-сокета и отвечает ему другим сообщением("that's all")

#include "RAW_tran_cli.h"

int main(){
    int sock, addr, port;
    struct sockaddr_in addr_cli, addr_ser;
    char buff[32];
    socklen_t size;

    port = 50001;

    if( inet_pton( AF_INET, "192.168.1.7", &addr ) != 1 ){
        printf("\nINET_PTON: FAILURE\n");
        exit(EXIT_FAILURE);
    }

    memset( &addr_cli, 0, sizeof(struct sockaddr_in) );//Filling structure '0'
    addr_cli.sin_family = AF_INET;
    addr_cli.sin_port = htons(port);
    addr_cli.sin_addr.s_addr = addr;

    printing_sockaddr_in(&addr_cli);

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1){
        perror("\nSOCKET: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nSOCKET: successful\n");
    }
    binding_sockaddr_in(&addr_cli,sock);

    while(1){
        memset( &addr_ser, 0, sizeof(struct sockaddr_in) );
        wrap_recvfrom(sock,buff,&addr_ser,&size);

        printf("\nmsg: %s\n", buff);

        printing_sockaddr_in(&addr_ser);

        strncpy(buff,"that's all\0",sizeof("that's all\0"));

        wrap_sendto(sock,buff,&addr_ser);
    }

    close(sock);
    exit(EXIT_SUCCESS);
}
