// Выполнили Богатырев, Филиппов
// Отправляет на обычный сокет сообщение упакованное в ручную

#include "RAW_tran_ser.h"

struct msg_cust{
    struct udphdr udp_my;
    char msg[32];
};

struct msg_cust_recv
{
    struct iphdr ip_my;
    struct msg_cust pay;
};

int main(){
    int sock, count;
    struct msg_cust msg_tmp;
    struct msg_cust_recv msg_tmp_r;
    struct sockaddr_in tmp_addr;

    memset( &msg_tmp, 0, sizeof(struct msg_cust) );
    memset( &msg_tmp_r, 0, sizeof(struct msg_cust_recv) );
    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sock == -1){
        perror("\nSOCKET: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nSOCKET: successful\n");
    }

    msg_tmp.udp_my.source = htons(50002);
    msg_tmp.udp_my.dest = htons(50001);
    msg_tmp.udp_my.len = htons( sizeof(struct msg_cust) );
    msg_tmp.udp_my.check = 0;
    strncpy( msg_tmp.msg, "Hello darkness my old friend\0", sizeof(char)*32 );

    filling_sockaddr_in(&tmp_addr, 50001);

    if( sendto( sock, &msg_tmp, sizeof(msg_tmp), 0, (struct sockaddr*)&tmp_addr, sizeof(tmp_addr) ) == -1 )
    {
        perror("\nSEND: something wrong with sending: ");
        close(sock);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nSEND: messege was successful sent\n");
    }

    for(int temp_i = 0; temp_i < 10; temp_i++)
    {
        count = recvfrom( sock, &msg_tmp_r, sizeof(msg_tmp_r), 0, NULL, NULL );

        if(msg_tmp_r.pay.udp_my.source == htons(50001))

        {
            filling_sockaddr_in(&tmp_addr, 50001);

            printing_sockaddr_in(&tmp_addr);

            strncpy( msg_tmp.msg, msg_tmp_r.pay.msg, sizeof(char)*32 );

            if( sendto( sock, &msg_tmp, sizeof(msg_tmp), 0, (struct sockaddr*)&tmp_addr, sizeof(tmp_addr) ) == -1 )
            {
                perror("\nSEND: something wrong with sending: ");
                close(sock);
                exit(EXIT_FAILURE);
            }
            else
            {
                printf("\nSEND: messege was successful sent\n");
            }

            printf("\nmessage: %s\n",msg_tmp_r.pay.msg);
        }
    }

    close(sock);
    exit(EXIT_SUCCESS);
}
