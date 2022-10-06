#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define RADIUS 1
#define TOTAL_PIXEL 100000*RADIUS*2
double timer = 0;
double pi = 0;

void montecarlo_chunk(int chunkSize){
    int start = clock();
    int MAX_PIXELS = chunkSize;
    double x_coord, y_coord;
    long int circlePoints = 0;
    long int squarePoints = MAX_PIXELS*MAX_PIXELS;
    srand(time(NULL));
    for (int i = 0; i < (MAX_PIXELS*MAX_PIXELS); i++){
        x_coord = (double)(rand() % (MAX_PIXELS +1))/(MAX_PIXELS);
        y_coord = (double)(rand() % (MAX_PIXELS +1))/(MAX_PIXELS);
        if ((x_coord*x_coord + y_coord*y_coord)<= (RADIUS)){
            circlePoints++;
        }
    }
    int end = clock();
    printf("C: %d\nS: %d\n",circlePoints,squarePoints);
    timer += (double)(end-start)/CLOCKS_PER_SEC;
    pi += ((double)(4*circlePoints)/(squarePoints));
}

int main(){
    montecarlo_chunk(TOTAL_PIXEL);
    printf("Pi estimation: %f\n",pi);
    printf("Elapsed time: %f\n",timer);
}