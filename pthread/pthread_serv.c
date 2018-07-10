// Выпонил Богатырев, Филиппов
/*
**`Сервер запускается без параметров; Параллельность есть, а выхода нет ;)
*/

#include "uni_mod.h"
#include "pthread_serv.h"

struct resp_c
{
    int fd;
    struct sockaddr_in cli_addr;
    char tmp[80];
};

void create_recive(void *arg)
{
    int sckl, amount;
    struct resp_c temp_resp = *((struct resp_c *)arg);

    while(atoi(temp_resp.tmp) < 50000)
    {

        //filling_sockaddr_in(&cli_addr,1003);
        printing_sockaddr_in(&temp_resp.cli_addr);

        amount = atoi(temp_resp.tmp) + 1;
        sprintf(temp_resp.tmp,"%d",amount);
        wrap_sendto( temp_resp.fd, temp_resp.tmp, &temp_resp.cli_addr );

        sckl = sizeof(struct sockaddr_in);
        wrap_recvfrom( temp_resp.fd, temp_resp.tmp, &temp_resp.cli_addr, &sckl );

    }

    close(temp_resp.fd);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    int sfd[3], i, port, amount;
    char tmp[80];
    struct sockaddr_in s_addr[3], cli_addr;
    struct resp_c send_r;
    socklen_t sckl;
    pthread_t tid[3];

    //Creation of socket_____________________________________________
    for(i = 0; i < 3; ++i){
        sfd[i] = create_socket(GRAM);
    }
    sleep(2);
    //_______________________________________________________________
    //Filling address________________________________________________
    for(i = 0, port = 50000; i < 3; ++i, ++port){
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
    i = 0;
    while(i<3){
            sckl = sizeof(struct sockaddr_in);
            wrap_recvfrom( sfd[i], tmp, &cli_addr, &sckl );

            send_r.fd = sfd[i];
            send_r.cli_addr = cli_addr;
            strncpy(send_r.tmp, tmp, sizeof(char)*80);

            pthread_create(&tid[i], NULL, (void*)create_recive, &send_r);
            i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    //_______________________________________________________________
    exit(EXIT_SUCCESS);
}
