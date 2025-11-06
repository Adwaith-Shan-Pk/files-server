#include <stdio.h>

int main() {
    int nb, np, i, j;
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    int block[nb], block_copy1[nb], block_copy2[nb], block_copy3[nb];
    printf("Enter size of each block:\n");
    for (i = 0; i < nb; i++) {
        scanf("%d", &block[i]);
        block_copy1[i] = block[i];
        block_copy2[i] = block[i];
        block_copy3[i] = block[i];
    }

    printf("Enter number of processes: ");
    scanf("%d", &np);
    int process[np];
    printf("Enter size of each process:\n");
    for (i = 0; i < np; i++)
        scanf("%d", &process[i]);

    int allocation[np];
    for (i = 0; i < np; i++)
        allocation[i] = -1;

    // First Fit
    for (i = 0; i < np; i++) {
        for (j = 0; j < nb; j++) {
            if (block_copy1[j] >= process[i]) {
                allocation[i] = j;
                block_copy1[j] -= process[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }

    for (i = 0; i < np; i++)
        allocation[i] = -1;

    // Best Fit
    for (i = 0; i < np; i++) {
        int bestIdx = -1;
        for (j = 0; j < nb; j++) {
            if (block_copy2[j] >= process[i]) {
                if (bestIdx == -1 || block_copy2[j] < block_copy2[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            block_copy2[bestIdx] -= process[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }

    for (i = 0; i < np; i++)
        allocation[i] = -1;

    // Worst Fit
    for (i = 0; i < np; i++) {
        int worstIdx = -1;
        for (j = 0; j < nb; j++) {
            if (block_copy3[j] >= process[i]) {
                if (worstIdx == -1 || block_copy3[j] > block_copy3[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            block_copy3[worstIdx] -= process[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("Process %d -> Block %d\n", i + 1, allocation[i] + 1);
        else
            printf("Process %d -> Not Allocated\n", i + 1);
    }

    return 0;
}
