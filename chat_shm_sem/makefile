VV_serv: common_data.o shm_sem_serv.o 
	gcc common_data.o shm_sem_serv.o -o VV_serv -lpthread

VV_cli: common_data.o shm_sem_cli.o
	gcc common_data.o shm_sem_cli.o -o VV_cli -lpthread

common_data.o: common_data.c
	gcc -c common_data.c

shm_sem_serv.o: shm_sem_serv.c
	gcc -c shm_sem_serv.c

shm_sem_cli.o: shm_sem_cli.c
	gcc -c shm_sem_cli.c

clean: 
	rm -f VV_* *.o
