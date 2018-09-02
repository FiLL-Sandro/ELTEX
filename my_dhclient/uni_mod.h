#ifndef _UNI_MOD_H_
#define _UNI_MOD_H_

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

enum typeofsocket{
    GRAM,
    STREAM,
	RAW
};

int create_socket(enum typeofsocket type);
void filling_sockaddr_in(struct sockaddr_in *addr, char *p_addr, int port);
void printing_sockaddr_in(struct sockaddr_in *addr);
void binding_sockaddr_in(struct sockaddr_in *addr, int fd);
void wrap_recvfrom(int fd, void *tmp, size_t s_tmp, struct sockaddr_in *cli_addr, socklen_t *sckl);
void wrap_sendto(int fd, void *tmp, size_t s_tmp, struct sockaddr_in *cli_addr, socklen_t sckl);

#endif
