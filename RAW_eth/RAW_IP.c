#include "RAW_IP.h"

struct wrap_IP* filling_IP(int sour, int dest, char *msg, u_int32_t addr_cli, u_int32_t addr_serv)
{
    struct wrap_UDP* temp_udp;
    struct wrap_IP* temp_ip;

    temp_udp = filling_UDP(sour, dest, msg);

    temp_ip = (struct wrap_IP*)malloc(sizeof(struct wrap_IP));
    memset(temp_ip, 0, sizeof(struct wrap_IP));
    temp_ip->udp475 = *temp_udp;
    temp_ip->ip475.version = 4;
    temp_ip->ip475.ihl = 5;
    temp_ip->ip475.tot_len = htons(sizeof(struct wrap_IP));
    temp_ip->ip475.frag_off = htons(0x4000);
    temp_ip->ip475.ttl = 255;
    temp_ip->ip475.protocol = 17;
    temp_ip->ip475.check = 0;
    temp_ip->ip475.saddr = addr_cli;
    temp_ip->ip475.daddr = addr_serv;

    return temp_ip;
}
