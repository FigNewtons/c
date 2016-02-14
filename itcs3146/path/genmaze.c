/* Maze generator */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generateMaze(char [], int, int);
void printMaze(char [], int, int);
void printToFile(char [], int, int, char []);

int main(int argc, char **argv){

    int row, col, i, j;
    char file_name[20];

    if(argc == 4){
        row = atoi(argv[1]);
        col = atoi(argv[2]);
        strcpy(file_name, argv[3]);
    }

    char maze[row * col];

    printf("%d %d %s\n", row, col, file_name);

    for(i = 0; i < row; i++)
        for(j = 0; j < col; j++)
            maze[col * i + j] = '1';

    generateMaze(maze, row, col);
    printMaze(maze, row, col);
    printToFile(maze, row, col, file_name);

}

void generateMaze(char maze[], int row, int col){

    int x, y, loop;
    int entry, exit, possible_zeros = (col * col) * 2 / 3;

    srandom(time(NULL));

    do {
        entry = random() % 4;
        exit = random() % 4;
    } while (entry == exit);

    switch(entry){

        case 0:
            x = 1 + random() % (row - 2);
            y = 0;
            break;

        case 1:
            x = 0;
            y = 1 + random() % (col - 2);
            break;

        case 2:
            x = 1 + random() % (row - 2);
            y = col - 1;
            break;

        default:
            x = row - 1;
            y = 1 + random() % (col - 2);
    }

    maze[col * x + y] = '0';

    switch(exit){

        case 0:
            x = 1 + random() % (row - 2);
            y = 0;
            break;

        case 1:
            x = 0;
            y = 1 + random() % (col - 2);
            break;

        case 2:
            x = 1 + random() % (row - 2);
            y = col - 1;
            break;

        default:
            x = row - 1;
            y = 1 + random() % (col - 2);
    }

    maze[col * x + y] = '0';

    for(loop = 1; loop < possible_zeros; loop++){
        x = 1 + random() % (row - 2);
        y = 1 + random() % (col - 2);
        maze[col * x + y] = '0';
    }
}

void printMaze(char maze[], int row, int col){

    int i, j;
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++)
            printf("%c ", maze[col * i + j]);

        printf("\n");
    }   

    printf("\n");
}

void printToFile(char maze[], int row, int col, char file_name[]){

    FILE *f;
    int i, j;

    f = fopen(file_name, "w");

    if(f == NULL){
        printf("Error opening %s\n", file_name);
        exit(1);
    }
    
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++)
            fprintf(f, "%c ", maze[col * i + j]);

       fprintf(f, "\n");
    }

    fclose(f);
}

