#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define RADIUS 1
#define TOTAL_PIXEL 10000000
double pi = 0;

long int circlePoints = 0;
// Create mutex variable
pthread_mutex_t lock;
// Function to run part of montecarlo pi estimation.
// Takes as argument THREAD_NUM to divide the for into N chunks
void* montecarlo_chunk(void * THREAD_NUM){
    int temp = 0; // temporary value to increment
    double x_coord, y_coord;
    srand(time(NULL));
    for (int i = 0; i < (TOTAL_PIXEL/(int)THREAD_NUM); i++){
        x_coord = (double)(rand() % (TOTAL_PIXEL))/(TOTAL_PIXEL);
        y_coord = (double)(rand() % (TOTAL_PIXEL))/(TOTAL_PIXEL);
        if ((x_coord*x_coord + y_coord*y_coord)<= (RADIUS)){
            temp++;
        }
    }
    // Lock aumenting the global variable to avoid conflicts
    pthread_mutex_lock(&lock);
    circlePoints += temp;
    pthread_mutex_unlock(&lock);
    //End threads
    pthread_exit(NULL);
}

int main(int argc, char* argv[]){ 
    int start = clock();
    // Parse the number of threads
    const int THREAD_NUM = atoi(argv[1]);
    int returnCode;
    long int squarePoints = TOTAL_PIXEL;
    //Create array to store threads in memory
    pthread_t threads[THREAD_NUM];
    // Check if mutex can be intialized
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("Mutex failed\n");
        return -1;
    }
    // Create THREAD_NUM number of threads
    for (int i = 0; i < THREAD_NUM; i++){
        returnCode = pthread_create(&threads[i],NULL,montecarlo_chunk, (void*) (THREAD_NUM));
    }
    // Wait for said number of threads to finish
    for (int j = 0; j < THREAD_NUM; j++){
        pthread_join(threads[j],NULL);
    }
    // Destroy mutex and free
    pthread_mutex_destroy(&lock);
    int end = clock();
    // Print values
    printf("Points in circle: %d ; Points in square: %d\n",circlePoints,squarePoints);
    pi = ((double)(4*circlePoints)/(squarePoints));
    printf("Pi estimation: %f\n",pi);
    printf("Completed with %d threads\n",THREAD_NUM);
    
}