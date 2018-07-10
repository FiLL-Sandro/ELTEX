#include "complex_arith.h"

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

