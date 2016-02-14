#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Size limits of the maze */
#define MIN_SIZE 5
#define MAX_SIZE 100

/* Input validation and bounds checking */
#define isValid(x, low, high) (low <= x && x<= high)

typedef struct { int x, y; } Point;

void readMaze(char [], int, int, char []);
void printMaze(char [], int, int);
int solveMaze(char [], int, int);
int traverse(char [], int, int, Point, Point);


main() {

    int row, col, solved;

    /* Input validation */
    do{
        printf("Please enter the size of the maze.\n"
               "Values must be between 5 and 100, inclusive. (e.g. 10,15)\n");
        scanf("%d,%d", &row, &col);
        while(getchar() != '\n');

    } while( !(isValid(row, MIN_SIZE, MAX_SIZE) && isValid(col, MIN_SIZE, MAX_SIZE)) );

    char maze[row * col], file_name[20];

    /* Check if file_name exists */
    do{
        printf("Type in the name of the file containing the maze\n");
        scanf("%s", file_name);
    } while(access(file_name, F_OK) == -1);


    readMaze(maze, row, col, file_name);
    solved = solveMaze(maze, row, col);


    /* Output */
    printMaze(maze, row, col);

    if (solved)
        printf("\nPath found.\n");
    else
        printf("\nNo path found.\n");

}


/* Extracts the maze from the field file */
void readMaze(char maze[], int row, int col, char file_name[]){

    char current;
    FILE *f;
    int i, j;

    f = fopen(file_name, "r");

    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++){
            current = fgetc(f);
    
            /* Eat spaces */
            while( !((current == '1') || (current == '0')) )
                current = fgetc(f);

            maze[col * i + j]  = current;
        }
    }

    fclose(f);
}


/* Output maze to screen */
void printMaze(char maze[], int row, int col){

    int i, j;

    printf("\n");
    for(i = 0; i < row; i++){
        for(j = 0; j < col; j++)
            printf("%c ", maze[col * i + j]);
        
        printf("\n");
    }
}


/* Wrapper function for finding maze endpoints and 
 * path traversal.  */ 
int solveMaze(char maze[], int row, int col){

    /* Step 1: Find maze entrance and exit, starting with the 
     * upper-left corner and moving clockwise */

    Point endpoints[2];
    int i, j, found = 0;

    /* Top wall */
    for(i = 0, j = 0; j < col && found < 2; j++){
        if(maze[i * col + j] == '0')
            endpoints[found++] = (Point) { i, j};
    }

    /* Right wall */
    for(i = 0, j = col - 1; i < row && found < 2; i++){
        if(maze[i * col + j] == '0')
            endpoints[found++] = (Point) { i, j};
    }   
   
    /* Bottom wall */
    for(i = row - 1, j = col - 1; j >= 0 && found < 2; j--){
        if(maze[i * col + j] == '0')
            endpoints[found++] = (Point) { i, j};
    }

    /* Left wall */
    for(i = row - 1, j = 0; i >= 0 && found < 2; i--){
        if(maze[i * col + j] == '0')
            endpoints[found++] = (Point) { i, j};
    }


    /* Step 2: Check possible moves on current tile */
    Point start = endpoints[0], exit = endpoints[1];

    return traverse(maze, row, col, start, exit);
}


/* Use DFS to traverse the path. Mark visited squares with
 * Xs and return the value 1 if a path is found from entrance
 * to exit. 
 */
int traverse(char maze[], int row, int col, Point current, Point exit){

    maze[current.x * col + current.y] = 'X';

    /* Found exit! Return true */
    if(current.x == exit.x && current.y == exit.y) return 1;


    Point possible_moves[] = { (Point) {current.x - 1, current.y },
                               (Point) {current.x + 1, current.y },
                               (Point) {current.x, current.y - 1 },
                               (Point) {current.x, current.y + 1 } };
    int i, x, y, found_exit;
    for(i = 0; i < 4; i++){
            x = possible_moves[i].x;
            y = possible_moves[i].y;

            if( isValid(x, 0, row-1) && isValid(y, 0, col-1) && maze[x * col + y] == '0'){
                if(traverse(maze, row, col, possible_moves[i], exit)) return 1;
            }
    }

    return 0;
}

