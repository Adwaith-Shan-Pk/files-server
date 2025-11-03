#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Macro for infinity
#define INF INT_MAX

// =================================================================
// 1. Graph Representation (Adjacency List)
// =================================================================

// Structure for an adjacency list node (represents an edge)
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure for the adjacency list
struct AdjList {
    struct AdjListNode *head;
};

// Structure for the graph itself
struct Graph {
    int V; // Number of vertices
    struct AdjList* array;
};

// Utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode = 
            (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Utility function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists. Size V
    graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList));

    // Initialize all adjacency lists as empty
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Adds an edge to an undirected graph (assuming edge list already contains both directions)
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    // Add edge from src to dest
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Add edge from dest to src (for undirected graph)
    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// =================================================================
// 2. Min Heap (Priority Queue) Implementation
// =================================================================

// Structure for a Min Heap node, containing a vertex and its distance
struct MinHeapNode {
    int v;
    int dist;
};

// Structure for a Min Heap
struct MinHeap {
    int size;      // Current number of heap nodes
    int capacity;  // Maximum size of the heap
    int *pos;      // Array to store position of vertex in minHeap array
    struct MinHeapNode **array;
};

// Utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist) {
    struct MinHeapNode* minHeapNode = 
           (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap = 
         (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = 
         (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Utility function to swap two nodes of min heap
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// A standard function to heapify a subtree with the root at given index
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size && 
        minHeap->array[left]->dist < minHeap->array[smallest]->dist)
      smallest = left;

    if (right < minHeap->size && 
        minHeap->array[right]->dist < minHeap->array[smallest]->dist)
      smallest = right;

    if (smallest != idx) {
        // The node to be swapped in min heap
        struct MinHeapNode *smallestNode = minHeap->array[smallest];
        struct MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions in the position array
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Checks if the given min heap is empty
int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Extracts the node with minimum distance value
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    // Store the root node
    struct MinHeapNode* root = minHeap->array[0];

    // Replace root node with the last node
    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;

    // Update position of the last node (now at index 0)
    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    // Decrease heap size and heapify the root
    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Function to decrease dist value of a given vertex v. This is important
// for the shortest path algorithm.
void decreaseKey(struct MinHeap* minHeap, int v, int dist) {
    // Get the index of v in heap array
    int i = minHeap->pos[v];

    // Get the node and update its dist value
    minHeap->array[i]->dist = dist;

    // Travel up while the complete tree is not heapified.
    // This is the "decrease-key" operation.
    while (i > 0 && minHeap->array[i]->dist < 
                   minHeap->array[(i - 1) / 2]->dist) {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
        swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

        // Move to the parent index
        i = (i - 1) / 2;
    }
}

// Check if a given vertex 'v' is in the min heap or not
int isInMinHeap(struct MinHeap *minHeap, int v) {
   if (minHeap->pos[v] < minHeap->size)
     return 1;
   return 0;
}

// Utility function to print the solution
void printArr(int dist[], int V) {
    printf("\n--- Shortest Path Distances from Source ---\n");
    for (int i = 0; i < V; ++i)
        printf("Vertex %d \t Distance: %s\n", i, 
               (dist[i] == INF) ? "INF" : (char[10]){0} && sprintf((char[10]){0}, "%d", dist[i]));
}

// =================================================================
// 3. Dijkstra's Algorithm
// =================================================================

// Function that implements Dijkstra's single source shortest path algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[V];      // dist[i] will hold the shortest distance from src to i

    // Step 1: Initialize Min Heap and distance array
    struct MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INF;
        // Initialize min heap with all vertices, distance as INF
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    // Distance of source vertex from itself is 0
    dist[src] = 0;
    decreaseKey(minHeap, src, 0);

    // Initially, size of min heap is V
    minHeap->size = V;

    printf("--- Dijkstra's Algorithm Trace (Source: %d) ---\n", src);

    // Step 2: Loop while the Min Heap is not empty
    while (!isEmpty(minHeap)) {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v; // The extracted vertex

        printf("  Extracted vertex %d (Distance: %d)\n", u, dist[u]);

        // Traverse all adjacent vertices of u
        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            // Relaxation step:
            // If shortest distance to v is not finalized and 
            // distance through u is less than its current distance
            if (isInMinHeap(minHeap, v) && dist[u] != INF && 
                pCrawl->weight + dist[u] < dist[v]) {
                
                dist[v] = dist[u] + pCrawl->weight;
                
                // Update distance value in min heap
                decreaseKey(minHeap, v, dist[v]);
                printf("    Relaxing edge %d-%d (New Dist: %d)\n", u, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
        free(minHeapNode); // Free the extracted node
    }

    // Step 3: Print the calculated distances
    printArr(dist, V);
    
    // Clean up memory
    free(minHeap->pos);
    for (int i = 0; i < V; ++i) {
        free(minHeap->array[i]);
    }
    free(minHeap->array);
    free(minHeap);
}

// =================================================================
// 4. Driver Code
// =================================================================

int main() {
    /*
        Example Graph (V=9)
        The graph is the one used in many standard Dijkstra examples.
        Edges:
        0-1(4), 0-7(8)
        1-2(8), 1-7(11)
        2-3(7), 2-8(2), 2-5(4)
        3-4(9), 3-5(14)
        4-5(10)
        5-6(2)
        6-7(1), 6-8(6)
        7-8(7)
    */
    int V = 9;
    struct Graph* graph = createGraph(V);
    
    // Add edges to the graph (for undirected, add both directions)
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 7, 8);
    addEdge(graph, 1, 2, 8);
    addEdge(graph, 1, 7, 11);
    addEdge(graph, 2, 3, 7);
    addEdge(graph, 2, 8, 2);
    addEdge(graph, 2, 5, 4);
    addEdge(graph, 3, 4, 9);
    addEdge(graph, 3, 5, 14);
    addEdge(graph, 4, 5, 10);
    addEdge(graph, 5, 6, 2);
    addEdge(graph, 6, 7, 1);
    addEdge(graph, 6, 8, 6);
    addEdge(graph, 7, 8, 7);

    // Run Dijkstra's Algorithm starting from Vertex 0
    dijkstra(graph, 0);

    // Clean up graph memory (simplified as it's complex for full dynamic cleanup)
    // For production, the Adjacency List nodes should also be freed.
    
    // Free adjacency lists (simplified)
    for (int i = 0; i < V; ++i) {
        struct AdjListNode* curr = graph->array[i].head;
        while (curr != NULL) {
            struct AdjListNode* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    
    free(graph->array);
    free(graph);

    return 0;
}



DIJKSTRA(AdjW, n, s):
 // AdjW[u] = list of (v, w), with w ≥ 0
 1. For i ← 1..n: dist[i] ← ∞; parent[i] ← NIL
 2. dist[s] ← 0
 3. Create empty min-priority-queue PQ; INSERT (0, s)
 4. While PQ not empty:
 4.1 (d, u) ← EXTRACT_MIN(PQ)
 4.2 If d > dist[u]: continue // skip stale pair
 4.3 For each (v, w) in AdjW[u]:
 If dist[u] + w < dist[v]:
 dist[v] ← dist[u] + w
 parent[v] ← u
 INSERT (dist[v], v) into PQ
 5. Return (dist, parent)
PATH(s, t, parent):
 1. If dist[t] = ∞: return "UNREACHABLE"
 2. P ← empty list; x ← t
 3. While x ≠ NIL: prepend x to P; x ← parent[x]
 4. Return P