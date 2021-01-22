#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

//Global Array of numbers
int iSizeOfArrOne = 0; //The size of array one
int iSizeOfArrTwo = 0; //The size of array two
int iFillCount = 0;
int *arrOne;
int *arrTwo;


void *fill(void *arrSize)
{
    long x = rand()%100 +1;

    long y = rand()%100 +1;
    
    if(iFillCount == 0){ // Then fill the first array
    //Loop through the array and add the random value 
    for(int l = 0; l<iSizeOfArrOne; l++)
    {
        arrOne[l] = x;
        x = rand()%100 +1;
    }
    iFillCount = 1;
    }
    else{ //Handle the seccond array
        for(int m = 0; m<iSizeOfArrTwo; m++)
    {
        arrTwo[m] = y;
        y = rand()%100 +1;
    } 
    }
    return NULL;
}

/*
o    A	separate	thread	should be	spawned to	compute	the	sum of	the	numbers	in	each	array.
o Both	of	these threads	should	execute	the	same	function	sum() but	work	on	a	different	array and	they	should	
both	return to	master-thread the	result	of	these summations.
*/

void *sum(void *arrChoice)
{
    int iArrOneSum = 0;
    int iArrTwoSum = 0;

    if(arrChoice == 0) //Handle the first array
    {
        for(int n =0; n< iSizeOfArrOne; n++)
        {
            iArrOneSum += arrOne[n];
        }
        return (int *)iArrOneSum;
    }else{ //Handle the seccond array
          for(int p =0; p< iSizeOfArrTwo; p++)
        {
            iArrTwoSum += arrTwo[p];
        }
        return  (int *)iArrTwoSum;
    }
}

/*
o Master thread should	spawn	two more thread	that	will	be computing	and	returning	to	the	master	thread	the	
minimum of	 each	 of	 the	two	 arrays. The	 master	 thread	 should	 be	 printing the	 absolute	 minimum of	 the	
numbers	in	both	arrays. A	separate	thread	should be	spawned to	compute	the	min of	the	numbers	in	each	array.
o Both	of	these threads	execute	the	thread-function	minimum() and	it	should	return to	main the	corresponding	
minimum number for	each	array.  

*/

void *minimum(void *arrChoice)
{
    int iArrOneMin = 0;
    int iArrTwoMin = 0;
    
    if(arrChoice == 0) //Handle the first array
    {
        iArrOneMin = arrOne[0];
        for(int q =0; q< iSizeOfArrOne; q++)
        {
            if(arrOne[q] < iArrOneMin)
          {
            iArrOneMin = arrOne[q];
          }
        }
       return (void *)iArrOneMin; 
    }else{ //Handle the seccond array
        iArrTwoMin = arrTwo[0];
        for(int r =0; r< iSizeOfArrTwo; r++)
       {
            if(arrTwo[r] < iArrTwoMin)
        {
            iArrTwoMin = arrTwo[r];
        }
       return (void *)iArrTwoMin; 
      }
}
return NULL;
}

int main(int argc, char *argv[])
{
     
     //input-validation for two numbers
//Command-line argument is provided / No command-line argument
    if(argc != 3){
        fprintf(stderr, "usage:./stats <integer value> <integer value>\n");
        return -1;
    }
    
    //N option is in the valid range
    if((atoi(argv[1])==0)||(atoi(argv[2])==0)){
        fprintf(stderr, "Your seccond and third Argument must be an int value");
        return -1;
    }
    
    
      srand(time(0));
      

    //Will use arrays and run them in a for loop that way but there is no order. The goal is to have threads in the rand; sum; and min 
    //posible run at the same time. Hopefully this is what she meant. Might need to uuse different forks.
    
    iSizeOfArrOne = atoi(argv[ 1 ]); /*argv[ 0 ] is the executable's name */
    iSizeOfArrTwo = atoi(argv[ 2 ]);
    arrOne = malloc(iSizeOfArrOne * sizeof *arrOne); /* create an array of size `size` */
    arrTwo = malloc(iSizeOfArrTwo * sizeof *arrTwo);
    
    if ((arrOne)&&(arrTwo)) { 
   
   
    pthread_t threads_rand[2];
    pthread_t threads_sum[2];
    pthread_t threads_min[2];
    
    
    /*
    pthread_t threads_rand_arrOne;
    pthread_t threads_rand_arrTwo;
    
    pthread_t threads_sum_arrOne;
    pthread_t threads_sum_arrOne;
    
    pthread_t threads_min_arrOne;
    pthread_t threads_min_arrOne;
    pthread_t threads_rand_arrOne;
*/

    
    void *iSumArrOne = NULL;
    void *iSumArrTwo = NULL;
    void *iMinArrOne = NULL;
    void *iMinArrTwo = NULL;
    int iAverage =0;

    
    int iSumCount = 0;
    int iMinCount = 0;

    int iArrChoiceOne = 0;
    int iArrChoiceTwo = 1;
    
   uintptr_t iSum =0;
   uintptr_t iSumTwo =0;

   //fill() method - To populate them with random values
    for(int i = 0; i< 2; i++)
    {
        if(iFillCount ==0) //Fill the first array
        {
       printf("Array Ones size is %d\n", iSizeOfArrOne);
       pthread_create(&threads_rand[i], NULL,fill,  (void *) iSizeOfArrOne); 
       pthread_join(threads_rand[i], NULL);
        //Display Array ones elements
         for(int s =0;s<iSizeOfArrOne;s++)
         {
        printf("Array One Element: %d at index: %d\n", arrOne[s], s);
         }
        }else //Fill the seccond array
        {
         printf("\nArray Twos size is %d\n", iSizeOfArrTwo);
         pthread_create(&threads_rand[i], NULL,fill, (void *) iSizeOfArrTwo); 
                pthread_join(threads_rand[i], NULL);
         for(int t =0; t<iSizeOfArrTwo; t++)
         {
        printf("Array Two Element: %d at index: %d\n", arrTwo[t], t);
         }
         printf("\n");
        }
    }
    
    
    printf("Calculating the sum:\n");
    //Sum() method - To calculate the sum of the arrays
    for(int j = 0; j< 2; j++)
    {
        
         if(iSumCount == 0) //Will calculate the first array 
         {
      pthread_create(&threads_sum[j], NULL,sum, (void *) iArrChoiceOne); 
         pthread_join(threads_sum[j], (void *)&iSumArrOne);
        iSum = (uintptr_t)iSumArrOne;
       printf("The sum of Array One is %d\n", iSum);
         iSumCount =1;
         }
         else{ //Will calculate the seccond array
            pthread_create(&threads_sum[j], NULL,sum, (void *) iArrChoiceTwo);
          pthread_join(threads_sum[j], (void *)&iSumArrTwo);
          iSumTwo = (uintptr_t)iSumArrTwo;        
         printf("The sum of Array Two is %d\n\n", iSumTwo);
         }
    }
 
     printf("Calculating the min:\n");
    //Minimum() - To calculate the min of the arrays
        for(int k = 0; k< 2; k++)
    {
         if(iMinCount == 0) //Will calculate the first array 
         {
                     pthread_create(&threads_min[k], NULL,minimum,(void *) iArrChoiceOne); 
                     pthread_join(threads_min[k],(void *) &iMinArrOne);
                     uintptr_t iMin = (uintptr_t)iMinArrOne;        
              printf("The min of Array One is %d\n", iMin);
            iMinCount = 1;
         }
         else{ //Will calculate the seccond array
                     pthread_create(&threads_min[k], NULL,minimum, (void * )iArrChoiceTwo); 
                     pthread_join(threads_min[k], (void *)&iMinArrTwo);
                     uintptr_t iMinTwo = (uintptr_t)iMinArrTwo;                      
                    printf("The min of Array Two is %d\n\n", iMinTwo);
         }
    }

   //Need to compute the average last
int iTheSum = iSum + iSumTwo;
 iAverage = iTheSum/2;

    printf("Calculating the Average:\n");
    printf("The Average is: %d\n\n ", iAverage);
    
    free(arrOne);
    free(arrTwo);
   pthread_exit(0);
   
    } else{
 fprintf(stderr, "Memory could not be allocated for your two arrays");

    }
    return 0;
}
