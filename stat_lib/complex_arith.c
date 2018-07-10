#include "complex_arith.h"
/*
int main(){
	int x, y, x1, y1;

	x = 123; y = 27; x1 = 5; y1 = -4;
	printf("\nfirst number: %d + %d*i, second number: %d + %d*i\n",x,y,x1,y1);
	sum_com(x,y,x1,y1);
	subtrac_com(x,y,x1,y1);
	multi_com(x,y,x1,y1);
	divi_com(x,y,x1,y1);

	exit(EXIT_SUCCESS);
}
*/
void sum_com(int x, int y, int x1, int y1){
	printf("\n(%d + %d*i) + (%d + %d*i) = %d + %d*i\n",x,y,x1,y1,x + x1,y + y1);
}

void subtrac_com(int x, int y, int x1, int y1){
	printf("\n(%d + %d*i) - (%d + %d*i) = %d + %d*i\n",x,y,x1,y1,x - x1,y - y1);
}

void multi_com( int x, int y, int x1, int y1){
	printf("\n(%d + %d*i) * (%d + %d*i) = %d + %d*i\n",x,y,x1,y1,x * x1 - y * y1,x * y1 + x1 * y);
}

void divi_com( int x, int y, int x1, int y1){
	double x_t, y_t;

	x_t = (double)(x * x1 + y * y1)/(double)(x1 * x1 + y1 * y1);
	y_t = (double)(x1 * y + x * y1)/(double)(x1 * x1 + y1 * y1);

	printf("\n(%d + %d*i) / (%d + %d*i) = %f + %f*i\n",x,y,x1,y1,x_t,y_t);
}
