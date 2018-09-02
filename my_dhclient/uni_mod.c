#include "uni_mod.h"

int create_socket(enum typeofsocket type){
    int fd;

    switch (type) {
        case GRAM: fd = socket( AF_INET, SOCK_DGRAM, 0 ); break;
        case STREAM: fd = socket( AF_INET, SOCK_STREAM, 0 ); break;
		case RAW: fd = socket( AF_INET, SOCK_RAW, IPPROTO_UDP ); break;
        default: printf("\nATTENTION: unknown type of socket\n"); exit(EXIT_FAILURE);
    }

    if( fd == -1 ){
        perror("\nSOCKET: creation of socket: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nSOCKET: socket was successful created: fd = %d\n",fd);
    }

    return fd;
}

void filling_sockaddr_in(struct sockaddr_in *addr, char *p_addr, int port){
    memset( addr, 0, sizeof(struct sockaddr_in) );//Filling structure '0'
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

	if( p_addr != NULL && inet_pton( AF_INET, p_addr, &(addr->sin_addr.s_addr) ) != 1 ){
		perror("\nINET_PTON: error occured when converting address: ");
        exit(EXIT_FAILURE);
    } else{
        printf("\nINET_PTON: address was successful converted\n");
    }
}

void printing_sockaddr_in(struct sockaddr_in *addr){
    char tmp[80];

    printf("\nIP: %s, port: %i\n",
        inet_ntop( AF_INET, &(addr->sin_addr), tmp, sizeof(tmp) ),ntohs(addr->sin_port));
}

void binding_sockaddr_in(struct sockaddr_in *addr, int fd){
    if( bind( fd, (struct sockaddr*)addr, sizeof(struct sockaddr_in) ) == -1){
        perror("\nBIND: something wrong with binding: ");
        close(fd);
        exit(EXIT_FAILURE);
    } else{
        printf("\nBIND: binding was successful completed\n");
    }
}

void wrap_recvfrom(int fd, void *tmp, size_t s_tmp, struct sockaddr_in *cli_addr, socklen_t *sckl){

    if(cli_addr != NULL) memset( cli_addr, 0, sizeof(struct sockaddr_in) );

    if( recvfrom(fd, tmp, s_tmp, 0, (struct sockaddr*)cli_addr, sckl ) == -1 ){
        perror("\nRECV: something wrong with receiving: ");
        close(fd);
        exit(EXIT_FAILURE);
    } else{
        printf("\nRECV: messege was successful received\n");
    }
}

void wrap_sendto(int fd, void *tmp, size_t s_tmp, struct sockaddr_in *cli_addr, socklen_t sckl){

    if( sendto( fd, tmp, s_tmp, 0, (struct sockaddr*)cli_addr, sckl ) == -1 ){
        perror("\nSEND: something wrong with sending: ");
        close(fd);
        exit(EXIT_FAILURE);
    } else{
        printf("\nSEND: messege was successful sent\n");
    }
}

