VV_serv: select_serv.o uni_mod.o
	gcc select_serv.o uni_mod.o -o VV_serv

VV_cli: select_cli.o uni_mod.o
	gcc select_cli.o uni_mod.o -o VV_cli

select_cli.o: select_cli.c
	gcc -c select_cli.c

select_serv.o: select_serv.c
	gcc -c select_serv.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f VV_* *.o
