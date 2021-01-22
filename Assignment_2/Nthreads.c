
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
int numbers[]={2,6,32,11,12,50,55,64,4,100};
void *drawNumber(void *threadnumb)
{
    long x = rand()%10;
    usleep(rand()% 1000000);
    uintptr_t nThreads = (uintptr_t)threadnumb;
    printf("Thread %d : drew  %d \n", nThreads, numbers[x]);
    return NULL;
}

int main(int argc, char *argv[])
{

    //Error handling
    //1 Command-line argument is provided / No command-line argument
    if(argc != 2){
        fprintf(stderr, "usage:./Nthreads <integer value>\n");
        return -1;
    }
   
    //N option is in the valid range
    if((atoi(argv[1]) <0)||(atoi(argv[1])==0) || (atoi(argv[1])>=10)){
        fprintf(stderr, "Your seccond Argument must be in the following range from 1 to 9");
        return -1;
    }
   
 
    int NUM_THREADS = atoi(argv[1]);
    pthread_t threads[NUM_THREADS];
    void *status;
    srand(time(0));
    //Loop through and create the threads with count specified; (void *)i?
   
    for(int i =0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL,drawNumber, (void *)(intptr_t)i);
        pthread_join(threads[i], &status);
    }
   
    printf("All threads completed!");
    pthread_exit(0);
   

    return 0;
}