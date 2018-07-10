#ifndef _PING_H_
#define _PING_H_

#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <unistd.h>
#include <linux/icmp.h>
#include <string.h>
#include <arpa/inet.h>

#include "crc_16.h"

struct ping_s{
    struct iphdr ip_part;
    struct icmphdr icmp_part;
    char tmp[576];
};

#endif
