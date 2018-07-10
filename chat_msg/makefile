VV_serv: common_data.o msg_serv.o 
	gcc common_data.o msg_serv.o -o VV_serv -lpthread

VV_cli: common_data.o msg_cli.o
	gcc common_data.o msg_cli.o -o VV_cli -lpthread

common_data.o: common_data.c
	gcc -c common_data.c

msg_serv.o: msg_serv.c
	gcc -c msg_serv.c

msg_cli.o: msg_cli.c
	gcc -c msg_cli.c

poll_serv.o: poll_serv.c
	gcc -c poll_serv.c

poll_cli.o: poll_cli.c
	gcc -c poll_cli.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f VV_* *.o
