#include "RAW_UDP.h"

struct wrap_UDP* filling_UDP(int sour, int dest, char *msg)
{
    struct wrap_UDP* temp_udp;

    temp_udp = (struct wrap_UDP*)malloc(sizeof( struct wrap_UDP ));
    memset(temp_udp , 0 , sizeof( struct wrap_UDP ));
    temp_udp->udp_my.dest = htons(dest);
    temp_udp->udp_my.source = htons(sour);
    temp_udp->udp_my.len = htons(sizeof(struct wrap_UDP));
    temp_udp->udp_my.check = 0;
    strncpy(&temp_udp->msg, msg, sizeof(char)*13);

    return temp_udp;
}
