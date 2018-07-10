VV_ping: crc_16.o ping.o
	gcc crc_16.o ping.o -o VV_ping

crc_16.o: crc_16.c
	gcc -c crc_16.c

ping.o: ping.c
	gcc -c ping.c

VV_crc: crc_16.c
	gcc crc_16.c -o VV_crc

clean: 
	rm -f *.o VV_*
