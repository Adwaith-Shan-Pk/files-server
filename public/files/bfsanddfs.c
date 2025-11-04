#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int queue[MAX];
int front = 0, rear = 0;
int n, directed;

void addEdge(int u, int v) {
    graph[u][v] = 1;
    if (!directed)
        graph[v][u] = 1;
}

void displayGraph() {
    int i, j;
    printf("\nAdjacency Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }
}

void enqueue(int v) {
    queue[rear++] = v;
}

int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

void BFS(int start) {
    int i, u;
    for (i = 0; i < n; i++)
        visited[i] = 0;
    front = rear = 0;
    visited[start] = 1;
    enqueue(start);
    printf("BFS Traversal: ");
    while (!isEmpty()) {
        u = dequeue();
        printf("%d ", u);
        for (i = 0; i < n; i++) {
            if (graph[u][i] && !visited[i]) {
                visited[i] = 1;
                enqueue(i);
            }
        }
    }
    printf("\n");
}

void DFSUtil(int v) {
    int i;
    visited[v] = 1;
    printf("%d ", v);
    for (i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            DFSUtil(i);
    }
}

void DFS(int start) {
    int i;
    for (i = 0; i < n; i++)
        visited[i] = 0;
    printf("DFS Traversal: ");
    DFSUtil(start);
    printf("\n");
}

int main() {
    int choice = 0, edges, u, v, start;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    printf("Is the graph directed? (1 for Yes / 0 for No): ");
    scanf("%d", &directed);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }
    while (choice != 4) {
        printf("\n1. Display Graph\n2. BFS Traversal\n3. DFS Traversal\n4. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1)
            displayGraph();
        else if (choice == 2) {
            printf("Enter starting vertex for BFS: ");
            scanf("%d", &start);
            BFS(start);
        } else if (choice == 3) {
            printf("Enter starting vertex for DFS: ");
            scanf("%d", &start);
            DFS(start);
        } else if (choice == 4)
            printf("Exiting...\n");
        else
            printf("Invalid choice!\n");
    }
    return 0;
}
