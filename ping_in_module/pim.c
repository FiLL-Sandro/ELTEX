#include <linux/module.h>
#include <linux/uaccess.h>
#include <linux/init.h>

#include <linux/skbuff.h>
#include <uapi/linux/icmp.h>
#include <net/icmp.h>
#include <net/route.h>
#include <uapi/linux/ip.h>
#include <net/ip.h>
#include <linux/ip.h>
#include <linux/inet.h>
#include <linux/netdevice.h>

#include <linux/string.h>
#include <linux/byteorder/generic.h>

MODULE_LICENSE( "GPL" );
static struct sk_buff *skb_my = NULL;

static int __init ping_my_init( void ) {
	struct icmphdr icmp, *tmp_icmp;
	struct iphdr ip4, *tmp_ip4;
	unsigned short counter;

	unsigned char mac_daddr[] = {0xf8,0x35,0xdd,0x6f,0x53,0xe8};
    unsigned char mac_saddr[] = {0xf8,0x35,0xdd,0x6f,0x53,0xe9};  

	int ret;

	memset( &icmp, 0, sizeof(struct icmphdr) );
	memset( &ip4,  0, sizeof(struct iphdr)   );

	counter = 0;
	icmp.type = ICMP_ECHO;
	icmp.code = 0;
	icmp.un.echo.id = 0;
	icmp.un.echo.sequence = htons(counter); ++counter;
	icmp.checksum = ip_compute_csum( &icmp, sizeof(struct icmphdr) );

	ip4.ihl = 5;
	ip4.version = 4;
	ip4.tos = 0x00;
	ip4.tot_len = htons( sizeof(struct iphdr) + sizeof(struct icmphdr) );
	ip4.id = 0;
	ip4.frag_off = 0;
	ip4.ttl = 65;
	ip4.protocol = 1;
	ip4.saddr = in_aton("10.0.0.10");
	ip4.daddr = in_aton("91.198.174.192");
	ip_send_check( &ip4 );

	skb_my = dev_alloc_skb(1500);
	if( skb_my == NULL ){
		printk( KERN_INFO "===dev_alloc_skb is failed");
	} else{
		skb_my->dev = __dev_get_by_name(&init_net,"enxf835dd6f53e9");
		if( skb_my->dev == NULL ){
			printk( KERN_INFO "===__dev_get_by_name is failed");
			goto err_case;
		}

		skb_reserve(skb_my,NET_IP_ALIGN);

		tmp_icmp = (struct icmphdr*)skb_push(skb_my,sizeof(struct icmphdr));
		memset( tmp_icmp, 0,     sizeof(struct icmphdr) );
		memcpy( tmp_icmp, &icmp, sizeof(struct icmphdr) );

		tmp_ip4 = (struct iphdr*)skb_push(skb_my,sizeof(struct iphdr));
		memset( tmp_ip4, 0,    sizeof(struct iphdr) );
		memcpy( tmp_ip4, &ip4, sizeof(struct iphdr) );

		dev_hard_header( skb_my, skb_my->dev, ETH_P_IP, mac_daddr, mac_saddr, skb_my->dev->addr_len );
		/*if( skb_my->sk != NULL ){
			ret = ip_local_out( dev_net( skb_my->dev ), skb_my->sk, skb_my );
			printk( KERN_INFO "\n\nip_local_out: %d\n\n", ret );
		} else{
			printk( KERN_INFO "\n\nskb_my->sk == NULL\n\n" );
		}*/

		//icmp_send( skb_my, ICMP_ECHO, 0, rt_nexthop( skb_rtable(skb_my), ip_hdr(skb_my)->daddr) );
		printk( KERN_INFO "\n\ndev_queue_xmit: %d\n\n", dev_queue_xmit(skb_my) );
	}

err_case:
	return 0;
}

static void __exit ping_my_exit( void ) {
	printk( KERN_INFO "\n\n===my module is disable\n\n" );
//if( skb_my != NULL ) kfree_skb(skb_my);
}

module_exit( ping_my_exit );
module_init( ping_my_init );
