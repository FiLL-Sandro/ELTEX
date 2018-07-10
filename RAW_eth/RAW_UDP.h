#ifndef _RAW_UDP_H_
#define _RAW_UPD_H_

#include <netinet/in.h>
#include <netinet/udp.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_CUST_MSG 20

struct wrap_UDP{
    struct udphdr udp_my;
    char msg[SIZE_CUST_MSG];
};

struct wrap_UDP* filling_UDP(int sour, int dest, char *msg);


#endif
