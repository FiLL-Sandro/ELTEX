//Выполнили Богатырев, Филиппов
/*Закомментированая часть на приём, действующая на отправку.
**Check_sum не высчитывается. Принять пакеты удалось, отправить ("выхода нет, скоро рассвет ;)")
*/

#include "RAW_eth_ser.h"

struct cust_pack
{
    struct ethhdr eth237;
    struct wrap_IP ip237;
};

//48:5a:b6:e6:4e:07

int main(){
    int sock, sock1, count = 0,size = 0, addr_cli, addr_serv;
    struct sockaddr_in tmp_addr, tmp_serv, temp;
    struct sockaddr_ll eth_addr;
    struct wrap_IP *tran_part;
    struct cust_pack eth457;
    char mas_ip_addr[80];
    unsigned char mac[] = {0x48, 0x5a, 0xb6, 0xe6, 0x4e, 0x07};

    inet_pton(AF_INET, "192.168.1.11", &addr_cli);
    inet_pton(AF_INET, "192.168.1.9", &addr_serv);

    printf("\nsizeof: %d\n", sizeof(struct wrap_IP));

    sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
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

    tran_part = filling_IP(50002, 50001, "aaaaaaaaaaaaa", addr_cli, addr_serv);

    /*if( sendto( sock, tran_part, sizeof(struct wrap_IP), 0, (struct sockaddr*)&tmp_addr, sizeof(tmp_addr) ) == -1 )
    {
        perror("\nSEND: something wrong with sending: ");
        close(sock);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("\nSEND: messege was successful sent\n");
    }*/

    /*while((size = recvfrom( sock, &eth457, sizeof(struct cust_pack), 0, NULL, NULL ))!= -1)
    {

        for(int i = 0; i < ETH_ALEN; i++)
        {
            if(eth457.eth237.h_source[i] != mac[i])
            {
                count = 1;
                break;
            }
        }

        if(count == 1) {count = 0; memset(&eth457, 0, sizeof(struct cust_pack)); continue;}
        else
        {
            printf("\nsize: %d\n", size);
            printf("mac_source: %x:%x:%x:%x:%x:%x\n",eth457.eth237.h_source[0], eth457.eth237.h_source[1],
                    eth457.eth237.h_source[2], eth457.eth237.h_source[3], eth457.eth237.h_source[4],
                    eth457.eth237.h_source[5]);
            temp.sin_addr.s_addr = eth457.ip237.ip475.saddr;
            if(inet_ntop(AF_INET, &temp.sin_addr, mas_ip_addr, 80) == 0)
            {
                perror("inet_ntop: ");
            }
            printf("\nip_source: %s\n", mas_ip_addr);
            printf("\nmsg: %s\n", eth457.ip237.udp475.msg);
            memset(&eth457, 0, sizeof(struct cust_pack));
        }
    }*/

    tran_part = filling_IP(50002, 50001, "Hellow Fill\0", addr_cli, addr_serv);
    eth457.ip237 = *tran_part;
    eth457.eth237.h_dest[0] = 0x48; eth457.eth237.h_dest[1] = 0x5a; eth457.eth237.h_dest[2] = 0xb6;
    eth457.eth237.h_dest[3] = 0xe6; eth457.eth237.h_dest[4] = 0x4e; eth457.eth237.h_dest[5] = 0x07;

    eth457.eth237.h_source[0] = 0x24; eth457.eth237.h_source[1] = 0xfd; eth457.eth237.h_source[2] = 0x52;
    eth457.eth237.h_source[3] = 0xbe; eth457.eth237.h_source[4] = 0x56; eth457.eth237.h_source[5] = 0x63;

    eth457.eth237.h_proto = 0x0800;

    eth_addr.sll_family = AF_PACKET;
    eth_addr.sll_addr[0] = 0x48; eth_addr.sll_addr[1] = 0x5a; eth_addr.sll_addr[2] = 0xb6;
    eth_addr.sll_addr[3] = 0xe6; eth_addr.sll_addr[4] = 0x4e; eth_addr.sll_addr[5] = 0x07;
    eth_addr.sll_halen = 6;
    eth_addr.sll_ifindex = if_nametoindex("wlp3s0");
    eth_addr.sll_protocol = ETH_P_WAN_PPP;

    count = sendto(sock, &eth457, sizeof(struct cust_pack), 0, (struct sockaddr*)&eth_addr, sizeof(struct sockaddr_ll));
    printf("\ncount: %d\n", count);


    close(sock);
    exit(EXIT_SUCCESS);
}
