#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int u, v, w;
};

struct Edge edges[100], mst[100];
int parent[100];
int n, e;

int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

void unionSet(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

void sortEdges() {
    struct Edge temp;
    for (int i = 0; i < e - 1; i++) {
        for (int j = 0; j < e - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w ||
               (edges[j].w == edges[j + 1].w && edges[j].u > edges[j + 1].u) ||
               (edges[j].w == edges[j + 1].w && edges[j].u == edges[j + 1].u && edges[j].v > edges[j + 1].v)) {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

void kruskal() {
    int i, j = 0, total = 0;
    sortEdges();
    for (i = 0; i < n; i++)
        parent[i] = i;
    for (i = 0; i < e; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;
        if (find(u) != find(v)) {
            mst[j++] = edges[i];
            unionSet(u, v);
            total += w;
            if (j == n - 1)
                break;
        }
    }
    printf("\nEdges in MST:\n");
    for (i = 0; i < j; i++)
        printf("%d - %d : %d\n", mst[i].u, mst[i].v, mst[i].w);
    printf("Total cost of MST: %d\n", total);
}

int main() {
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Enter number of edges: ");
    scanf("%d", &e);
    printf("Enter edges (u v w):\n");
    for (int i = 0; i < e; i++)
        scanf("%d%d%d", &edges[i].u, &edges[i].v, &edges[i].w);
    kruskal();
    return 0;
}



KRUSKAL_MST(n, edges):
 // edges: list of (u, v, w), undirected; assume graph connected
 1. Sort edges by weight ascending (stable tie-break by (u,v) ascending)
 2. MakeSet(1..n) in DSU; MST ← empty list; total ← 0
 3. For each (u, v, w) in edges (in order):

    3.1 If Find(u) ≠ Find(v):
 Union(u, v)
 append (u, v, w) to MST
 total ← total + w
 3.2 If |MST| = n-1: break
 4. Return (MST, total)
