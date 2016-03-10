#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

main() {

    
    char filename[50], line[100], *token;
    FILE *f;
    
    int width, buffer = 100, invalid = 0, newline = 0;

    do {
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
        }

    }while(invalid);


    f = fopen(filename, "r");
    
    while(fgets(line, 100, f) != NULL){
        token = strtok(line, " \t");
        
        while(token != NULL){
          
            if(!strcmp(token, "\n")) newline++;

            token[strcspn(token, "\n")] = 0;

            printf("%s %d\n", token, (int) strlen(token));

            if(newline >= 2){
                printf("NEWPARAGRAPH\n");
                newline = 0;
            }

            token = strtok(NULL, " \t");
        }

    }

    fclose(f);

}
