VV_serv: pthread_serv.o uni_mod.o
	gcc pthread_serv.o uni_mod.o -o VV_serv -lpthread

VV_cli: pthread_client.o uni_mod.o
	gcc pthread_client.o uni_mod.o -o VV_cli

pthread_cli.o: pthread_client.c
	gcc -c pthread_client.c

pthread_serv.o: pthread_serv.c
	gcc -c pthread_serv.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f VV_* *.o
