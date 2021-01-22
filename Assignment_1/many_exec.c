


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>



 int main(int argc, char **argv){
     
     //The parent creates the four children

     if(argc != 4) //If you do not have four arguements
     {
printf("\nError: You did enter the correct amount of arguements.\n");
exit(0);
     }
    
     if(access(argv[1], F_OK)==-1) //Cannot access the file
     {
       printf("\nError: Please enter a proper file path\n");
        exit(0);
     }
    
    
     if(atoi(argv[2])==0)//input is not an int
{
   printf("\nError: The seccond argument should be an int.\n");
   exit(0);
}

     //Arrays
     char *cl_argvCat[] = {"/bin/cat","/etc/passwd",NULL};
     char *cl_argvWc[] = {"/usr/bin/wc", "-lw",argv[1], NULL};
     char *cl_argvHead[] = {"/usr/bin/head","-n",argv[2],argv[1],NULL};
     char *cl_argvGrep[] = {"/bin/grep","-n",argv[3],argv[1],NULL};


     if(fork()==0) // Parent creates Child A
     {
    
       printf("\nResults of cat command:\n");
         //Use an execv call to cat command to print contents of the /etc/passwd file on machine
         execv(cl_argvCat[0],cl_argvCat);
     }
     wait(NULL);
     if(fork()==0) // Parent creates Child B
     {
         
    printf("\nResults of wc command:\n");
     //Use wc command with the options -lw of a user provided file
     execv(cl_argvWc[0],cl_argvWc);
     
     }
     wait(NULL);
     if(fork()==0) // Parent creates Child C
     {
          printf("\nResults of head command:\n");

         //Use the head command to print the most N lines of user-provided file.
        execv(cl_argvHead[0],cl_argvHead);

      }
      wait(NULL);
       if(fork()==0) // Parent creates Child D
     {
          printf("\nResults of grep command:\n");

         //Use the grep command with -n optino , to search the contents of the user-provided file for a keyword and return the exact lines where this string is found
execv(cl_argvGrep[0],cl_argvGrep);
     }

else{
wait(NULL);
 printf("\nParent is out! Bye!\n");
     }
 return 0;  
 }
