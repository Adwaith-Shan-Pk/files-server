#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int key) {
    if (root == NULL)
        return createNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key)
        return root;
    if (key < root->key)
        return search(root->left, key);
    return search(root->right, key);
}

void inorder(struct Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

struct Node* findMin(struct Node* node) {
    while (node->left != NULL)
        node = node->left;
    return node;
}

struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL)
            return root->right;
        else if (root->right == NULL)
            return root->left;
        struct Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

void rangeQuery(struct Node* root, int L, int R) {
    if (root == NULL)
        return;
    if (root->key > L)
        rangeQuery(root->left, L, R);
    if (root->key >= L && root->key <= R)
        printf("%d ", root->key);
    if (root->key < R)
        rangeQuery(root->right, L, R);
}

int main() {
    struct Node* root = NULL;
    int choice = 0, key, L, R;
    while (choice != 6) {
        printf("\n1. Insert\n2. Delete\n3. Search\n4. Inorder Traversal\n5. Range Query\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter key to insert: ");
            scanf("%d", &key);
            root = insert(root, key);
        } else if (choice == 2) {
            printf("Enter key to delete: ");
            scanf("%d", &key);
            root = deleteNode(root, key);
        } else if (choice == 3) {
            printf("Enter key to search: ");
            scanf("%d", &key);
            if (search(root, key))
                printf("Key found.\n");
            else
                printf("Key not found.\n");
        } else if (choice == 4) {
            printf("Inorder Traversal: ");
            inorder(root);
            printf("\n");
        } else if (choice == 5) {
            printf("Enter range (L R): ");
            scanf("%d%d", &L, &R);
            printf("Keys in range [%d, %d]: ", L, R);
            rangeQuery(root, L, R);
            printf("\n");
        } else if (choice == 6) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice.\n");
        }
    }
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
