/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h> 
#include <stdint.h>
#include <unistd.h>

sem_t full;
sem_t empty;


//Global variable of how many people are in the store
long sum = 0;



//The Store method -  Called every time a new customer thread shows up. 
//Threads can enter the store and leave the store 

void *Shopping(void *arg){
    int x = *(int *) arg;
    sem_wait(&full);
    sum = sum + 1;
    printf("Customer #%d: I'm in!(current-customers-in: %ld)\n", x, sum);

    usleep(rand() %500000);
    
   sum = sum -1;
   
   sem_post(&empty);
    printf("Customer #%d: left!(current-customers-in: %ld)\n", x, sum);
}




int main(int argc, char * argv[]){ //Two command line arguements: the max and the numb of customers
    int MAX_NUMB = atoi(argv[1]);
    int CUST_COUNT = atoi(argv[2]);
    pthread_t threads[CUST_COUNT];
    sem_init(&full, 0, 0); 
    sem_init(&empty, 0, MAX_NUMB);

     int *param[CUST_COUNT];

    
    //Have a loop that will be sending these threads into the method

    for(int i = 0; i<CUST_COUNT; i++){
        //Create the threads 
         param[i] = malloc(sizeof(int));
        *param[i]= i+1;
        sem_wait(&empty);
       pthread_create(&threads[i], NULL , Shopping, (void *)param[i]);
        sem_post(&full);
    }
    
    for(int i =0; i<CUST_COUNT; i++){
    pthread_join(threads[i],NULL);
    }
    
   
    //Main thread waits for the threads then states 
    printf("Store closed for the day! We open again tomorrow at 9am!");
     pthread_exit(NULL);
    
    sem_destroy(&full);
    sem_destroy(&empty);


}

