VV_storage: storage.o common_sect.o flow_cli.o
	gcc storage.o common_sect.o flow_cli.o -o VV_strorage -lpthread

storage.o: storage.c
	gcc -c storage.c

common_sect.o: common_sect.c
	gcc -c common_sect.c

flow_cli.o: flow_cli.c
	gcc -c flow_cli.c

clean: 
	rm -f VV_* *.o
