//Выполнили Богатырев, Филиппов
//После активации обработчика захвата, требуется нажимать разные клавиши; введите 'a' для выхода
//на каждом проходе захватывается по 3 UPD пакета
#include "test_pcap.h"
//name: wlp3s0

void handler(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes){
    struct timeval ug_time = h->ts;
    struct tm* ptm;
    struct package *pack;
    ptm = localtime(&ug_time.tv_sec);
    char time_string[40], tmp[80];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", ptm);
    printf("\n%s\n", time_string);

    pack = (struct package *)bytes;

    printf("\nIP: %s, port: %i\n",
        inet_ntop( AF_INET, &(pack->ip.daddr), tmp, sizeof(tmp) ),ntohs(pack->udp.dest));
}

int main()
{
    int stat, *lst_dl, i;
    pcap_if_t *lst_dev;
    pcap_addr_t *lst_addr;
    pcap_t *cap_h;
    struct bpf_program fp;
    char err_msg[PCAP_ERRBUF_SIZE], name_dev[] = "wlp3s0";
    u_char *begin_pack;

    cap_h = pcap_create(name_dev,err_msg);
    if( cap_h == NULL ){
        printf("\nPCAP_CREATE: %s\n",err_msg);
        exit(EXIT_FAILURE);
    } else{
        printf("\nPCAP_CREATE: successful\n");
    }

    pcap_set_snaplen(cap_h,65535);
    pcap_set_promisc(cap_h,1);
    pcap_set_rfmon(cap_h,0);
    pcap_set_timeout(cap_h,1000);
    if( pcap_set_tstamp_type(cap_h,PCAP_TSTAMP_HOST) != 0 ){
        printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    }

    stat = pcap_activate(cap_h);
    if( stat > 0 ){
        //printf("\nPCAP_ACTIVATE: FAILURE\n");
        pcap_perror(cap_h,"\nPCAP_ACTIVATE: ");
        pcap_close(cap_h);
        exit(EXIT_FAILURE);
    } else{
        printf("\nPCAP_ACTIVATE: SUCCESSFUL\n");
    }

    if( pcap_set_datalink(cap_h,1) == -1 ){
        pcap_perror(cap_h,"\nPCAP_SET_DATALINK: ");
        pcap_close(cap_h);
        exit(EXIT_FAILURE);
    }

    if (pcap_compile(cap_h, &fp, "ip proto \\udp", 0, PCAP_NETMASK_UNKNOWN) == -1)
    {
        pcap_perror(cap_h,"\nPCAP_COMPILE: ");
        pcap_close(cap_h);
        exit(EXIT_FAILURE);
    }


    pcap_setfilter(cap_h, &fp);

    while(getchar() != 'a')
    {

        if( pcap_loop(cap_h, 3, handler, begin_pack) == -1){
            pcap_perror(cap_h,"\nPCAP_LOOP: ");
            pcap_close(cap_h);
            exit(EXIT_FAILURE);
        }

        stat = pcap_list_datalinks(cap_h,&lst_dl);
        if( stat == -1 ){
            pcap_perror(cap_h,"\nPCAP_LIST_DATALINKS: ");
            exit(EXIT_FAILURE);
        } else{
            printf("\nPCAP_LIST_DATALINKS: successful\n");
        }
    }
    /*printf("\n%d\n",stat);
    for(i = 0; i < stat; ++i){
        printf("\n%s %d\n",pcap_datalink_val_to_name(lst_dl[i]),lst_dl[i]);
    }*/




    pcap_close(cap_h);


    /*
    stat = pcap_findalldevs(&lst_dev, err_msg);
    if( stat == -1 ){
        printf("\nPCAP_FINDALLDEVS: %s\n",err_msg);
        exit(EXIT_FAILURE);
    } else{
        printf("\nPCAP_FINDALLDEVS: successful\n");
    }

    while( lst_dev->next != NULL ){
        printf("\nname: %s\n",lst_dev->name);
        if( lst_dev->addresses != NULL ) lst_addr = lst_dev->addresses;
            else{ lst_dev = lst_dev->next; continue;}
        while( lst_addr->next != NULL ){
            if( lst_addr->addr->sa_family == AF_INET ) printf("addr: AF_INET\n");
                else if( lst_addr->addr->sa_family == AF_INET6 ) printf("addr: AF_INET6\n");
                    else printf("addr: none\n");
            lst_addr = lst_addr->next;
        }
        printf("\n");
        lst_dev = lst_dev->next;
    }
    */

    exit(EXIT_SUCCESS);
}
