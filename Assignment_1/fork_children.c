#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

/*
Multiples of 5 n%5 =0 [n is divisible by 5] 
1)	ChildB: Computes the sum of all the numbers in an array. Should wait for its ChildE to terminate before exiting.
2)	ChildC: Counts the number of multiples of 5 in this array.
3)	ChildD: Counts the number of multiples of 7 in this array. 
4)	ChildE: Computes the average of all numbers in this array. 
5)	Parent: Prints the results of the computations of all its immediate children. s Note: that the children should just “pass” the results of their computations to the Parent process
Parent would need to print out the results for  Child B, C, D
*/

int main(void)
{

  //Variable Declarations

  //The array 
  int arr[] = {9, 6, 10, 5, 2, 14, 2,5,6,2, 7, 8, 7, 14, 3, 10, 1, 2, 12, 3};

  //Integers
  int iTotal = 0;
  int iFiveMCount = 0;
  int iSevenMCount = 0;
  float iAverage = 0;
  int iAmount = sizeof(arr)/sizeof(arr[0]);
  pid_t pidC = 0;
  pid_t pidD = 0;

    printf("Parent Process %d just started! \n", getpid());
     pid_t pidB = fork();
  if (pidB == 0) // Parent creates Child B; Child B Enters
  {
     printf("[%d]: Forked process %d \n", getppid(), getpid());
    //Child E
    pid_t pid = fork(); //Child B creates Child E
   
   wait(NULL); //Child B waits for Child E 
    if (pid == 0)       //Child E enters
    {

    printf("[%d]: Forked process %d \n", getppid(), getpid());

      // Child E Computes the average of all the numbers in the arrays
      iTotal = 0;
      for (int i = 0; i < iAmount; i++)
      {                   // Child C loops through and calculates the total.
        iTotal += arr[i]; //Adds the total
      }
      //Computes the average
      iAverage = (float)iTotal / iAmount;
      //Print the average value
      printf("[%d]: Average: %f \n", getpid(), iAverage);
      // Terminate E
      exit(0);
    }
    //Child B continues
    for (int j = 0; j < iAmount; j++)
    { // Child B loops through and calculates the total.
      iTotal += arr[j];
    }
    //Terminate B and pass it's value to the Parent
    exit(iTotal);
  }
  else
  {                  // The Parent Enters
   pidC = fork(); 
    if (pidC  == 0) // Parent Creates Child C; C Enters
    {
        printf("[%d]: Forked process %d \n",  getppid(), getpid());
      // Counts the number of multiples of 5 in the array
      for (int k = 0; k < iAmount; k++)
      {                      // Child C loops through and calculates the total.
        if (arr[k] % 5 == 0) // Checks if the value is divisible by 5
        {
          iFiveMCount += 1;
        }
      }
        //Terminate C and pass it's value to the Parent
        exit(iFiveMCount);
      }
       pidD = fork();
      if (pidD == 0) // Parent Creates Child D;  D Enters
      {
          printf("[%d]: Forked process %d \n",  getppid(), getpid());
        // Counts the number of multiples of 7 in the array
        for (int l = 0; l < iAmount; l++)
        {                      // Child D loops through and calculates the total.
          if (arr[l] % 7 == 0) // Checks if  the value is divisible by 7
          {
            iSevenMCount += 1;
          }
        }
        //Terminate D and Pass it's value to Parent
        exit(iSevenMCount);
      }
    }

    //Before print
    int cpidTotal = wait(&iTotal);
    int cpidFiveCount =  wait(&iFiveMCount);
    int cpidSevenCount = wait(&iSevenMCount);
    //Print out all of the values
   if(pidB == cpidTotal){
    printf("[%d]: Sum: %d \n",getpid(), WEXITSTATUS(iTotal));
   }
   else if(pidB == cpidFiveCount)
   {
     printf("[%d]: Sum: %d \n", getpid(), WEXITSTATUS(iFiveMCount));
   }else if(pidB == cpidSevenCount){
    printf("[%d]: Sum: %d \n", getpid(), WEXITSTATUS(iSevenMCount));
   }

     if(pidC== cpidTotal){
   printf("[%d]: Multiples of 5: %d \n",getpid(),  WEXITSTATUS(iTotal));
   }else if(pidC == cpidFiveCount)
     {
       printf("[%d]: Multiples of 5: %d \n",getpid(),  WEXITSTATUS(iFiveMCount));
   }
   else if(pidC == cpidSevenCount){
     printf("[%d]: Multiples of 5: %d \n",getpid(),  WEXITSTATUS(iSevenMCount));
   }

     if(pidD== cpidTotal){
    printf("[%d]: Multiples of 7: %d \n",getpid(),  WEXITSTATUS(iTotal)); 
   }else if(pidD == cpidFiveCount)
     {
      printf("[%d]: Multiples of 7: %d \n",getpid(),  WEXITSTATUS(iFiveMCount)); 
   }
   else if(pidD == cpidSevenCount){
    printf("[%d]: Multiples of 7: %d \n", getpid(), WEXITSTATUS(iSevenMCount)); 
   }
  return 0;
}