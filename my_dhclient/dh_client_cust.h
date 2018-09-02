#ifndef _DH_CLIENT_CUST_H_
#define _DH_CLIENT_CUST_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <netinet/in.h>
#include <unistd.h>
#include "uni_mod.h"

struct bootp_header{
	unsigned char op;
	unsigned char htype;
	unsigned char hlen;
	unsigned char hops;
	unsigned int xid;
	unsigned short secs;

	unsigned short reserv;

	unsigned int ciaddr;
	unsigned int yiaddr;
	unsigned int siaddr;
	unsigned int giaddr;
	unsigned char chaddr[16];
	unsigned char sname[64];
	unsigned char file[128];
	unsigned char vend[64];
};

struct my_dh_request{
	struct ip ip_head;
	struct udphdr udp_head;
	struct bootp_header bootp_data;
};

#endif
