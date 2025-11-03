#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the maximum number of nodes the array can hold.
// Array index 0 is typically unused, so MAX_NODES + 1 is the array size.
#define MAX_NODES 15 
#define EMPTY_NODE 0 // Value used to represent an empty slot

// Structure to hold the array-based tree
struct ArrayTree {
    // Array to store keys. We use MAX_NODES + 1 size, ignoring index 0 
    // to simplify calculations: Left Child = 2*i, Right Child = 2*i + 1.
    int nodes[MAX_NODES + 1]; 
    int nextInsertIndex; // Tracks the next available slot for a simple, complete-like insertion
};

// Utility function to initialize the array tree
void initializeTree(struct ArrayTree* tree) {
    // Set all nodes to EMPTY_NODE (0)
    memset(tree->nodes, EMPTY_NODE, sizeof(tree->nodes));
    // The first node will be inserted at index 1
    tree->nextInsertIndex = 1; 
}

// Function to insert a node at the next available position 
// (mimicking a level-order insertion for simplicity)
int insertNode(struct ArrayTree* tree, int key) {
    if (tree->nextInsertIndex > MAX_NODES) {
        printf("Error: Tree array is full! Cannot insert %d.\n", key);
        return 0; // Insertion failed
    }

    int index = tree->nextInsertIndex;
    tree->nodes[index] = key;
    tree->nextInsertIndex++;
    
    // Calculate and print parent information for visualization
    if (index > 1) {
        int parentIndex = index / 2;
        char* side = (index % 2 == 0) ? "Left" : "Right";
        printf("  Inserted %d at index %d. Parent (%d) is %d.\n", 
               key, index, parentIndex, tree->nodes[parentIndex]);
    } else {
        printf("  Inserted %d at index 1 (Root).\n", key);
    }

    return index; // Insertion successful
}

// --- Traversal functions using array indices ---

// Preorder Traversal (Root -> Left -> Right)
void preorderTraversal(struct ArrayTree* tree, int index) {
    if (index > MAX_NODES || tree->nodes[index] == EMPTY_NODE) {
        return;
    }

    // 1. Visit Root
    printf("%d ", tree->nodes[index]);

    // 2. Traverse Left Subtree (at 2*index)
    preorderTraversal(tree, 2 * index);

    // 3. Traverse Right Subtree (at 2*index + 1)
    preorderTraversal(tree, 2 * index + 1);
}

// Inorder Traversal (Left -> Root -> Right)
void inorderTraversal(struct ArrayTree* tree, int index) {
    if (index > MAX_NODES || tree->nodes[index] == EMPTY_NODE) {
        return;
    }

    // 1. Traverse Left Subtree (at 2*index)
    inorderTraversal(tree, 2 * index);

    // 2. Visit Root
    printf("%d ", tree->nodes[index]);

    // 3. Traverse Right Subtree (at 2*index + 1)
    inorderTraversal(tree, 2 * index + 1);
}

// Postorder Traversal (Left -> Right -> Root)
void postorderTraversal(struct ArrayTree* tree, int index) {
    if (index > MAX_NODES || tree->nodes[index] == EMPTY_NODE) {
        return;
    }

    // 1. Traverse Left Subtree (at 2*index)
    postorderTraversal(tree, 2 * index);

    // 2. Traverse Right Subtree (at 2*index + 1)
    postorderTraversal(tree, 2 * index + 1);

    // 3. Visit Root
    printf("%d ", tree->nodes[index]);
}

// Function to display the raw array structure
void displayArray(struct ArrayTree* tree) {
    printf("\n--- Array Representation (Index 1 to %d) ---\n", MAX_NODES);
    printf("Index: ");
    for (int i = 1; i <= MAX_NODES; i++) {
        printf(" %3d ", i);
    }
    printf("\nValue: ");
    for (int i = 1; i <= MAX_NODES; i++) {
        if (tree->nodes[i] == EMPTY_NODE) {
            printf(" --- ");
        } else {
            printf(" %3d ", tree->nodes[i]);
        }
    }
    printf("\n");
}


// =================================================================
// 2. Driver Code
// =================================================================

int main() {
    struct ArrayTree tree;
    initializeTree(&tree);

    printf("--- Array-Based Binary Tree Operations (Max Nodes: %d) ---\n", MAX_NODES);

    // --- Insertion Demonstration ---
    int keys_to_insert[] = {50, 30, 70, 20, 40, 60, 80, 10, 25};
    int num_keys = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);

    printf("\n1. Inserting keys (Level-Order):\n");
    for (int i = 0; i < num_keys; i++) {
        insertNode(&tree, keys_to_insert[i]);
    }

    // --- Array Display Demonstration ---
    displayArray(&tree);
    
    // --- Traversal Demonstration ---
    printf("\n2. Traversal Order:\n");
    printf("   Inorder (LVR):    ");
    inorderTraversal(&tree, 1);
    printf("\n");
    
    printf("   Preorder (VLR):   ");
    preorderTraversal(&tree, 1);
    printf("\n");
    
    printf("   Postorder (LRV):  ");
    postorderTraversal(&tree, 1);
    printf("\n");

    return 0;
}

BINARY_TREE_ARRAY():
 1. Let T[1 … CAP] be an array (initialize all to NULL)
 2. BUILD_LEVEL_ORDER(L): // L is list of values in level order, may
contain NULL
 2.1 n ← min(|L|, CAP)
 2.2 For i ← 1 to n: T[i] ← L[i]
 3. INORDER(i):
 3.1 If i > CAP or T[i] = NULL: return
 3.2 INORDER(2i)
 3.3 VISIT(T[i])
 3.4 INORDER(2i+1)
 4. PREORDER(i):
 4.1 If i > CAP or T[i] = NULL: return
 4.2 VISIT(T[i])
 4.3 PREORDER(2i)
 4.4 PREORDER(2i+1)
 5. POSTORDER(i):
 5.1 If i > CAP or T[i] = NULL: return
 5.2 POSTORDER(2i)
 5.3 POSTORDER(2i+1)
 5.4 VISIT(T[i])
 6. LEAF_COUNT(i):
 6.1 If i > CAP or T[i] = NULL: return 0
 6.2 If (T[2i] = NULL and T[2i+1] = NULL): return 1
 6.3 return LEAF_COUNT(2i) + LEAF_COUNT(2i+1)
 7. ANCESTORS(i):
 7.1 A ← empty list
 7.2 while i ≥ 2: i ← floor(i/2); if T[i] ≠ NULL then append T[i] to A
 7.3 return A // from parent up to root