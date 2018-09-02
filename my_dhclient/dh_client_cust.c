//enxf835dd6f53e9
#include "dh_client_cust.h"

void main(){
	int val, size_val, rfd;
	struct my_dh_request pack_bootp;
	struct sockaddr_in dst_for_udp;

	int i, port_cli, port_serv, cfd;
	unsigned int src_ip, dst_ip;
    char tmp[80];
    struct sockaddr_in s_addr, cli_addr;
    socklen_t sckl;

	struct bootp_header dhcp_str;

	memset( &pack_bootp, 0, sizeof(struct my_dh_request) );
	filling_sockaddr_in( &dst_for_udp, "255.255.255.255", 67);

	pack_bootp.udp_head.source = htons(68);
	pack_bootp.udp_head.dest = htons(67);
	pack_bootp.udp_head.len = htons(sizeof(struct udphdr) + sizeof(struct bootp_header));
	pack_bootp.udp_head.check = 0;

	pack_bootp.ip_head.ip_hl = 5;
	pack_bootp.ip_head.ip_v = 4;
	pack_bootp.ip_head.ip_tos = 0;
	pack_bootp.ip_head.ip_len = sizeof(struct ip) + sizeof(struct udphdr) + sizeof(struct bootp_header);
	pack_bootp.ip_head.ip_id = htons(0x659b);
	pack_bootp.ip_head.ip_off = htons(IP_DF);
	pack_bootp.ip_head.ip_ttl = 128;
	pack_bootp.ip_head.ip_p = IPPROTO_UDP;
	pack_bootp.ip_head.ip_sum = 0;

	if( inet_pton( AF_INET, "0.0.0.0", &pack_bootp.ip_head.ip_src.s_addr) != 1 ){
		perror("\nINET_PTON(src): something wrong: ");
		exit(EXIT_FAILURE);
	} else{
		printf("\nINET_PTON(src): address was successful converted\n");
	}

	if( inet_pton( AF_INET, "255.255.255.255", &pack_bootp.ip_head.ip_dst.s_addr) != 1 ){
		perror("\nINET_PTON(dst): something wrong: ");
		exit(EXIT_FAILURE);
	} else{
		printf("\nINET_PTON(dst): address was successful converted\n");
	}

	rfd = create_socket(RAW);

	val = 1;
	if( setsockopt( rfd, IPPROTO_IP, IP_HDRINCL, &val, sizeof(int) ) == -1  ){
		perror("\nSETSOCKOPT: error is occured when setting option value: ");
	} else{
		printf("\nSETSOCKOPT: command was successful complete; size_val =\n");
	}
	i = 1;
	if( setsockopt( rfd, SOL_SOCKET, SO_BROADCAST, &i, sizeof(int) ) == -1  ){
		perror("\nSETSOCKOPT: error is occured when getting option value: ");
	} else{
		printf("\nSETSOCKOPT: command was successful complete;\n");
	}

	//_______________________________________________________________
	printf("\n\nsizes:\n");
	printf("unsigned short: %lu\n",sizeof(unsigned short));
	printf("short: %lu\n",sizeof(short));
	printf("int: %lu\n",sizeof(int));
	printf("unsigned int: %lu\n",sizeof(unsigned int));
	printf("char: %lu\n",sizeof(char));
	printf("unsigned char: %lu\n",sizeof(unsigned char));
	printf("\n\n\n");
	//_______________________________________________________________
	memset( &dhcp_str, 0, sizeof(struct bootp_header) );
	dhcp_str.op = 1;
	dhcp_str.htype = 0x01;
	dhcp_str.hlen = 6;
	dhcp_str.xid = 0xf2589d04;
	dhcp_str.secs = 100;

	dhcp_str.chaddr[0] = 0xf8;
	dhcp_str.chaddr[1] = 0x35;
	dhcp_str.chaddr[2] = 0xdd;
	dhcp_str.chaddr[3] = 0x6f;
	dhcp_str.chaddr[4] = 0x53;
	dhcp_str.chaddr[5] = 0xe9;
	
	dhcp_str.vend[0] = 99;
	dhcp_str.vend[1] = 130;
	dhcp_str.vend[2] = 83;
	dhcp_str.vend[3] = 99;
	
	dhcp_str.vend[4] = 53;
	dhcp_str.vend[5] = 1;
	dhcp_str.vend[6] = 1;
	dhcp_str.vend[7] = 255;

	memcpy( &pack_bootp.bootp_data, &dhcp_str, sizeof(struct bootp_header) );
	wrap_sendto( rfd, &pack_bootp, sizeof(struct my_dh_request), &dst_for_udp, sizeof(struct sockaddr_in) );

	while(1){
		memset( &pack_bootp, 0, sizeof(struct my_dh_request) );
		wrap_recvfrom( rfd, &pack_bootp, sizeof(struct my_dh_request), NULL, NULL );

		if( ntohs(pack_bootp.udp_head.source) == 67 && ntohs(pack_bootp.udp_head.dest) == 68 ){
			if( pack_bootp.bootp_data.op == 2 )
				src_ip = pack_bootp.bootp_data.yiaddr;
				inet_ntop( AF_INET, &pack_bootp.bootp_data.yiaddr, tmp, sizeof(char)*80 );
				printf("\noffered address: %s\n",tmp);
				break;
		}
	}

	i = 0; dst_ip = 0;
	while( pack_bootp.bootp_data.vend[i] != 255 ){
		if( pack_bootp.bootp_data.vend[i] == htons(54) ){
			i += 2;
			dst_ip |= pack_bootp.bootp_data.vend[i] << 3*8; ++i;
			dst_ip |= pack_bootp.bootp_data.vend[i] << 2*8; ++i;
			dst_ip |= pack_bootp.bootp_data.vend[i] << 1*8; ++i;
			dst_ip |= pack_bootp.bootp_data.vend[i];
			break;
		}
		++i;
	}

	memset( &pack_bootp, 0, sizeof(struct my_dh_request) );
	pack_bootp.udp_head.source = htons(68);
	pack_bootp.udp_head.dest = htons(67);
	pack_bootp.udp_head.len = htons(sizeof(struct udphdr) + sizeof(struct bootp_header));
	pack_bootp.udp_head.check = 0;

	pack_bootp.ip_head.ip_hl = 5;
	pack_bootp.ip_head.ip_v = 4;
	pack_bootp.ip_head.ip_tos = 0;
	pack_bootp.ip_head.ip_len = sizeof(struct ip) + sizeof(struct udphdr) + sizeof(struct bootp_header);
	pack_bootp.ip_head.ip_id = htons(0x659b);
	pack_bootp.ip_head.ip_off = htons(IP_DF);
	pack_bootp.ip_head.ip_ttl = 128;
	pack_bootp.ip_head.ip_p = IPPROTO_UDP;
	pack_bootp.ip_head.ip_sum = 0;
	pack_bootp.ip_head.ip_src.s_addr = src_ip;
	pack_bootp.ip_head.ip_dst.s_addr = dst_ip;

	memset( &dhcp_str, 0, sizeof(struct bootp_header) );
	dhcp_str.op = 1;
	dhcp_str.htype = 0x01;
	dhcp_str.hlen = 6;
	dhcp_str.xid = 0xf2589d04;
	dhcp_str.secs = 100;

	dhcp_str.chaddr[0] = 0xf8;
	dhcp_str.chaddr[1] = 0x35;
	dhcp_str.chaddr[2] = 0xdd;
	dhcp_str.chaddr[3] = 0x6f;
	dhcp_str.chaddr[4] = 0x53;
	dhcp_str.chaddr[5] = 0xe9;
	
	dhcp_str.vend[0] = 99;
	dhcp_str.vend[1] = 130;
	dhcp_str.vend[2] = 83;
	dhcp_str.vend[3] = 99;
	
	dhcp_str.vend[4] = 53;
	dhcp_str.vend[5] = 1;
	dhcp_str.vend[6] = 3;

	dhcp_str.vend[7] = 55;
	dhcp_str.vend[8] = 1;
	dhcp_str.vend[9] = 1;

	dhcp_str.vend[10] = 50;
	dhcp_str.vend[11] = 4;
	dhcp_str.vend[12] = (src_ip & 0xff000000) >> 8*3;
	dhcp_str.vend[13] = (src_ip & 0x00ff0000) >> 8*2;
	dhcp_str.vend[14] = (src_ip & 0x0000ff00) >> 8*1;
	dhcp_str.vend[15] = (src_ip & 0x000000ff);

	dhcp_str.vend[16] = 255;

	memcpy( &pack_bootp.bootp_data, &dhcp_str, sizeof(struct bootp_header) );
	wrap_sendto( rfd, &pack_bootp, sizeof(struct my_dh_request), &dst_for_udp, sizeof(struct sockaddr_in) );

	close(rfd);

    exit(EXIT_SUCCESS);
}
