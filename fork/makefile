VV_serv: fork_serv.o uni_mod.o
	gcc fork_serv.o uni_mod.o -o VV_serv

VV_cli: fork_client.o uni_mod.o
	gcc fork_client.o uni_mod.o -o VV_cli

fork_cli.o: fork_client.c
	gcc -c fork_client.c

fork_serv.o: fork_serv.c
	gcc -c fork_serv.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f VV_* *.o
