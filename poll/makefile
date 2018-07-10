VV_serv: poll_serv.o uni_mod.o
	gcc poll_serv.o uni_mod.o -o VV_serv

VV_cli: poll_cli.o uni_mod.o
	gcc poll_cli.o uni_mod.o -o VV_cli

poll_serv.o: poll_serv.c
	gcc -c poll_serv.c

poll_cli.o: poll_cli.c
	gcc -c poll_cli.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f VV_* *.o
