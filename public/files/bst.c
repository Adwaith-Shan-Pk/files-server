#include <stdio.h>
#include <stdlib.h>

// Structure for a BST Node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
};

// Utility function to create a new BST Node
struct Node* newNode(int item) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// Utility function to perform Inorder Traversal
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Utility function to perform Preorder Traversal
void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorder(root->left);
        preorder(root->right);
    }
}

// Utility function to perform Postorder Traversal
void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->key);
    }
}


// Function to insert a new key in the BST
struct Node* insert(struct Node* node, int key) {
    // If the tree is empty, return a new node
    if (node == NULL) return newNode(key);

    // Otherwise, recur down the tree
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    // Return the (unchanged) node pointer
    return node;
}

// Function to find the node with the minimum key value (smallest node in a BST)
struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;

    // Loop down to find the leftmost leaf
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Function to delete a node with the given key from the BST
struct Node* deleteNode(struct Node* root, int key) {
    // Base case: If the tree is empty
    if (root == NULL) return root;

    // 1. Recur down the tree to find the node
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    
    // 2. If the key is the same as root's key, this is the node to be deleted
    else {
        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children
        // Get the inorder successor (smallest in the right subtree)
        struct Node* temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Utility function to free all memory used by the BST
void destroyBST(struct Node* root) {
    if (root != NULL) {
        destroyBST(root->left);
        destroyBST(root->right);
        free(root);
    }
}

// =================================================================
// 2. Driver Code
// =================================================================

int main() {
    struct Node* root = NULL;

    printf("--- Binary Search Tree (BST) Operations ---\n");

    // --- Insertion Demonstration ---
    int keys_to_insert[] = {50, 30, 70, 20, 40, 60, 80};
    int num_keys = sizeof(keys_to_insert) / sizeof(keys_to_insert[0]);

    printf("\n1. Inserting keys: ");
    for (int i = 0; i < num_keys; i++) {
        root = insert(root, keys_to_insert[i]);
        printf("%d ", keys_to_insert[i]);
    }
    printf("\n");

    // --- Traversal Demonstration ---
    printf("\n2. Traversal Order:\n");
    printf("   Inorder (Sorted): ");
    inorder(root);
    printf("\n");
    
    printf("   Preorder:         ");
    preorder(root);
    printf("\n");
    
    printf("   Postorder:        ");
    postorder(root);
    printf("\n");


    // --- Deletion Demonstration ---
    printf("\n3. Deletion Operations:\n");

    // Delete a leaf node (e.g., 20)
    printf("   Deleting 20 (Leaf)... ");
    root = deleteNode(root, 20);
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    // Delete a node with one child (e.g., 70)
    printf("   Deleting 70 (One child)... ");
    root = deleteNode(root, 70);
    printf("Inorder: ");
    inorder(root);
    printf("\n");

    // Delete a node with two children (e.g., 50 - the root)
    printf("   Deleting 50 (Two children)... ");
    root = deleteNode(root, 50);
    printf("Inorder: ");
    inorder(root);
    printf("\n");
    
    // Final state
    printf("\nFinal Inorder Traversal: ");
    inorder(root);
    printf("\n");

    // Clean up memory
    destroyBST(root);

    return 0;
}



BST_LINKED():
 1. Define record NODE { key, left, right }
 2. root ← NIL
 3. INSERT(root, k):
 3.1 If root = NIL: return NODE(k, NIL, NIL)
 3.2 If k < root.key: root.left ← INSERT(root.left, k)
 Else if k > root.key: root.right ← INSERT(root.right, k)
 Else // duplicate: ignore or handle policy
 3.3 return root
 4. SEARCH(root, k):
 4.1 If root = NIL or root.key = k: return root
 4.2 If k < root.key: return SEARCH(root.left, k)
 Else: return SEARCH(root.right, k)
 5. INORDER(root): // yields sorted order
 5.1 If root = NIL: return
 5.2 INORDER(root.left); VISIT(root.key); INORDER(root.right)
 6. FIND_MIN(x):
 6.1 while x.left ≠ NIL: x ← x.left
 6.2 return x
 7. DELETE(root, k):
 7.1 If root = NIL: return NIL
 7.2 If k < root.key: root.left ← DELETE(root.left, k)
 Else if k > root.key: root.right ← DELETE(root.right, k)
 Else: // found node
 a) If root.left = NIL: return root.right
 b) If root.right = NIL: return root.left
 c) s ← FIND_MIN(root.right) // inorder successor
 root.key ← s.key
 root.right ← DELETE(root.right, s.key)
 7.3 return root
 8. RANGE_QUERY(root, L, R):
 8.1 If root = NIL: return
 8.2 If root.key > L: RANGE_QUERY(root.left, L, R)
 8.3 If L ≤ root.key ≤ R: VISIT(root.key)
 8.4 If root.key < R: RANGE_QUERY(root.right, L, R)