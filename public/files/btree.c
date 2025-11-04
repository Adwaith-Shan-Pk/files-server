#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 1

struct BTreeNode {
    int item[MAX + 1], count;
    struct BTreeNode *link[MAX + 1];
};

struct BTreeNode *root;

struct BTreeNode* createNode(int item, struct BTreeNode* child) {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->item[1] = item;
    newNode->count = 1;
    newNode->link[0] = root;
    newNode->link[1] = child;
    return newNode;
}

void insertNode(int item, int pos, struct BTreeNode* node, struct BTreeNode* child) {
    int j = node->count;
    while (j > pos) {
        node->item[j + 1] = node->item[j];
        node->link[j + 1] = node->link[j];
        j--;
    }
    node->item[j + 1] = item;
    node->link[j + 1] = child;
    node->count++;
}

void splitNode(int item, int *pval, int pos, struct BTreeNode* node, struct BTreeNode* child, struct BTreeNode** newNode) {
    int median, j;
    if (pos > MIN)
        median = MIN + 1;
    else
        median = MIN;
    *newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    j = median + 1;
    while (j <= MAX) {
        (*newNode)->item[j - median] = node->item[j];
        (*newNode)->link[j - median] = node->link[j];
        j++;
    }
    (*newNode)->count = MAX - median;
    node->count = median;
    if (pos <= MIN)
        insertNode(item, pos, node, child);
    else
        insertNode(item, pos - median, *newNode, child);
    *pval = node->item[node->count];
    (*newNode)->link[0] = node->link[node->count];
    node->count--;
}

int setValue(int item, int *pval, struct BTreeNode* node, struct BTreeNode** child) {
    int pos;
    if (!node) {
        *pval = item;
        *child = NULL;
        return 1;
    }
    if (item < node->item[1])
        pos = 0;
    else {
        for (pos = node->count; (item < node->item[pos] && pos > 1); pos--);
        if (item == node->item[pos])
            return 0;
    }
    if (setValue(item, pval, node->link[pos], child)) {
        if (node->count < MAX)
            insertNode(*pval, pos, node, *child);
        else {
            splitNode(*pval, pval, pos, node, *child, child);
            return 1;
        }
    }
    return 0;
}

void insert(int item) {
    int flag, i;
    struct BTreeNode *child;
    flag = setValue(item, &i, root, &child);
    if (flag)
        root = createNode(i, child);
}

void traversal(struct BTreeNode* node) {
    int i;
    if (node) {
        for (i = 0; i < node->count; i++) {
            traversal(node->link[i]);
            printf("%d ", node->item[i + 1]);
        }
        traversal(node->link[i]);
    }
}

int main() {
    int item, choice = 0;
    while (choice != 3) {
        printf("\n1. Insert\n2. Display\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter value to insert: ");
            scanf("%d", &item);
            insert(item);
        } else if (choice == 2) {
            printf("B-Tree Traversal: ");
            traversal(root);
            printf("\n");
        } else if (choice == 3) {
            printf("Exiting...\n");
        } else {
            printf("Invalid choice!\n");
        }
    }
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
