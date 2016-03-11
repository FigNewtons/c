#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*      queue.h
 *
 *      Author: Daniel Gruszczynski
 *      Date: March 16, 2016
 *
 *      Queue (linked-list) implementation to store
 *      word tokens. The code is pretty self-explanatory.
 */

typedef struct Node Node;
struct Node {
    char *word;
    Node *next;
};

typedef struct Queue Queue;
struct Queue {
    Node *front;
    Node *back;
    int length;
};


Queue * createQueue(void);
void deleteQueue(Queue *);
void printQueue(Queue *);

void enqueue(Queue *, char *);
char* dequeue(Queue *);

char* peek(Queue *);
int isEmpty(Queue *);
int length(Queue *);


Queue *createQueue(){
    Queue *q = malloc(sizeof(Queue));
    q -> length = 0;

    return q;
}

void deleteQueue(Queue *q){
    while(!isEmpty(q)) dequeue(q);
    free(q);
}

void printQueue(Queue *q){

    if(!isEmpty(q)){

        printf("Queue length: %d\n", length(q));

        Node *current;
        current = q -> front;

        do {
            printf("Item: %s\n", current -> word);
            current = current -> next;
        }while(current != NULL);
    }
}

void enqueue(Queue *q, char *w){

    Node *item;
    char *temp;

    item = malloc(sizeof(Node));
    temp = malloc(sizeof(w));

    strcpy(temp, w);

    if(item != NULL || temp != NULL){
        item -> word = temp;
        item -> next = NULL;

        if(isEmpty(q)){
            q -> front = item;
            q -> back = item;
        }else{
            (q -> back) -> next = item;
            q -> back = (q -> back) -> next;
        }

        (q -> length)++;

    }else 
        printf("%s not inserted. No memory available.\n", w);
}

char* dequeue(Queue *q){

    if (isEmpty(q)) return NULL;

    Node *temp = q -> front;
    char *w = temp -> word;

    (q -> front) = (q -> front) -> next;
    (q -> length)--;

    free(temp); 
    
    return w;
}

char* peek(Queue *q){

    if(!isEmpty(q)) return (q -> front) -> word;

    return NULL;
}

int isEmpty(Queue *q){
    return q -> front == NULL;
}

int length(Queue *q){
    return  q -> length;
}

