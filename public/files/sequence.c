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


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Structure to represent a disk block
struct block {
    int bno;  // Block number (not strictly needed but helpful for tracking)
    int flag; // 0 for free, 1 for allocated
};

// Global disk array and size
#define DISK_SIZE 100
struct block b[DISK_SIZE];

void initialize_disk() {
    for (int i = 0; i < DISK_SIZE; i++) {
        b[i].bno = i;
        b[i].flag = 0; // All blocks are initially free
    }
}

void sequential_allocation() {
    int num_files;
    printf("Enter the number of files: ");
    if (scanf("%d", &num_files) != 1) return;

    int p[num_files]; // Array to store memory requirement (length) of each file

    // Step 2 & 3: Get number of files and memory requirement
    for (int i = 0; i < num_files; i++) {
        printf("Enter the memory requirement (blocks) for file %d: ", i + 1);
        if (scanf("%d", &p[i]) != 1) return;
    }

    // k[i][j] stores the block number of the j-th block of file i.
    // Assuming max file length is DISK_SIZE for simplicity.
    int k[num_files][DISK_SIZE];
    
    // Seed the random number generator for random starting block selection
    srand(time(NULL));

    printf("\n--- Allocation Results ---\n");
    printf("File No.\tLength\tBlocks Allocated\n");
    
    // Step 4: Allocate locations to each file
    for (int i = 0; i < num_files; i++) {
        int s1; // Starting location
        int allocated = 0;
        int max_attempts = DISK_SIZE * 2; // Limit attempts to prevent infinite loop

        for (int attempt = 0; attempt < max_attempts; attempt++) {
            // Step 4.a). Randomly select a location from available location s1
            s1 = rand() % DISK_SIZE; 
            
            // Check if selected location is valid and can accommodate the file
            if (s1 + p[i] <= DISK_SIZE) { 
                
                // Check whether the required locations are free from the selected location.
                int count = 0; 
                
                // Check the first block
                if (b[s1].flag == 0) { 
                    for (int j = s1; j < s1 + p[i]; j++) {
                        if ((b[j].flag) == 0) {
                            count++;
                        } else {
                            // Non-contiguous free space found, break and try again from a new random start
                            break; 
                        }
                    }
                    
                    // Found a contiguous free block sequence of the required length
                    if (count == p[i]) {
                        // Step 4.b): Allocate and set flag=1 to the allocated locations.
                        int j = 0;
                        for (int s = s1; s < (s1 + p[i]); s++) {
                            k[i][j] = s; 
                            j = j + 1; 
                            b[s].bno = s;
                            b[s].flag = 1; // Mark as allocated
                        }
                        allocated = 1;
                        break; // Allocation successful, move to the next file
                    }
                }
            }
        }

        // Step 5: Print the results
        printf("%d\t\t%d\t", i + 1, p[i]);
        if (allocated) {
            for (int j = 0; j < p[i]; j++) {
                printf("%d%s", k[i][j], (j < p[i] - 1) ? ", " : "");
            }
            printf("\n");
        } else {
            printf("NOT ALLOCATED (No contiguous block found)\n");
        }
    }
}

int main() {
    // Step 1: Start the program.
    initialize_disk();
    sequential_allocation(); 
    // Step 6: Stop the program (implicit return 0)
    return 0;
}
