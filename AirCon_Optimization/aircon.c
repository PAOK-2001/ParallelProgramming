// Pablo Agustín Ortega Kral A00344664

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <omp.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>
// Constants for room parameters
#define ROOM_ROWS 6
#define ROOM_COLUMNS 7
#define TIME_SIZE 11
// Temperature constant
#define HIGH 100
#define LOW 60
// N amount of time between measurments
#define SAMPLE_RATE 80000
// Diferential Eq. constants
#define GAMMA 0.00625 //using gammma provided by python implementation

char temp_mat[ROOM_ROWS][ROOM_COLUMNS];
int heat_map[TIME_SIZE][ROOM_COLUMNS][ROOM_ROWS];

void init_matrix(){
    for (int row = 0; row < ROOM_ROWS; row++){
        for(int col = 0; col < ROOM_ROWS; col++){
            heat_map[0][row][col] = INT_MIN;
        }
    }
}

void read_from_CSV(){
    char buffer[1024];
    FILE *roomLayout = fopen("provided_layout.csv", "r");
    if(roomLayout == NULL){
        printf("Could not read CSV\n");
        return ;
    }
    int row = 0;
    printf("Room read from CSV: \n");
    while(fgets(buffer,sizeof(buffer),roomLayout)){
        printf("%s",buffer);
        for(int i = 0; i < 2*ROOM_COLUMNS-1; i++){
            char readVal = buffer[i];
            if(readVal != 44){// Compare against ASCII code for colon , to determine id valid number
                temp_mat[row][i/2] = buffer[i];
            }
        }
        row++;// Iterate rows
    }
}
// Check if room is complete
void check_room_complete(){
    bool complete = false;
    while(!complete){
        complete = true; // Assume room travesal is complete
        for (int row = 0; row < ROOM_ROWS; row++){
            for(int col = 0; col < ROOM_COLUMNS; col++){
                if(heat_map[0][row][col] == INT_MIN){
                    complete = false; // Disprove if an intialized value is found
                }
            }
        }
    }
}

void *assign_temp(void * THREAD_NUM){
    // Place robot in random coordinates
    int xcord = rand() % ROOM_ROWS;
    int ycord = rand() % ROOM_COLUMNS;
    // While loop to indicate robot movement
    while(1){
        char relativeTemp = temp_mat[xcord][ycord];
        if(relativeTemp == 'C'){
            heat_map[0][xcord][ycord] = rand() %(LOW +1);
        }else{
            heat_map[0][xcord][ycord] = rand() %(HIGH -(LOW-1)) + LOW;
        }
        //Move robot to next position
        int cardinal_movement = rand()%4; // 0 down, 1 right, 2 left, 3 up
        switch (cardinal_movement){
            case 0:{
                //Check if can move
                if(xcord-1 >= 0){
                    xcord--;
                }
                break;
            }
            case 1:{
                //Check if can move
                if(ycord+1 < ROOM_COLUMNS){
                    ycord++;
                }
                break;
            }
            case 2:{
                //Check if can move
                if(ycord-1 >= 0){
                    ycord--;
                }
                break;
            }
            case 3:{
                //Check if can move
                if(xcord+1 < ROOM_ROWS){
                    xcord++;
                }
                break;
            }
            default:
                break;
        }
        //Delay threads by the SAMPLE_RATE to simulate periodic measurments
        clock_t start_time = clock();
        while (clock() < start_time + SAMPLE_RATE);
    }
}

void differential_heat_eq(){
    int i,j,k;
    for (k = 0; k < TIME_SIZE; k++){
        #pragma omp parallel for private(i,j) shared(heat_map)
        for (i = 0; i<ROOM_ROWS; i++){
            for (j = 0; j < ROOM_COLUMNS;j++){
                if (i == 0 || j == 0){ //Set boundaries for initial conditions to avoid indexing out of bounds
                    heat_map[k + 1][i][j] = heat_map[k][i][j];
                }else{
                    heat_map[k + 1][i][j] = 0.02 * (heat_map[k][i+1][j] + heat_map[k][i-1][j] + heat_map[k][i][j+1] + heat_map[k][i][j-1] - 4*heat_map[k][i][j]) + heat_map[k][i][j];
                }
        }
    }
    }
}



int main(int argc, char* argv[]){ 
    read_from_CSV();
    init_matrix();
    const int NUMBER_OF_ROBOTS = atoi(argv[1]);
    omp_set_num_threads(NUMBER_OF_ROBOTS);
    int returnCode;
    //Create array to store threads in memory
    pthread_t robots[NUMBER_OF_ROBOTS];
    for (int i = 0; i < NUMBER_OF_ROBOTS; i++){
        returnCode = pthread_create(&robots[i],NULL,&assign_temp, (void*) &(NUMBER_OF_ROBOTS));
    }
    // Use main, as a master thread to verify if matrix has been covered fully
    check_room_complete();
     for (int j = 0; j < NUMBER_OF_ROBOTS; j++){
        returnCode = pthread_cancel(robots[j]);
    }
    printf("Initial measurment T = O \n");
     for (int row = 0; row < ROOM_ROWS; row++){
        for(int col = 0; col < ROOM_COLUMNS; col++){
            printf("%d,",heat_map[0][row][col]);
        }
        printf("\n");
    }
    differential_heat_eq();
    printf("Estimated value T = 1O \n");
     for (int row = 0; row < ROOM_ROWS; row++){
        for(int col = 0; col < ROOM_COLUMNS; col++){
            printf("%d,",heat_map[10][row][col]);
        }
        printf("\n");
    }
}