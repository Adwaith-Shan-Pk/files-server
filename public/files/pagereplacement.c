#include <stdio.h>

int findLRU(int time[], int n) {
    int i, minimum = time[0], pos = 0;
    for (i = 1; i < n; ++i)
        if (time[i] < minimum)
            minimum = time[i], pos = i;
    return pos;
}

int findLFU(int freq[], int n) {
    int i, min = freq[0], pos = 0;
    for (i = 1; i < n; ++i)
        if (freq[i] < min)
            min = freq[i], pos = i;
    return pos;
}

int main() {
    int n, f, i, j, k, pos, count, time[10], freq[10], page[30], frames[10];

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (i = 0; i < n; ++i)
        scanf("%d", &page[i]);
    printf("Enter number of frames: ");
    scanf("%d", &f);

    printf("\n===== FIFO Page Replacement =====\n");
    for (i = 0; i < f; ++i)
        frames[i] = -1;

    int index = 0, pageFaults = 0;
    for (i = 0; i < n; ++i) {
        int flag = 0;
        for (j = 0; j < f; ++j)
            if (frames[j] == page[i])
                flag = 1;
        if (!flag) {
            frames[index] = page[i];
            index = (index + 1) % f;
            pageFaults++;
            printf("Page %2d -> ", page[i]);
            for (k = 0; k < f; ++k)
                if (frames[k] != -1) printf("%2d ", frames[k]); else printf(" - ");
            printf(" | FAULT\n");
        } else {
            printf("Page %2d -> ", page[i]);
            for (k = 0; k < f; ++k)
                if (frames[k] != -1) printf("%2d ", frames[k]); else printf(" - ");
            printf(" | HIT\n");
        }
    }
    printf("Total Page Faults (FIFO): %d\n\n", pageFaults);

    printf("===== LRU Page Replacement =====\n");
    for (i = 0; i < f; ++i)
        frames[i] = -1;
    count = 0;
    pageFaults = 0;

    for (i = 0; i < n; ++i) {
        int flag = 0;
        for (j = 0; j < f; ++j)
            if (frames[j] == page[i]) {
                count++;
                time[j] = count;
                flag = 1;
            }
        if (!flag) {
            int empty = -1;
            for (j = 0; j < f; ++j)
                if (frames[j] == -1)
                    empty = j;
            if (empty != -1) {
                count++;
                frames[empty] = page[i];
                time[empty] = count;
            } else {
                pos = findLRU(time, f);
                count++;
                frames[pos] = page[i];
                time[pos] = count;
            }
            pageFaults++;
            printf("Page %2d -> ", page[i]);
            for (k = 0; k < f; ++k)
                if (frames[k] != -1) printf("%2d ", frames[k]); else printf(" - ");
            printf(" | FAULT\n");
        } else {
            printf("Page %2d -> ", page[i]);
            for (k = 0; k < f; ++k)
                if (frames[k] != -1) printf("%2d ", frames[k]); else printf(" - ");
            printf(" | HIT\n");
        }
    }
    printf("Total Page Faults (LRU): %d\n\n", pageFaults);

    printf("===== LFU Page Replacement =====\n");
    for (i = 0; i < f; ++i) {
        frames[i] = -1;
        freq[i] = 0;
    }
    pageFaults = 0;
    for (i = 0; i < n; ++i) {
        int flag = 0;
        for (j = 0; j < f; ++j)
            if (frames[j] == page[i]) {
                freq[j]++;
                flag = 1;
            }
        if (!flag) {
            int empty = -1;
            for (j = 0; j < f; ++j)
                if (frames[j] == -1)
                    empty = j;
            if (empty != -1) {
                frames[empty] = page[i];
                freq[empty] = 1;
            } else {
                pos = findLFU(freq, f);
                frames[pos] = page[i];
                freq[pos] = 1;
            }
            pageFaults++;
            printf("Page %2d -> ", page[i]);
            for (k = 0; k < f; ++k)
                if (frames[k] != -1) printf("%2d ", frames[k]); else printf(" - ");
            printf(" | FAULT\n");
        } else {
            printf("Page %2d -> ", page[i]);
            for (k = 0; k < f; ++k)
                if (frames[k] != -1) printf("%2d ", frames[k]); else printf(" - ");
            printf(" | HIT\n");
        }
    }
    printf("Total Page Faults (LFU): %d\n", pageFaults);

    return 0;
}
