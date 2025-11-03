#include <stdio.h>
#include <stdlib.h>

// Define the minimum degree (t) of the B-Tree.
// t=3 means:
// 1. Every node (except root) must have at least t-1 = 2 keys.
// 2. Every node can have at most 2t-1 = 5 keys.
#define T 3 

// Structure for a B-Tree node
struct BTreeNode {
    int *keys;              // Array of keys (size 2*T - 1)
    struct BTreeNode **children; // Array of child pointers (size 2*T)
    int n;                  // Current number of keys
    int isLeaf;             // 1 if node is a leaf, 0 otherwise
};

// Structure for the B-Tree (main structure holding the root)
struct BTree {
    struct BTreeNode *root;
    int t; // Minimum degree T
};

// Utility function to create a new B-Tree node
struct BTreeNode* createNode(int t, int isLeaf) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    
    // Set the minimum degree
    newNode->t = t;
    
    // Allocate memory for the key array (size 2*t - 1)
    newNode->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    
    // Allocate memory for the child pointer array (size 2*t)
    newNode->children = (struct BTreeNode**)malloc((2 * t) * sizeof(struct BTreeNode*));
    
    // Set properties
    newNode->isLeaf = isLeaf;
    newNode->n = 0; // Starts with zero keys
    
    return newNode;
}

// Utility function to traverse the tree (in-order traversal of keys)
void traverse(struct BTreeNode* root) {
    if (root == NULL) return;

    int i;
    // Recurse to the children and print keys
    for (i = 0; i < root->n; i++) {
        // If not a leaf, recurse to the i-th child (subtree to the left of key i)
        if (root->isLeaf == 0) {
            traverse(root->children[i]);
        }
        printf("%d ", root->keys[i]);
    }

    // Recurse to the last child (subtree to the right of the last key)
    if (root->isLeaf == 0) {
        traverse(root->children[i]);
    }
}

// A function to split the child 'y' of node 'x' at index 'i'.
// 'y' must be full (has 2t-1 keys).
void splitChild(struct BTreeNode* x, int i, struct BTreeNode* y) {
    int t = x->t;
    // Create a new node 'z' that will store t-1 keys of 'y'
    struct BTreeNode* z = createNode(t, y->isLeaf);
    z->n = t - 1;

    // Copy the last t-1 keys of 'y' to 'z'
    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    // If 'y' is not a leaf, copy the last t children of 'y' to 'z'
    if (y->isLeaf == 0) {
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }

    // Reduce the number of keys in 'y'
    y->n = t - 1;

    // Since node 'x' is gaining a new child, move all children after i to the right
    for (int j = x->n; j >= i + 1; j--) {
        x->children[j + 1] = x->children[j];
    }

    // Link the new child 'z' to 'x'
    x->children[i + 1] = z;

    // Move all keys in 'x' after i-1 to the right
    for (int j = x->n - 1; j >= i; j--) {
        x->keys[j + 1] = x->keys[j];
    }

    // Copy the middle key of 'y' up to 'x'
    x->keys[i] = y->keys[t - 1];

    // Increment the number of keys in 'x'
    x->n = x->n + 1;
}

// A function to insert a new key in a node that is guaranteed not to be full
void insertNonFull(struct BTreeNode* x, int k) {
    int i = x->n - 1;
    int t = x->t;

    // Case 1: x is a leaf
    if (x->isLeaf == 1) {
        // Find location of new key and shift all greater keys to the right
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }

        // Insert the new key at the found position
        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } 
    // Case 2: x is not a leaf
    else {
        // Find the child which is going to have the new key
        while (i >= 0 && x->keys[i] > k) {
            i--;
        }
        i++; // i is the index of the child pointer

        // Check if the found child is full
        if (x->children[i]->n == 2 * t - 1) {
            // If full, split it
            splitChild(x, i, x->children[i]);

            // After split, the middle key of the child moves up to x.
            // Determine which of the two children will now contain the key k.
            if (x->keys[i] < k) {
                i++;
            }
        }
        // Recursively call insertNonFull on the appropriate child
        insertNonFull(x->children[i], k);
    }
}

// The main function to insert a new key into the B-Tree
void insert(struct BTree* tree, int k) {
    struct BTreeNode* root = tree->root;
    int t = tree->t;

    // Case 1: Root is full
    if (root->n == 2 * t - 1) {
        // Create a new root node
        struct BTreeNode* s = createNode(t, 0);
        tree->root = s;

        // Make the old root its first child
        s->children[0] = root;

        // Split the old root and connect the new children to the new root
        splitChild(s, 0, root);

        // Insert the new key into the new root
        insertNonFull(s, k);
    } 
    // Case 2: Root is not full
    else {
        insertNonFull(root, k);
    }
}

// Utility function to free allocated memory for the B-Tree
void destroyNode(struct BTreeNode* node) {
    if (node) {
        // Recursively free children if not a leaf
        if (node->isLeaf == 0) {
            for (int i = 0; i <= node->n; i++) {
                destroyNode(node->children[i]);
            }
        }
        free(node->keys);
        free(node->children);
        free(node);
    }
}

void destroyBTree(struct BTree* tree) {
    if (tree && tree->root) {
        destroyNode(tree->root);
    }
    free(tree);
}

// =================================================================
// 2. Driver Code
// =================================================================

int main() {
    // Create a B-Tree with minimum degree T=3
    struct BTree* tree = (struct BTree*)malloc(sizeof(struct BTree));
    tree->t = T;
    
    // Initialize root as a leaf node
    tree->root = createNode(T, 1); 

    // Demonstration of insertion
    printf("--- B-Tree Insertion (T=%d) ---\n", T);
    int keys[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120};
    int num_keys = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < num_keys; i++) {
        insert(tree, keys[i]);
        printf("Inserted key %d. Current tree keys (in-order): ", keys[i]);
        traverse(tree->root);
        printf("\n");
    }

    // Final traversal
    printf("\n--- Final B-Tree Traversal ---\n");
    printf("Keys in sorted order: ");
    traverse(tree->root);
    printf("\n");

    // Clean up memory
    destroyBTree(tree);

    return 0;
}




B_TREE():
 1. Define record NODE { keys[ ], child[ ], n, leaf } // n = #keys
 2. Create empty root: NODE with leaf = TRUE, n = 0
 3. SEARCH(x, k): // return (node, index) or NOTFOUND
 3.1 i ← 1
 3.2 while i ≤ x.n and k > x.keys[i]: i ← i + 1
 3.3 If i ≤ x.n and k = x.keys[i]: return (x, i)
 3.4 If x.leaf = TRUE: return NOTFOUND
 3.5 return SEARCH(x.child[i], k)
 4. SPLIT_CHILD(x, i, y): // y = full child at position i; x is its
parent
 4.1 z ← new NODE; z.leaf ← y.leaf
 4.2 z.n ← t - 1
 4.3 For j ← 1 to t-1: z.keys[j] ← y.keys[j + t]
 4.4 If y.leaf = FALSE:
 For j ← 1 to t: z.child[j] ← y.child[j + t]
 4.5 y.n ← t - 1
 4.6 For j ← x.n+1 down to i+1: x.child[j+1] ← x.child[j]
 4.7 x.child[i+1] ← z
 4.8 For j ← x.n down to i: x.keys[j+1] ← x.keys[j]
 4.9 x.keys[i] ← y.keys[t]
 4.10 x.n ← x.n + 1
 5. INSERT(k):
 5.1 r ← root
 5.2 If r.n = 2t - 1: // root full
 s ← new NODE; s.leaf ← FALSE; s.n ← 0
 s.child[1] ← r; root ← s
 SPLIT_CHILD(s, 1, r)
 INSERT_NONFULL(s, k)
 Else:
 INSERT_NONFULL(r, k)
 6. INSERT_NONFULL(x, k):
 6.1 i ← x.n
 6.2 If x.leaf = TRUE:
 while i ≥ 1 and k < x.keys[i]:
 x.keys[i+1] ← x.keys[i]; i ← i - 1
 x.keys[i+1] ← k; x.n ← x.n + 1
 Else:
 while i ≥ 1 and k < x.keys[i]: i ← i - 1
 i ← i + 1
 If x.child[i].n = 2t - 1:
 SPLIT_CHILD(x, i, x.child[i])
 If k > x.keys[i]: i ← i + 1
 INSERT_NONFULL(x.child[i], k)