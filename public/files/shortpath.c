#include <stdio.h>
#define INF 9999
#define MAX 20

int n, graph[MAX][MAX];

void dijkstra(int start) {
    int dist[MAX], parent[MAX], visited[MAX];
    int i, j, u, v, count, minDist;

    for (i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    dist[start] = 0;

    for (count = 0; count < n - 1; count++) {
        minDist = INF;
        u = -1;
        for (i = 0; i < n; i++)
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }

        if (u == -1)
            break;

        visited[u] = 1;

        for (v = 0; v < n; v++) {
            if (!visited[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nVertex\tDistance\tPath");
    for (i = 0; i < n; i++) {
        printf("\n%d\t%d\t\t", i, dist[i]);
        if (dist[i] == INF)
            printf("UNREACHABLE");
        else {
            int path[MAX], len = 0;
            for (v = i; v != -1; v = parent[v])
                path[len++] = v;
            for (j = len - 1; j >= 0; j--)
                printf("%d ", path[j]);
        }
    }
    printf("\n");
}

int main() {
    int i, j, edges, u, v, w, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter edges (u v w):\n");
    for (i = 0; i < edges; i++) {
        scanf("%d%d%d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    printf("Enter source vertex: ");
    scanf("%d", &start);
    dijkstra(start);

    return 0;
}
