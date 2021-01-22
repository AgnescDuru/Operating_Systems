
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>
#include <stdint.h>
#include <unistd.h>


sem_t sem1;
sem_t sem2;
sem_t sem3;
sem_t sem4;
sem_t sem5;
sem_t sem6;


//For thread A
void * Thread1Message (void *arg)
{ 
 sem_wait (&sem1);		//Aquire semaphore
  printf ("Hang in ");
  sem_post (&sem2);		//release semaphore
 
 sem_wait(&sem6); //release semaphore
  printf ("here!\n");

}

//For thread B
void * Thread2Message (void *arg)
{
  //Thread B - Print almost
  //Delay
  sem_wait (&sem5);		//Aquire Semaphore 
  printf ("almost ");
  // printf("\nThread %d is here \n", x);
  sem_post (&sem6);		//Release Semaphore

}

//For thread C
void * Thread3Message (void *arg)
{
      //Delay
  sem_wait (&sem4);		//Aquire Semaphore 
  printf ("is ");
  //printf("\nThread %d is here \n", x);
  sem_post (&sem5);		//Release Semaphore
}


//For thread D
void * Thread4Message (void *arg)
{
  sem_wait (&sem2);		//Aquire semaphore
  printf ("there! ");
  // printf("\nThread %d is here \n", x);
  sem_post (&sem3);
  
  sem_wait (&sem3);		//Release semaphore 
  printf ("Summer ");
  //printf("Thread %d is here \n", x);
  sem_post (&sem4);		///Release semaphore
}




int main (int argc, char *argv[])
{
  int NUM_THREADS = 4;
  sem_init (&sem1, 0, 1);
  sem_init (&sem2, 0, 0);
  sem_init (&sem3, 0, 0);
  sem_init (&sem4, 0, 0);
  sem_init (&sem5, 0, 0);
  sem_init (&sem6, 0, 0);

  pthread_t threads[NUM_THREADS];
  int *param[NUM_THREADS];

  printf ("Program started\n");

  //sem_wait(&sem1);
  for (long i = 0; i < NUM_THREADS; i++)
    {
      param[i] = malloc (sizeof (int));
      *param[i] = i + 1;
      

       if (i ==0){
                pthread_create (&threads[i], NULL, Thread1Message, (void *) param[i]);
      usleep (rand () % 50000);
          
      }else if (i ==1){
               pthread_create (&threads[i], NULL, Thread2Message, (void *) param[i]);
     usleep (rand () % 50000);
          
     }else if (i ==2){
               pthread_create (&threads[i], NULL, Thread3Message, (void *) param[i]);
      usleep (rand () % 50000);

      }else if (i ==3){
                pthread_create (&threads[i], NULL, Thread4Message, (void *) param[i]);
      usleep (rand () % 50000);
          
      }
    }
    
    
    //Join the threads
    for(int i =0;i<4;i++){
    pthread_join(threads[i],NULL);
}


  printf ("The End!");
  pthread_exit (NULL);
  sem_destroy (&sem1);
  sem_destroy (&sem2);
  sem_destroy (&sem3);
  sem_destroy (&sem4);
 sem_destroy (&sem5);
  sem_destroy (&sem6);
}
