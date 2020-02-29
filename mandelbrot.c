#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <complex.h>
#include <stdbool.h> 
#include <limits.h>


double boundry, i, j;
double complex z, c;
bool boolVar;
int k, l, m;
int max_iterations = 512;
// double complex mSet[10000];
FILE *f;



void main(){
    clock_t begin, end;
    double time_spent;
    begin = clock();
    z = 0.0 + 0.0*I;
    // printf("%f + i%f\n", creal(z), cimag(z));
    boundry = 2.0;
    // for(m=0;m<100000;m++) {
    //     mSet[m] = z;
    // }
    // l = 0;
    f = fopen("mandelbrot.txt", "w");
    for(i=-2.0;i<=2.0;i=i+0.0001) {
        for(j=-2.0;j<=2.0;j=j+0.0001) {
            // printf("%f\n", i);
            boolVar = false;
            z = 0.0 + 0.0*I;
            c = i + j*I;
            // printf("%f + i%f\n", creal(c), cimag(c));
            k = 0;
            while(cabs(z) < fabs(boundry) && !boolVar) {
                // printf("%d\n", cabs(z) - fabs(boundry));
                if(k==max_iterations) {
                    boolVar = true;
                } else if(!boolVar) {
                z = z*z + c;
                // printf("%f\n", c);
                // printf("%f\n", cabs(z) - fabs(boundry));
                k++;
                }
            }
            if(boolVar) {
                // printf("%f + i%f\n", creal(c), cimag(c));
                // mSet[l] = c;
                fprintf(f, "%f + i%f\n", creal(c), cimag(c));
                // l++;
            }
        }
    }
    // fmt.Println(mSet)
    // opening file in writing mode
    // f = fopen("mandelbrot.txt", "w");
    
    // for(m=0;m<(100000);m++) {
    //     fprintf(f, "%f + i%f\n", creal(mSet[m]), cimag(mSet[m]));
    // }
    fclose(f);
    end = clock();
    time_spent = (double)(end - begin)/CLOCKS_PER_SEC;
    printf("%6.3f\n", time_spent);
}

// run with -lm in gcc
