#include <stdio.h>

#define INF 999999

int main() {
    int n, i, j;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int cost[n][n];
    printf("Enter the cost adjacency matrix (0 for no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
            if (cost[i][j] == 0)
                cost[i][j] = INF;   // Replace 0 with INF except diagonal
        }
    }

    int visited[n];
    for (i = 0; i < n; i++)
        visited[i] = 0;

    visited[0] = 1;  // Start from vertex 0
    int edges = 0, min, a, b, total_cost = 0;

    printf("\nEdges in Minimum Spanning Tree:\n");

    while (edges < n - 1) {
        min = INF;

        for (i = 0; i < n; i++) {
            if (visited[i]) {
                for (j = 0; j < n; j++) {
                    if (!visited[j] && cost[i][j] < min) {
                        min = cost[i][j];
                        a = i;
                        b = j;
                    }
                }
            }
        }

        visited[b] = 1;
        printf("%d -> %d  cost = %d\n", a, b, min);
        total_cost += min;
        edges++;
    }

    printf("\nTotal cost of Minimum Spanning Tree = %d\n", total_cost);

    return 0;
}


PRIM_MST(AdjW, n, s):
 1. inMST[1..n] ← FALSE; key[1..n] ← ∞; parent[1..n] ← NIL
 2. key[s] ← 0
 3. PQ ← empty min-PQ; INSERT (0, s)
 4. total ← 0
 5. While PQ not empty:
 5.1 (k, u) ← EXTRACT_MIN(PQ)
 5.2 If inMST[u] = TRUE: continue
 5.3 inMST[u] ← TRUE; total ← total + k
 5.4 For each (v, w) in AdjW[u]:
 If inMST[v] = FALSE and w < key[v]:
 key[v] ← w; parent[v] ← u; INSERT (key[v], v)
 6. MST ← edges {(parent[v], v, key[v]) | v ≠ s}
 7. Return (MST, total)