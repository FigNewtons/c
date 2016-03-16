#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*      justify.c
 *
 *      Author: Daniel Gruszczynski
 *      Date: March 16, 2016
 *
 *      Given a valid file name (plaintext) and the number of
 *      characters per line (between 40 and 100, inclusive), 
 *      output a text-justified version of the original file's
 *      contents.
 */


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


/* Given a string (path to the file name), return a pointer
 * to a queue containing word tokens parsed from the file's
 * contents. 
 */
Queue * tokenize(char filename[]){

    Queue *q;
    FILE  *f;
    char line[1000], *token;
    int newline = 0;

    q = createQueue();
    f = fopen(filename, "r");

    /* Read file in chunks, then tokenize by tabs
     * and whitespaces. We strip new lines and demarcate 
     * paragraphs by enqueuing "\n\n" as a separator. 
     * This means we can use one queue for the entire file. 
     */
    while(fgets(line, 1000, f) != NULL){
        token = strtok(line, " \t");
        
        while(token != NULL){

            if(strchr(token, '\n') != NULL){ 

                /* Strip trailing newline from token */ 
                token[strcspn(token, "\r\n")] = 0;

                if(strcmp(token, "")) enqueue(q, token);
                
                newline++;

            }else {

                if(newline >= 2) enqueue(q, "\n\n");

                enqueue(q, token);
                newline = 0;
            }

            token = strtok(NULL, " \t");
        }
    }

    fclose(f);

    return q;
}

/* Formats the text using queue tokens and line width (no. of characters) */
void justify(Queue *text, int width){

    char *buffer[50], *word;
    int spaceleft, padding, wordcount;

    int additional, remain, spacing, i, j;

    spaceleft = width;
    wordcount = 0;

    while(!isEmpty(text)){

        word = peek(text);

        /* If the token is not paragraph separator */
        if(strcmp(word, "\n\n")){ 
      
            /* Spacing is done to the left of the word */
            padding = wordcount? strlen(word) + 1 : strlen(word);

            /* Line hasn't reached max capacity */
            if(spaceleft >= padding){
                buffer[wordcount++] = dequeue(text);
                spaceleft -= padding;
            }else {

                /* Evenly distribute the spaces left */
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

            /* Last line in paragraph. Empty the buffer before 
             * printing two newlines
             */
            if(wordcount){
                for(i = 0; i < wordcount; i++) printf("%s ", buffer[i]);
                
                spaceleft = width;
                wordcount = 0;
            }
            printf("\n\n");
            dequeue(text);
            
        }
    }

    /* Print last line of file */
    for(i = 0; i < wordcount; i++) printf("%s ", buffer[i]);
    printf("\n");

    deleteQueue(text);
}


