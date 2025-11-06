Step 1: Start the program.
Step 2: Get the number of files.
Step 3: Get the memory requirement of each file.
Step 4: Allocate the required locations to each in sequential order  a). Randomly select a location from available location s1= random(100);

a) Check whether the required locations are free from the selected location.

if(b[s1].flag==0)
{
for(j=s1;j<s1+p[i];j++)
{
if((b[j].flag)==0)count++;
}
if(count==p[i]) break;
}


b) Allocate and set flag=1 to the allocated locations. 

for(s=s1;s<(s1+p[i]);s++)
{
k[i][j]=s; j=j+1; 
b[s].bno=s;
b[s].flag=1;
}

Step 5: Print the results file no, length, Blocks allocated. 

Step 6: Stop the program


Q1. Write a program to implement sequential file allocation method
#include <stdio.h>
//Write the program here

