#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


Queue * tokenize(char filename[]);
void justify(Queue *, int);


main() {

    char filename[50];
    int width, invalid = 0;

    do {
        invalid = 0;

        printf("Enter the path to the text file you want to justify:\n");
        scanf("%s", filename);

        printf("Enter the no. of characters per line (between 40 and 100):\n");
        scanf("%d", &width);

        if(access(filename, F_OK) == -1){
            printf("Error: file %s does not exist\n", filename);
            invalid = 1;
        }

        if(width < 40 || width > 100){
            printf("Error: %d is not in valid range.\n", width);
            invalid = 1;
        }

    }while(invalid);

    justify(tokenize(filename), width);
 }


Queue * tokenize(char filename[]){

    Queue *q;
    FILE  *f;
    char line[100], *token;
    int newline = 0;

    q = createQueue();
    f = fopen(filename, "r");

    while(fgets(line, 100, f) != NULL){
        token = strtok(line, " \t");
        
        while(token != NULL){

            if(!strcmp(token, "\n")) newline++;
            else {
                /* Strip trailing newline from token */ 
                token[strcspn(token, "\r\n")] = 0; 

                if(newline >= 2){ 
                    newline = 0;
                    enqueue(q, "\n\n");
                }
                    
                enqueue(q, token);
            }

            token = strtok(NULL, " \t");
        }

    }

    fclose(f);

    return q;
}


void justify(Queue *text, int width){

    char *buffer[50], *word;
    int spaceleft, padding, wordcount;

    int additional, remain, spacing, i, j;

    spaceleft = width;
    wordcount = 0;

    while(!isEmpty(text)){

        word = peek(text);

        if(strcmp(word, "\n\n")){ 
       
            padding = wordcount? strlen(word) + 1 : strlen(word);

            if(spaceleft >= padding){
                buffer[wordcount++] = dequeue(text);
                spaceleft -= padding;
            }else {

                additional = spaceleft / (wordcount - 1);
                remain = spaceleft % (wordcount - 1);

                printf("%s", buffer[0]);
                for(i = 1; i < wordcount; i++){
                
                    spacing = additional + 1;
                    
                    if(remain){
                        spacing++;
                        remain--;
                    }   
                
                    for(j = 0; j < spacing; j++) printf(" ");

                    printf("%s", buffer[i]);
                }
                printf("\n");

                /* Reset */
                spaceleft = width;
                wordcount = 0;
            }

        }else {

            if(wordcount){
                additional = spaceleft / (wordcount - 1);
                remain = spaceleft % (wordcount - 1);

                printf("%s", buffer[0]);
                for(i = 1; i < wordcount; i++){

                    spacing = additional + 1;

                    if(remain){
                        spacing++;
                        remain--;
                    }
                    for(j = 0; j < spacing; j++) printf(" ");

                    printf("%s", buffer[i]);
                }
                printf("\n");
                
                spaceleft = width;
                wordcount = 0;

            }
            printf("\n\n");
            dequeue(text);
            
        }
    }

    for(i = 0; i < wordcount; i++) printf("%s ", buffer[i]);
    printf("\n");
}


