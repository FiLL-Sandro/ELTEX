//Выполнили Богатырев, Филиппов
//Отправляет собранный пакет RAW клиенту и получает ответ от клиента

#include "RAW_IP_ser.h"

struct cust_pack
{
    struct iphdr ip237;
    struct wrap_UDP udp237;
};

int main(){
    int sock, sock1, count = 1, addr_cli, addr_serv;
    struct sockaddr_in tmp_addr, tmp_serv;
    struct wrap_UDP* tran_part;
    struct cust_pack pack237;

    memset(&pack237, 0, sizeof(struct cust_pack));

    inet_pton(AF_INET, "192.168.1.4", &addr_cli);
    inet_pton(AF_INET, "192.168.1.7", &addr_serv);

    printf("\nsizeof: %d\n", sizeof(struct cust_pack));

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
    if (sock == -1){
        perror("\nSOCKET: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nSOCKET: successful\n");
    }

    sock1 = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock1 == -1){
        perror("\nSOCKET: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nSOCKET: successful\n");
    }

    memset( &tmp_addr, 0, sizeof(struct sockaddr_in) );
    tmp_addr.sin_family = AF_INET;
    tmp_addr.sin_port = htons(50001);
    tmp_addr.sin_addr.s_addr = addr_serv;

    memset( &tmp_serv, 0, sizeof(struct sockaddr_in) );
    tmp_serv.sin_family = AF_INET;
    tmp_serv.sin_port = htons(50002);
    tmp_serv.sin_addr.s_addr = addr_cli;

    binding_sockaddr_in(&tmp_serv, sock1);

    tran_part = filling_UDP(50002, 50001, "aaaaaaaaaaaaa");

    pack237.udp237 = *tran_part;

    printf("\n%s\n", pack237.udp237.msg);

    pack237.ip237.version = 4;
    pack237.ip237.ihl = 5;
    pack237.ip237.tot_len = htons(sizeof(struct cust_pack));
    pack237.ip237.frag_off = htons(0x4000);
    pack237.ip237.ttl = 255;
    pack237.ip237.protocol = 17;
    pack237.ip237.check = 0;
    pack237.ip237.saddr = addr_cli;
    pack237.ip237.daddr = addr_serv;

    if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &count, sizeof(int)) == -1)
    {
        perror("\nlochara: ");
        close(sock);
        exit(EXIT_FAILURE);
    }

    if( sendto( sock, &pack237, sizeof(struct cust_pack), 0, (struct sockaddr*)&tmp_addr, sizeof(tmp_addr) ) == -1 )
    {
        perror("\nSEND: something wrong with sending: ");
        close(sock);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nSEND: messege was successful sent\n");
    }

    count = recvfrom( sock, &pack237, sizeof(pack237), 0, NULL, NULL );

    printf("count: %d", count);

    printf("\nmsg: %s\n", pack237.udp237.msg);

    close(sock);
    exit(EXIT_SUCCESS);
}
