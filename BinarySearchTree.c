
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

typedef struct _Data {
    int number;
} Data;

typedef struct _Node {
    Data data;
    struct _Node *left;
    struct _Node *right;
    struct _Node *parent;
} Node;

typedef struct _BST {
    Node *root_node;
} Tree;


Tree *createTree();
Node *createNode(Data d);
void insert(Tree *bst, Data data);
void insertNode(Node *node, Data data);
Node *search(Tree *bst, Data data);
Node *searchNode(Node *node, Data data);
void printInorder(Tree *bst);
void printInorderdata(Node *node);
void printpreorder(Tree *bst);
void printpreorderdata(Node *node);
void printpostorder(Tree *bst);
void printpostorderdata(Node *node);
Node* deleteNode(Node *node);
void removeLeaf(Tree *bst, Node *d_node);
void shortCircuit(Tree *bst, Node *d_node);
void promotion(Tree *bst, Node *d_node);
void removeNode(Tree * bst, Data value);
void removeRootNode(Tree *bst);
void removeOtherNode(Node* current, Data value);
Node *getnextMaxNode(Node *d_node);
Node *getnextMinNode(Node *d_node);
void postorderdeletion(Tree *bst, Data value);

Tree *createTree() {
    Tree *btree = (Tree*) malloc(sizeof (Tree));
    btree->root_node = NULL;
    return btree;
}

Node *createNode(Data d) {
    Node *node = (Node*) malloc(sizeof (Node));
    node->data.number = d.number;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

void insert(Tree *bst, Data data) {
    printf("Inserting value in B-Tree %d\n", data.number);
    //    Create the first Node (root Node)
    if (bst->root_node == NULL) {
        Node* new_created_node = createNode(data);
        bst->root_node = new_created_node;
    } else {
        insertNode(bst->root_node, data);
    }
}

void insertNode(Node *currentnode, Data data) {
    Node *newnode;
    if (currentnode->data.number == data.number) {
        printf("Insertion of duplicate values are not possible\n");
        return;
    } else if (currentnode->data.number > data.number) {
        if (currentnode->left == NULL) {
            newnode = createNode(data);
            currentnode->left = newnode;
            newnode->parent = currentnode;
        } else {
            insertNode(currentnode->left, data);
        }
    } else if (currentnode->data.number < data.number) {
        if (currentnode->right == NULL) {
            newnode = createNode(data);
            currentnode->right = newnode;
            newnode->parent = currentnode;
        } else {
            insertNode(currentnode->right, data);
        }
    } else {
        printf("Cannot insert duplicate values.\n");
    }
}

Node *search(Tree *bst, Data data) {
    if (bst->root_node == NULL) {
        printf("Tree is Null \n");
        return NULL;
    } else {
        return searchNode(bst->root_node, data);
    }
    return NULL;
}

Node *searchNode(Node *currentnode, Data data) {
    if (currentnode == NULL) {
        printf("Value missing in B-Tree \n");
        return NULL;
    }
    //    printf("currentnode->data.number : %d and data.number : %d\n", currentnode->data.number, data.number);
    if (currentnode->data.number == data.number) {
        printf("Element is present %d \n", currentnode->data.number);
        return currentnode;
    } else if (currentnode->data.number < data.number) {
        return searchNode(currentnode->right, data);
    } else {
        return searchNode(currentnode->left, data);
    }
}

void printInorder(Tree *bst) {
    if (bst->root_node == NULL) {
        printf("Tree is empty \n");
    } else {
        Node *node = bst->root_node;
        printInorderdata(node);
    }
}

void printInorderdata(Node *node) {
    if (node != NULL) {
        printInorderdata(node->left);
        printf(" %d ", node->data.number);
        printInorderdata(node->right);
    }
}

void printpreorder(Tree *bst) {
    if (bst->root_node == NULL) {
        printf("Tree is empty \n");
    } else {
        Node *node = bst->root_node;
        printpreorderdata(node);
    }
}

void printpreorderdata(Node *node) {
    if (node != NULL) {
        printf(" %d ", node->data.number);
        printpreorderdata(node->left);
        printpreorderdata(node->right);
    }
}

void printpostorder(Tree *bst) {
    if (bst->root_node == NULL) {
        printf("Tree is empty \n");
    } else {
        Node *node = bst->root_node;
        printpostorderdata(node);
    }
}

void printpostorderdata(Node *node) {
    if (node != NULL) {
        printpostorderdata(node->left);
        printpostorderdata(node->right);
        printf(" %d ", node->data.number);
    }
}

Node* deleteNode(Node *node) {
    free(node);
    return NULL;
}

void removeLeaf(Tree *bst, Node *d_node) {
    printf("Removing Leaf Node \n");
    Node *parentnode = d_node->parent;
    if (parentnode->right != NULL) {
        if (parentnode->right->data.number == d_node->data.number) {
            deleteNode(d_node);
            parentnode->right = NULL;
            return;
        }
    }
    if (parentnode->left != NULL) {
        if (parentnode->left->data.number == d_node->data.number) {
            deleteNode(d_node);
            parentnode->left = NULL;
            return;
        }
    }

}

void shortCircuit(Tree *bst, Node *d_node) {
    printf("In short circuit delete Leaf Node flow \n");
    Node *parentnode = d_node->parent;

    if (d_node->left != NULL) {
        if ((parentnode->left != NULL) && (parentnode->left->data.number == d_node->data.number)) {
            parentnode->left = d_node->left;
            parentnode->left->parent = parentnode;
            deleteNode(d_node);
        } else {
            parentnode->right = d_node->left;
            parentnode->right->parent = parentnode;
            deleteNode(d_node);
        }
    }

    if (d_node->right != NULL) {
        if ((parentnode->left != NULL) && (parentnode->left->data.number == d_node->data.number)) {
            parentnode->left = d_node->right;
            parentnode->left->parent = parentnode;
            deleteNode(d_node);
        } else {
            parentnode->right = d_node->right;
            parentnode->right->parent = parentnode;
            deleteNode(d_node);
        }
    }

}

void promotion(Tree *bst, Node *d_node) {
    Node *currentnode = d_node->left;
    while (currentnode->right != NULL) {
        currentnode = currentnode->right;
    }

    if (currentnode->left == NULL && currentnode->right == NULL) {
        printf("Node to be removed : %d \n", currentnode->data.number);
        removeLeaf(bst, currentnode);
        return;
    }

    if (currentnode->left == NULL || currentnode->right == NULL) {
        printf("Node to be removed : %d \n", currentnode->data.number);
        shortCircuit(bst, currentnode);
        return;
    }
}

void removeOtherNode(Node* current, Data value) {
    Tree *bst;
    if (current->data.number == value.number) {
        if (current->left == NULL && current->right == NULL) {
            removeLeaf(bst, current);
        } else if (current->left == NULL || current->right == NULL) {
            shortCircuit(bst, current);
        } else {
            promotion(bst, current);
        }
    } else if (current->data.number < value.number) {
        removeOtherNode(current->right, value);
    } else if (current->data.number > value.number) {
        removeOtherNode(current->left, value);
    }
}

void removeRootNode(Tree *bst) {
    Node *nodetoberemoved;
    if (bst->root_node == NULL) {
        printf("B-Tree is empty \n");
        return;
    }
    if (bst->root_node->right == NULL && bst->root_node->left == NULL) {
        deleteNode(bst->root_node);
        bst->root_node = NULL;
        return;
    } else if (bst->root_node->left == NULL && bst->root_node->right != NULL) {
        nodetoberemoved = bst->root_node;
        bst->root_node = bst->root_node->right;
        deleteNode(nodetoberemoved);
        nodetoberemoved = NULL;
    } else if (bst->root_node->left != NULL && bst->root_node->right == NULL) {
        nodetoberemoved = bst->root_node;
        bst->root_node = bst->root_node->left;
        deleteNode(nodetoberemoved);
        nodetoberemoved = NULL;
    } else {
        Node *rootnode = bst->root_node;
        Node *nexthighestnode = getnextMaxNode(rootnode);
        bst->root_node->data = nexthighestnode->data;
        if (nexthighestnode->left == NULL && nexthighestnode->right == NULL) {
            removeLeaf(bst, nexthighestnode);
            return;
        } else if (nexthighestnode->left == NULL || nexthighestnode->right == NULL) {
            shortCircuit(bst, nexthighestnode);
        }
    }
}

void removeNode(Tree *bst, Data value) {
    if (bst->root_node == NULL) {
        printf("Tree is empty. \n");
        return;
    } else {
        printf("Searching Node in B Tree\n");
        Node *nodestatus = search(bst, value);
        if (nodestatus == NULL) {
            printf("Value not present in B-Tree. \n");
        } else {
            if (bst->root_node->data.number == value.number) {
                removeRootNode(bst);
            } else {
                removeOtherNode(bst->root_node, value);
            }
        }
    }
}

Node *getnextMaxNode(Node *d_node) {
    Node *currentnode = d_node;
    currentnode = currentnode->right;
    while (currentnode->left != NULL) {
        currentnode = currentnode->left;
    }
    return currentnode;
}

Node *getnextMinNode(Node *d_node) {
    Node *currentnode = d_node;
    currentnode = currentnode->left;
    while (currentnode->right != NULL) {
        currentnode = currentnode->right;
    }
    return currentnode;
}

Node* deleteTreeFurtherNodes(Node* current) {
    if (current->left != NULL) {
        deleteTreeFurtherNodes(current->left);
    }
    if (current->right != NULL) {
        deleteTreeFurtherNodes(current->right);
    }
    deleteNode(current);
    return NULL;
}

Tree *deleteTree(Tree *bst) {
    if (bst->root_node != NULL) {
        deleteTreeFurtherNodes(bst->root_node);
    }
    free(bst);
    return NULL;
}

void postorderdeletion(Tree *bst, Data value) {
    if (bst->root_node == NULL) {
        printf("Tree is empty. \n");
        return;
    } else {
        printf("Searching Node in B Tree\n");
        Node *nodestatus = search(bst, value);
        if (nodestatus == NULL) {
            printf("Value not present in B-Tree. \n");
        } else {
            if (nodestatus->left == NULL && nodestatus->right == NULL) {
                removeLeaf(bst, nodestatus);
            } else {
                printf("Deletion not possible \n");
                printf("Entered node is not Leaf Node.\n");
                printf("Post Order deletion only delete the Leaf Node.\n");
                return;
            }
        }
    }
}

int main() {
    FILE *file_pointer;
    Tree *binarytree;
    int userinput;
    Node* foundnode;
    int filedata[8];
    int count;
    count = 0;
    Data data;

    binarytree = createTree();
    file_pointer = fopen("data.txt", "r");
    printf("Reading values from file\n");
    //    Reading data from File (Start)
    while (!feof(file_pointer)) {
        fscanf(file_pointer, "%d", &filedata[count]);
        printf("%d", filedata[count]);
        count++;
    }
    fclose(file_pointer);
    file_pointer = NULL;
    //    Reading data from File (End)

    printf("Inserting respective values in B-Tree\n");
    for (count = 0; count < 8; count++) {
        data.number = filedata[count];
        insert(binarytree, data);
    }

    printf("\nPrinting B-Tree - In Order   : ");
    printInorder(binarytree);
    printf("\nPrinting B-Tree - Post Order : ");
    printpostorder(binarytree);
    printf("\nPrinting B-Tree - Pre Order  : ");
    printpreorder(binarytree);
    printf("\n");
    printf("\n");
    printf("Kindly enter the number you want to search \n");
    scanf("%d", &data.number);
    printf("\nSearch data : %d\n", data.number);

    foundnode = search(binarytree, data);
    if (foundnode != NULL) {
        if (foundnode->parent == NULL || foundnode == foundnode->parent) {
            printf("Node is root node = %d\n", foundnode->data.number);
        } else {
            printf("Parent Node = %d\n", foundnode->parent->data.number);
        }
        printf("Printing Nodes Child Values in InOrder Format \n");
        printInorderdata(foundnode);
    }
    printf("\n");
    
    /*    ------------------ Normal Deletion (Start) ----------------- */
    printf("\nBefore Deletions. Printing B-Tree - In Order format  : ");
    printInorder(binarytree);
    printf("\n\nEnter the values to be deleted \tEnter 0 to exit\n");
    do {
        scanf("%d", &userinput);
        data.number = userinput;
        removeNode(binarytree, data);
        printf("\nPrinting B-Tree - In Order format   : ");
        printInorder(binarytree);
        printf("\n\nEnter the values to be deleted \tEnter 0 to exit\n");
        if (binarytree->root_node == NULL) {
            printf("Tree is Empty. Further Deletion not possible.");
            userinput = 0;
        }
    } while (userinput != 0);
    printf("\n");
    printf("\n");
    deleteTree(binarytree);
    binarytree = NULL;
    /* ------------------ Normal Deletion (END) --------------------- */


    /* ------------------ Post Order Deletion (Start) ----------------- */
    binarytree = createTree();
    printf("\n\nRe-populating values in B-Tree for Post-order deletion \n");

    for (count = 0; count < 8; count++) {
        data.number = filedata[count];
        insert(binarytree, data);
    }

    printf("\nBefore Deletions. Printing B-Tree - Post Order format  : ");
    printpostorder(binarytree);
    printf("\n\nEnter the values to be deleted for Post-order deletion \tEnter 0 to exit\n");
    do {
        scanf("%d", &userinput);
        data.number = userinput;
        postorderdeletion(binarytree, data);
        printf("\nPrinting B-Tree - Post Order format   : ");
        printpostorder(binarytree);
        printf("\n\nEnter the values to be deleted for post-order deletion \tEnter 0 to exit\n");
        if (binarytree->root_node == NULL) {
            printf("\nTree is Empty. Further Deletion not possible.\n");
            userinput = 0;
        }
    } while (userinput != 0);
    /* ------------------ Post Order Deletion (END) ----------------- */
    printf("\n");
    printf("\n");
    deleteTree(binarytree);
    binarytree = NULL;

    return 0;
}