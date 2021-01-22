

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

int main(void) {

//Variable Declarations

//The array CHANGE TO ACCEPT AS ARGUMENT
int arr[] = {13, 5, 1, 13, 6, 6, 3, 7, 13, 3, 7, 2, 8, 15, 3, 12, 10, 7, 13, 10};

//Integers
int iTotal = 0;
int iFiveMCount= 0;
int iSevenMCount = 0;
float iAverage  = 0;
int iAmount = sizeof(arr);
int status; 
 
if (fork() == 0) // Parent creates Child B; Child B Enters
{
  //Child E
pid_t pid = fork(); //Child B creates Child E
if(pid==0)//Child E enters
{
//Child B Waits for E
//waitpid(pid, NULL, 0);

// Child E Computes the average of all the numbers in the arrays
iTotal =0;
for (int i = 0;i<iAmount;i++){ // Child C loops through and calculates the total.
iTotal  += arr[i]; //Adds the total
}
//Computes the average
iAverage = (float) iTotal/iAmount;
//Print the average value
printf("Average: %f", iAverage);
// Terminate E
exit (0);
}
//Child B continues 
for(int j = 0;j<iAmount;j++){ // Child B loops through and calculates the total.
 iTotal  +=  arr[j];
}
//Terminate B and pass it's value to the Parent 
exit (iTotal); 
}
else{   // The Parent Enters
if(fork() == 0)// Parent Creates Child C; C Enters
{
// Counts the number of multiples of 5 in the array
for(int k = 0;k< iAmount;k++){ // Child C loops through and calculates the total.
if(arr[k] % 5 == 0)// Checks if the value is divisible by 5
{
 iFiveMCount +=1;
}
// //Terminate C and pass it's value to the Parent
exit (iFiveMCount);
}
if(fork() == 0)// Parent Creates Child D;  D Enters
{
// Counts the number of multiples of 7 in the array
for(int l = 0; l< iAmount ;l++){ // Child D loops through and calculates the total.
if(arr[l] % 7 == 0)// Checks if  the value is divisible by 7
 {
 iSevenMCount +=1;
 }
}
 //Terminate D and Pass it's value to Parent
exit (iSevenMCount); 
}
}

//Before print 
wait(iTotal);
wait(iFiveMCount);
wait(iSevenMCount)
//Print out all of the values
printf("Sum: [%d] \n", iTotal);
printf("Multiples of 5: [%d] \n", iFiveMCount);
printf("Multiples of 7: [%d] \n", iSevenMCount);
}
  return 0;
}

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

int main(void) {

//Variable Declarations

//The array CHANGE TO ACCEPT AS ARGUMENT
int arr[] = {13, 5, 1, 13, 6, 6, 3, 7, 13, 3, 7, 2, 8, 15, 3, 12, 10, 7, 13, 10};

//Integers
int iTotal = 0;
int iFiveMCount= 0;
int iSevenMCount = 0;
float iAverage  = 0;
int iAmount = sizeof(arr);
int status; 
 
if (fork() == 0) // Parent creates Child B; Child B Enters
{
  //Child E
pid_t pid = fork(); //Child B creates Child E
if(pid==0)//Child E enters
{
//Child B Waits for E
//waitpid(pid, NULL, 0);

// Child E Computes the average of all the numbers in the arrays
iTotal =0;
for (int i = 0;i<iAmount;i++){ // Child C loops through and calculates the total.
iTotal  += arr[i]; //Adds the total
}
//Computes the average
iAverage = (float) iTotal/iAmount;
//Print the average value
printf("Average: %f", iAverage);
// Terminate E
exit (0);
}
//Child B continues 
for(int j = 0;j<iAmount;j++){ // Child B loops through and calculates the total.
 iTotal  +=  arr[j];
}
//Terminate B and pass it's value to the Parent 
exit (iTotal); 
}
else{   // The Parent Enters
if(fork() == 0)// Parent Creates Child C; C Enters
{
// Counts the number of multiples of 5 in the array
for(int k = 0;k< iAmount;k++){ // Child C loops through and calculates the total.
if(arr[k] % 5 == 0)// Checks if the value is divisible by 5
{
 iFiveMCount +=1;
}
// //Terminate C and pass it's value to the Parent
exit (iFiveMCount);
}
if(fork() == 0)// Parent Creates Child D;  D Enters
{
// Counts the number of multiples of 7 in the array
for(int l = 0; l< iAmount ;l++){ // Child D loops through and calculates the total.
if(arr[l] % 7 == 0)// Checks if  the value is divisible by 7
 {
 iSevenMCount +=1;
 }
}
 //Terminate D and Pass it's value to Parent
exit (iSevenMCount); 
}
}

//Before print 
wait(iTotal);
wait(iFiveMCount);
wait(iSevenMCount)
//Print out all of the values
printf("Sum: [%d] \n", iTotal);
printf("Multiples of 5: [%d] \n", iFiveMCount);
printf("Multiples of 7: [%d] \n", iSevenMCount);
}
  return 0;
}