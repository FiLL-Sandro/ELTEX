VV_serv: RAW_IP_ser.o RAW_UDP.o uni_mod.o
	gcc RAW_IP_ser.o RAW_UDP.o uni_mod.o -o VV_serv

VV_cli: RAW_IP_cli.o uni_mod.o
	gcc RAW_IP_cli.o uni_mod.o -o VV_cli

RAW_IP_ser.o: RAW_IP_ser.c 
	gcc -c RAW_IP_ser.c

RAW_IP_cli.o: RAW_IP_cli.c
	gcc -c RAW_IP_cli.c

RAW_UDP.o: RAW_UDP.c
	gcc -c RAW_UDP.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f VV_* *.o
