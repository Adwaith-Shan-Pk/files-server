#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a large number to represent infinity (no edge)
#define INF INT_MAX

// =================================================================
// 1. Graph Representation (Adjacency Matrix)
// =================================================================

// Structure for the graph using Adjacency Matrix
struct Graph {
    int V;          // Number of vertices
    int** adjMatrix; // The adjacency matrix (2D array of integers)
};

// Utility function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Allocate memory for the matrix (array of V pointers)
    graph->adjMatrix = (int**)malloc(V * sizeof(int*));

    // Allocate memory for each row and initialize all weights
    for (int i = 0; i < V; ++i) {
        graph->adjMatrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; ++j) {
            // Self-loops have weight 0, non-existent edges have weight INF
            graph->adjMatrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    return graph;
}

// Adds an edge to the graph with a specified weight
// Note: This implementation assumes an undirected graph.
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    if (src >= 0 && src < graph->V && dest >= 0 && dest < graph->V) {
        // For undirected graph, set the weight in both directions
        graph->adjMatrix[src][dest] = weight;
        graph->adjMatrix[dest][src] = weight;
        printf("  Added edge %d -- %d with weight %d.\n", src, dest, weight);
    } else {
        printf("  Error: Vertex index out of bounds.\n");
    }
}

// Utility function to display the adjacency matrix
void displayGraph(struct Graph* graph) {
    printf("\n--- Adjacency Matrix (%d Vertices) ---\n", graph->V);
    
    // Print column headers
    printf("     ");
    for (int j = 0; j < graph->V; ++j) {
        printf("| %3d ", j);
    }
    printf("|\n");
    
    // Print separator
    printf("-----");
    for (int j = 0; j < graph->V; ++j) {
        printf("------");
    }
    printf("\n");

    // Print rows
    for (int i = 0; i < graph->V; ++i) {
        printf("V %2d |", i);
        for (int j = 0; j < graph->V; ++j) {
            int weight = graph->adjMatrix[i][j];
            if (weight == INF) {
                printf("  INF ");
            } else {
                printf(" %4d ", weight);
            }
        }
        printf("|\n");
    }
    printf("----------------------------------------\n");
}

// Utility function to free allocated memory
void destroyGraph(struct Graph* graph) {
    if (graph) {
        if (graph->adjMatrix) {
            for (int i = 0; i < graph->V; ++i) {
                free(graph->adjMatrix[i]);
            }
            free(graph->adjMatrix);
        }
        free(graph);
    }
}

// =================================================================
// 2. Driver Code
// =================================================================

int main() {
    int V = 5; // Number of vertices: 0, 1, 2, 3, 4
    printf("Creating a graph with %d vertices...\n", V);
    struct Graph* graph = createGraph(V);

    // Demonstration of adding edges
    printf("\n--- Adding Edges ---\n");
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 20);
    addEdge(graph, 1, 2, 30);
    addEdge(graph, 1, 3, 40);
    addEdge(graph, 1, 4, 50);
    addEdge(graph, 2, 3, 60);
    addEdge(graph, 3, 4, 70);

    // Display the graph matrix
    displayGraph(graph);
    
    // Clean up memory
    destroyGraph(graph);

    return 0;
}




BUILD_GRAPH(n, edges, directed):
 1. Create MATRIX M[1..n][1..n] ← 0
 2. Create LIST Adj[1..n] each empty
 3. For each (u, v) in edges:
 3.1 M[u][v] ← 1; append v to Adj[u]
 3.2 If directed = FALSE: M[v][u] ← 1; append u to Adj[v]
 4. For i ← 1..n: sort Adj[i] ascending
 5. Return (M, Adj)
BFS(Adj, n, s):
 1. visited[1..n] ← FALSE; order ← empty
 2. Create empty queue Q; visited[s] ← TRUE; ENQUEUE(Q, s)
 3. While Q not empty:
 3.1 u ← DEQUEUE(Q); append u to order
 3.2 For each v in Adj[u] (ascending):
 If visited[v] = FALSE:
 visited[v] ← TRUE; ENQUEUE(Q, v)
 4. Return order
DFS(Adj, n, s):
 1. visited[1..n] ← FALSE; order ← empty
 2. Procedure VISIT(u):
 2.1 visited[u] ← TRUE; append u to order
 2.2 For each v in Adj[u] (ascending):
 If visited[v] = FALSE: VISIT(v)
 3. VISIT(s)
 4. Return or