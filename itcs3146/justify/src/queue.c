#include <stdio.h>
#include <stdlib.h>


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

void enqueue(Queue *, char *);
char* dequeue(Queue *);

char* peek(Queue *);
int isEmpty(Queue *);
int length(Queue *);
void print(Queue *);


main() {

    Queue *q = createQueue();

    if(isEmpty(q))
       printf("Queue is empty\n"); 

    enqueue(q, "lol");
    enqueue(q, "penis");
    enqueue(q, "hello");
    enqueue(q, "bye");
    dequeue(q);
    dequeue(q);

    print(q);

    deleteQueue(q);

}

Queue *createQueue(){
    Queue *q = malloc(sizeof(Queue));
    q -> length = 0;

    return q;
}

void deleteQueue(Queue *q){
    while(!isEmpty(q)) dequeue(q);
    free(q);
}

void enqueue(Queue *q, char *w){

    Node *item;

    item = malloc(sizeof(Node));
    
    if(item != NULL){
        item -> word = w;
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

void print(Queue *q){

    if(!isEmpty(q)){

        printf("Stack length: %d\n", length(q));

        Node *current;
        current = q -> front;

        do {
            printf("Item: %s\n", current -> word);
            current = current -> next;
        }while(current != NULL);
    }
}
