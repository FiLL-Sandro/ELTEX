VV_serv: RAW_tran_ser.o uni_mod.o
	gcc RAW_tran_ser.o uni_mod.o -o VV_serv

VV_cli: RAW_tran_cli.o uni_mod.o
	gcc RAW_tran_cli.o uni_mod.o -o VV_cli

RAW_tran_ser.o: RAW_tran_ser.c
	gcc -c RAW_tran_ser.c

RAW_tran_cli.o: RAW_tran_cli.c
	gcc -c RAW_tran_cli.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f VV_* *.o
