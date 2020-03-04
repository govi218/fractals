#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <complex.h>
#include <stdbool.h> 
#include <limits.h>
#include <string.h>


// run with -lm in gcc and don't forget the -fopenmp

// Complie with:
// gcc -fopenmp mandelbrot_parallel.c -lm -o m.out -mcmodel=large

double boundry;
int l, m, n; 
int max_iterations = 512; // how many iteration before one decides c belongs to the set
static float complex mSet[1000000000];
FILE *f;



void main(){
    clock_t begin, end;
    double time_spent;
    begin = clock();
    // printf("%f + i%f\n", creal(z), cimag(z));
    boundry = 2.0;
    // for(m=0;m<100000;m++) {
    //     mSet[m] = z;
    // }
    // l = 0;
    
    #pragma omp parallel // initiating the parallel
    #pragma omp for schedule(runtime) // – Schedule and chunk size taken from the OMP_SCHEDULE environment variable (or the runtime library … for OpenMP 3.0).
    for(n=0; n<8;n++) { // intiate a loop of length 8 for 8 threads. Adjustable to any other amount
        n = n/2; // for the purpose of spliting the outer loop for each thread  below
        // char filename[100] = "mandelbrot.";
        // sprintf(filename, "mandelbrot%d", n);
        // strcat(filename, ".txt");
        // printf("%s\n", filename);
        // f = fopen(filename, "w");
        double i, j; // declare as global variables for index and boundry
        double complex z, c; // complex number of the from a + b*I
        bool boolVar;
        int k;
        for(i=-2.0+n;i<=-1.5+n;i=i+0.0001) { // breaking the loop down for 8 threads
            for(j=-2.0;j<=2.0;j=j+0.0001) { // this loop will not directly participate in multithreading. Only as a result of outer loop participating
                // printf("%f\n", i);
                boolVar = false;
                z = 0.0 + 0.0*I; // initiate the mandelbrot algorithm
                c = i + j*I;
                // printf("%f + i%f\n", creal(c), cimag(c));
                k = 0;
                while(cabs(z) < fabs(boundry) && !boolVar) { // condition on the set
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
                    mSet[l] = c; // store c in array for writing to file later
                    // fprintf(f, "%f + i%f\n", creal(c), cimag(c));
                    l++;
                }
            }
        }
        // fclose(f);
    }
    // fmt.Println(mSet)
    // opening file in writing mode
    f = fopen("mandelbrot.txt", "w");
    
    for(m=0;m<(1000000000);m++) {
        fprintf(f, "%f + i%f\n", creal(mSet[m]), cimag(mSet[m]));
    }
    fclose(f);
    end = clock();
    time_spent = (double)(end - begin)/(4*CLOCKS_PER_SEC);
    printf("%6.3f\n", time_spent);
    printf("%d\n", l);
}

// run with -lm in gcc
