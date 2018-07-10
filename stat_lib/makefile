VV_test_dyn: dyn_comp_cust test.c
	gcc -o VV_test_dyn test.c -L. -lcomp_cust

VV_test_stat: stat_comp_cust test.c
	gcc -o VV_test_stat test.c -L. -lcomp_cust

VV_test: clean complex_arith.o test.o
	gcc complex_arith.o test.o -o VV_test

complex_arith.o: complex_arith.c
	gcc -c complex_arith.c

test.o: test.c
	gcc -c test.c

VV_complex_arith: clean complex_arith.c
	gcc complex_arith.c -o VV_complex_arith

stat_comp_cust: clean complex_arith.o	
	rm -f libcomp_cust.*
	ar -rc libcomp_cust.a complex_arith.o

dyn_comp_cust: clean
	rm -f libcomp_cust.*
	gcc -fPIC -c complex_arith.c
	gcc -shared -o libcomp_cust.so complex_arith.o

clean:
	rm -f VV_* *.o
