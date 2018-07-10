#ifndef _RAW_IP_H_
#define _RAW_IP_H_

#include "RAW_UDP.h"
#include <netinet/ip.h>

struct wrap_IP
{
    struct iphdr ip475;
    struct wrap_UDP udp475;
};

struct wrap_IP* filling_IP(int sour, int dest, char *msg, u_int32_t addr_cli, u_int32_t addr_serv);


#endif
