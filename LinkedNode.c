//
// Created by Andy Hu on 5/31/23.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedNode {
    int data;
    struct LinkedNode *next;
//    struct LinkedNode *prev;
} node;

node *freeSentinel(node *head);

node *createNode(int data) {
    node *newNode = (node *) malloc(sizeof(node));
    newNode->data = data;
    return newNode;
}

int searchNode(int data, node *head) {
    node *current = head;
    for (int i = 1; current != NULL; ++i) {
        if (current->data == data) {
            return i;
        }
        current = current->next;
    }
    return -1;
}

node *insertNode(int data, int position, node *head) {
    if (head == NULL) {
        printf("Create a new node with null as header");
        head = createNode(data);
        return head;
    }
    node *sentinel = createNode(-1);
    node *newNode = createNode(data);
    sentinel->next = head;
    head = sentinel;
    for (int i = 1; i < position; ++i) {
        head = head->next;
    }
    newNode->next = head->next;
    head->next = newNode;
    node *temp = freeSentinel(sentinel);
    return temp;
}

node *deleteNode(int data, node *head) {
    node *sentinel = createNode(-1);
    sentinel->next = head;
    head = sentinel;
    while (head->next != NULL) {
        if (head->next->data == data) {
            node * temp = head->next;
            head->next = head->next->next;
            free(temp);
            break;
        }
        head = head->next;
    }
    return freeSentinel(sentinel);
}

node *popNode(node *head) {
    node *sentinel = createNode(-1);
    sentinel->next = head;
    head = sentinel;
    while (head->next && head->next->next != NULL) {
        head = head->next;
    }
    head->next = NULL;
    return freeSentinel(sentinel);
}

node *deleteLinkNodes(node *head) {
    node *current = head;
    while (current != NULL) {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    return NULL;
}

node *printAllData(node *head) {
    node *current = head;
    while (current != NULL) {
        printf("%d ->", current->data);
        current = current->next;
    }
    printf("null \n");
    return head;
}

node *freeSentinel(node *head) {
    node *sentinel = head;
    head = head->next;
    free(sentinel);
    return head;
}


int main(){
    printf("Create a new node with null as header");
    node *head = NULL;
    printf("\nInsert 1 to the first position");
    head = insertNode(1, 1, head);
    printf("\nInsert 2 to the second position");
    head = insertNode(2, 2, head);
    printf("\nInsert 3 to the third position");
    head = insertNode(3, 3, head);
    printf("the link looks like: ");
    printAllData(head);
    printf("\nInsert 4 to the second position");
    head = insertNode(4, 2, head);
    printf("the link looks like: ");
    printAllData(head);
    printf("\n pop the last node");
    head = popNode(head);
    printf("the link looks like: ");
    printAllData(head);
    printf("\nDelete 2");
    head = deleteNode(2, head);
    printf("the link looks like: ");
    printAllData(head);
    printf("\nSearch 3");
    printf("\n3 is at position %d", searchNode(3, head));
    printf("\nSearch 4");
    printf("\n4 is at position %d", searchNode(4, head));
    printf("\nDelete all nodes");
    head = deleteLinkNodes(head);
    printf("the link looks like: ");
    printAllData(head);
    return 0;
}