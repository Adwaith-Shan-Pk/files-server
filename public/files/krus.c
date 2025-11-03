#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Structure to represent an edge in the graph
struct Edge {
    int src, dest, weight;
};

// 2. Structure to represent a graph
struct Graph {
    int V, E;           // V: number of vertices, E: number of edges
    struct Edge* edge;  // Array of edges
};

// 3. Structure to represent a subset for Disjoint Set Union (DSU)
struct Subset {
    int parent;
    int rank; // Used for Union by Rank optimization
};

// A utility function to create a graph with V vertices and E edges
struct Graph* createGraph(int V, int E) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->E = E;
    // Allocate memory for E edges
    graph->edge = (struct Edge*)malloc(graph->E * sizeof(struct Edge));
    return graph;
}

// DSU function with Path Compression: Finds the representative (root) of set i
int find(struct Subset subsets[], int i) {
    // Base case: if element is the root of its set
    if (subsets[i].parent == i)
        return i;

    // Path Compression: recursively find the root and update the parent
    subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// DSU function with Union by Rank: Merges the sets of x and y
void Union(struct Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    // Attach the tree with smaller rank to the root of the tree with higher rank
    if (rootX != rootY) {
        if (subsets[rootX].rank < subsets[rootY].rank) {
            subsets[rootX].parent = rootY;
        } else if (subsets[rootX].rank > subsets[rootY].rank) {
            subsets[rootY].parent = rootX;
        } else {
            // If ranks are the same, make one root the parent and increment its rank
            subsets[rootY].parent = rootX;
            subsets[rootX].rank++;
        }
    }
}

// Comparison function used by qsort() to sort edges based on their weight
int compareEdges(const void* a, const void* b) {
    // Cast void pointers to Edge pointers
    struct Edge* edgeA = (struct Edge*)a;
    struct Edge* edgeB = (struct Edge*)b;
    // Compare weights (smallest first)
    return edgeA->weight - edgeB->weight;
}

// The main function to construct MST using Kruskal's algorithm
void kruskalMST(struct Graph* graph) {
    int V = graph->V;
    int E = graph->E;
    struct Edge result[V];  // Stores the resulting MST edges
    int e = 0;              // Index used for the result[] array
    int i = 0;              // Index used for sorted_edges

    // Step 2: Sort all the edges in non-decreasing order of their weight
    // We use C's standard library qsort function
    qsort(graph->edge, E, sizeof(graph->edge[0]), compareEdges);

    // Step 1: Initialize V subsets (DSU structure)
    struct Subset* subsets = (struct Subset*)malloc(V * sizeof(struct Subset));

    // Initially, all vertices are in different sets and have rank 0
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Step 3: Iterate through sorted edges
    printf("\n--- Kruskal's Algorithm Trace ---\n");
    printf("Processing edges in ascending order of weight...\n");

    while (e < V - 1 && i < E) {
        struct Edge next_edge = graph->edge[i++];

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // Check if adding this edge forms a cycle
        if (x != y) {
            // No cycle: Add this edge to MST and perform Union
            result[e++] = next_edge;
            Union(subsets, x, y);
            printf("  [ACCEPTED] Edge %d-%d (Weight: %d). MST Edges: %d/%d\n", 
                   next_edge.src, next_edge.dest, next_edge.weight, e, V - 1);
        } else {
            // Cycle detected: Discard the edge
            printf("  [REJECTED] Edge %d-%d (Weight: %d). Creates a cycle.\n",
                   next_edge.src, next_edge.dest, next_edge.weight);
        }
    }

    // Print the final MST
    printf("\n--- Minimum Spanning Tree ---\n");
    int minimumCost = 0;
    printf("Edges in the MST:\n");
    for (i = 0; i < e; ++i) {
        printf("  %d -- %d \t(Weight: %d)\n", result[i].src, result[i].dest, result[i].weight);
        minimumCost += result[i].weight;
    }
    printf("\nTotal Minimum Cost: %d\n", minimumCost);

    // Clean up memory
    free(subsets);
}

// Driver code to test the function
int main() {
    /*
        Example Graph (V=4, E=5)
        Edges:
        0-1 (10)
        0-2 (6)
        0-3 (5)
        1-3 (15)
        2-3 (4)
    */
    int V = 4; // Number of vertices (0, 1, 2, 3)
    int E = 5; // Number of edges
    struct Graph* graph = createGraph(V, E);

    // Edge 0-1, weight 10
    graph->edge[0].src = 0;
    graph->edge[0].dest = 1;
    graph->edge[0].weight = 10;

    // Edge 0-2, weight 6
    graph->edge[1].src = 0;
    graph->edge[1].dest = 2;
    graph->edge[1].weight = 6;

    // Edge 0-3, weight 5
    graph->edge[2].src = 0;
    graph->edge[2].dest = 3;
    graph->edge[2].weight = 5;

    // Edge 1-3, weight 15
    graph->edge[3].src = 1;
    graph->edge[3].dest = 3;
    graph->edge[3].weight = 15;

    // Edge 2-3, weight 4
    graph->edge[4].src = 2;
    graph->edge[4].dest = 3;
    graph->edge[4].weight = 4;

    kruskalMST(graph);

    // Clean up graph memory
    free(graph->edge);
    free(graph);

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