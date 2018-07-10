#ifndef _TEST_PCAP_H_
#define _TEST_PCAP_H_

#include "uni_mod.h"
#include <pcap/pcap.h>
#include <time.h>
#include <string.h>

#include <netinet/ip.h>
#include <netinet/udp.h>

#define ETHER_ADDR_LEN 6

struct sniff_ethernet {
    u_char ether_dhost[ETHER_ADDR_LEN]; /* Адрес назначения */
    u_char ether_shost[ETHER_ADDR_LEN]; /* Адрес источника */
    u_short ether_type; /* IP? ARP? RARP? и т.д. */
 };


struct package
{
    struct sniff_ethernet eth;
    struct iphdr ip;
    struct udphdr udp;
};

#endif
