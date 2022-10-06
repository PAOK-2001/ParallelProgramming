#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define THREAD_NUM 10
#define RADIUS 1
#define TOTAL_PIXEL 100000*RADIUS*2
double timer = 0;
double pi = 0;
long int circlePoints = 0;

void* montecarlo_chunk(void * CS){
    int start = clock();
    int MAX_PIXELS = (int) CS;
    double x_coord, y_coord;
    srand(time(NULL));
    for (int i = 0; i < (MAX_PIXELS*MAX_PIXELS)/THREAD_NUM; i++){
        x_coord = (double)(rand() % (MAX_PIXELS +1))/(MAX_PIXELS);
        y_coord = (double)(rand() % (MAX_PIXELS +1))/(MAX_PIXELS);
        if ((x_coord*x_coord + y_coord*y_coord)<= (RADIUS)){
            circlePoints+= 1;
        }
    }
    int end = clock();
    timer += (double)(end-start)/CLOCKS_PER_SEC;
    pthread_exit(NULL);
}

int main(){
    int returnCode;
    long int squarePoints = TOTAL_PIXEL*TOTAL_PIXEL;
    pthread_t threads[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++){
        returnCode = pthread_create(&threads[i],NULL,montecarlo_chunk, (void*) (TOTAL_PIXEL));
        pthread_join(threads[i],NULL);
    }
    

    printf("C: %d\nS: %d\n",circlePoints,squarePoints);
    pi = ((double)(4*circlePoints)/(squarePoints));
    printf("Pi estimation: %f\n",pi);
    printf("Elapsed time: %f\n",timer);
    pthread_exit(NULL);
    
}