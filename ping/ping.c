/*
*  Указан адресс клиента yota и адресс VK.com; запускаем -- получаем.
*/

#include "ping.h"

int main(){
    struct ping_s pack_ping;
    int sock, addr_cli, addr_serv, count;
    struct sockaddr_in tmp_addr;
    struct in_addr rec_addr;
    char res_addr[INET_ADDRSTRLEN];

    inet_pton(AF_INET, "10.0.0.10", &addr_cli);
    inet_pton(AF_INET, "87.240.129.133", &addr_serv);

    memset(&pack_ping, 0, sizeof(struct ping_s));

    printf("\nsize of ping_s: %lu\n",sizeof(struct ping_s));

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock == -1){
        perror("\nSOCKET: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nSOCKET: successful\n");
    }

    count = 1;
    if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, &count, sizeof(int)) == -1)
    {
        perror("\nlochara: ");
        close(sock);
        exit(EXIT_FAILURE);
    }

    pack_ping.ip_part.version = 4;
    pack_ping.ip_part.ihl = 5;
    pack_ping.ip_part.tot_len = htons(sizeof(struct ping_s));
    pack_ping.ip_part.frag_off = htons(0x4000);
    pack_ping.ip_part.ttl = 64;
    pack_ping.ip_part.protocol = 1;
    pack_ping.ip_part.saddr = addr_cli;
    pack_ping.ip_part.daddr = addr_serv;

    pack_ping.icmp_part.type = 8;
    pack_ping.icmp_part.checksum = htons(0xf7ff);//crc_16( (unsigned char*)&pack_ping.icmp_part, sizeof(pack_ping.icmp_part) )

    memset( &tmp_addr, 0, sizeof(struct sockaddr_in) );
    tmp_addr.sin_family = AF_INET;
    tmp_addr.sin_addr.s_addr = addr_serv;

    if( sendto( sock, &pack_ping, sizeof(struct ping_s), 0, (struct sockaddr*)&tmp_addr, sizeof(struct sockaddr_in) ) == -1 )
    {
        perror("\nSEND: something wrong with sending: ");
        close(sock);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nSEND: messege was successful sent\n");
    }

    count = recvfrom( sock, &pack_ping, sizeof(struct ping_s), 0, NULL, NULL );

    if( pack_ping.icmp_part.type == 0 ){
        rec_addr.s_addr = pack_ping.ip_part.saddr;
        if (inet_ntop(AF_INET, &rec_addr, res_addr, INET_ADDRSTRLEN) == NULL) {
            perror("\nINET_NTOP: ");
        } else{
            printf("\nping: source: %s, code: %u\n", res_addr, pack_ping.icmp_part.code);
        }
    }


    //printf("\nmsg: %s\n", pack237.udp237.msg);

    close(sock);
    exit(EXIT_SUCCESS);
}
