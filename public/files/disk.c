#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i, j, head, total = 0, temp;
    printf("Enter number of disk requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter the disk requests sequence: ");
    for (i = 0; i < n; i++)
        scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);

    // FCFS
    int fcfs_total = 0;
    int curr = head;
    for (i = 0; i < n; i++) {
        fcfs_total += abs(req[i] - curr);
        curr = req[i];
    }
    printf("\n===== FCFS Disk Scheduling =====\n");
    printf("Sequence: %d ", head);
    curr = head;
    for (i = 0; i < n; i++) {
        printf("-> %d ", req[i]);
        curr = req[i];
    }
    printf("\nTotal Head Movement: %d\n\n", fcfs_total);

    // SCAN
    int disk_size;
    printf("Enter total disk size (e.g., 200): ");
    scanf("%d", &disk_size);

    int scan_req[n + 2];
    for (i = 0; i < n; i++)
        scan_req[i] = req[i];
    scan_req[n] = head;
    scan_req[n + 1] = 0; // assuming movement towards 0 first

    int scan_total = 0;
    for (i = 0; i < n + 2; i++) {
        for (j = i + 1; j < n + 2; j++) {
            if (scan_req[i] > scan_req[j]) {
                temp = scan_req[i];
                scan_req[i] = scan_req[j];
                scan_req[j] = temp;
            }
        }
    }

    int pos;
    for (i = 0; i < n + 2; i++) {
        if (scan_req[i] == head) {
            pos = i;
            break;
        }
    }

    printf("===== SCAN Disk Scheduling =====\n");
    printf("Sequence: ");
    for (i = pos; i >= 0; i--)
        printf("%d ", scan_req[i]);
    for (i = pos + 1; i < n + 2; i++)
        printf("%d ", scan_req[i]);

    for (i = pos; i > 0; i--)
        scan_total += abs(scan_req[i] - scan_req[i - 1]);
    scan_total += abs(scan_req[0] - scan_req[pos + 1]);
    for (i = pos + 1; i < n + 1; i++)
        scan_total += abs(scan_req[i + 1] - scan_req[i]);

    printf("\nTotal Head Movement: %d\n\n", scan_total);

    // C-SCAN
    int cscan_req[n + 2];
    for (i = 0; i < n; i++)
        cscan_req[i] = req[i];
    cscan_req[n] = head;
    cscan_req[n + 1] = 0;

    for (i = 0; i < n + 2; i++) {
        for (j = i + 1; j < n + 2; j++) {
            if (cscan_req[i] > cscan_req[j]) {
                temp = cscan_req[i];
                cscan_req[i] = cscan_req[j];
                cscan_req[j] = temp;
            }
        }
    }

    for (i = 0; i < n + 2; i++) {
        if (cscan_req[i] == head) {
            pos = i;
            break;
        }
    }

    int cscan_total = 0;
    printf("===== C-SCAN Disk Scheduling =====\n");
    printf("Sequence: ");
    for (i = pos; i < n + 2; i++)
        printf("%d ", cscan_req[i]);
    for (i = 0; i < pos; i++)
        printf("%d ", cscan_req[i]);

    for (i = pos; i < n + 1; i++)
        cscan_total += abs(cscan_req[i + 1] - cscan_req[i]);
    cscan_total += abs(disk_size - 1 - cscan_req[n + 1]);
    cscan_total += abs(disk_size - 1 - cscan_req[0]);
    for (i = 0; i < pos - 1; i++)
        cscan_total += abs(cscan_req[i + 1] - cscan_req[i]);

    printf("\nTotal Head Movement: %d\n", cscan_total);

    return 0;
}
