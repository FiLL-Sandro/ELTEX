VV_dhcli: dh_client_cust.o uni_mod.o
	gcc dh_client_cust.o uni_mod.o -o VV_dhcli

dh_client_cust.o: dh_client_cust.c
	gcc -c dh_client_cust.c

uni_mod.o: uni_mod.c
	gcc -c uni_mod.c

clean: 
	rm -f *.o VV_*

VV_rawtest: uni_mod.o raw_test.o
	gcc uni_mod.o raw_test.o -o VV_rawtest

raw_test.o: raw_test.c
	gcc -c raw_test.c
