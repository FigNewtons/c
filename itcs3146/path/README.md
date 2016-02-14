                ITCS 3146: Assigment 1
                    The Pathfinder

            Author: Daniel Gruszczynski
            Date:   February 6, 2016

What is it?
----------------

Given a plaintext representation of a maze stored in a file (i.e. maze.txt), 
the pathfinder determines whether or not a path of 0s exist between the two 
endpoints. Here, 1s represent walls and the only valid moves are up, down, 
left, and right. The output displays the paths tried by the program as well 
as a statement that says whether or not a path was found.

Description
----------------

This project contains the following files:
    - path.c     (the main program)
    - genmaze.c  (maze generator)
    - maze.txt   (example maze)
    
path.c 

    Data structures 
        - char array (to store maze; explicit size is determined by user input)
        - struct Point (containing x and y coordinates for path traversal)

    Algorithm
        - Take user input 
            - Comma-separated size of the maze, and maze filename
        - Do basic input validation 
            - Mazes must be sized between 5x5 and 100x100, and filename 
              must exist  
        - Read the maze into the char array 
            - Ignoring all characters that are not 0 and 1
        - Attempt to solve the maze
            - Starting at (0,0), search clockwise along outer edge 
              of maze to find the two endpoints
            - Use a recursive depth-first search to traverse maze, marking
              Xs for visited tiles. We store the current and possible moves
              as Points. 
                - Initialize the search using first endpoint
                - Call helper function traverse which handles the maze
                  updating, exit checking, and searching for possible moves
                  (left, right, down, up). Return 1 if the current Point
                  matches the exit coordinates, and return 0 if current Point
                  yields a dead end (no more possible moves)
        - Print maze and statement for whether or not path was found 

genmaze.c : Modified version of the maze generator provided for the assignment.
            Takes the number of rows, number of columns, and destination 
            filename as command-line arguments. Outputs the generated maze 
            and writes it to the designated file.

Usage
----------------

To generate a maze, compile genmaze.c
> gcc -o genmaze genmaze.c

Then, supply your arguments
> ./genmaze 20 20 testmaze.txt

This creates a randomly generated 20x20 maze and writes it to testmaze.txt


To run the pathfinder, first compile path.c
> gcc -o path path.c

Then, simply run 
> ./path

Here is the example output for maze.txt:

Please enter the size of the maze.
Values must be between 5 and 100, inclusive. (e.g. 10,15)
9,10
Type in the name of the file containing the maze
maze.txt

1 1 1 1 1 X 1 1 1 1 
1 1 1 0 0 X X X X 1 
1 1 1 1 0 1 1 1 X 1 
1 1 0 0 0 1 1 X X 1 
1 1 0 0 1 1 1 X 1 1 
1 1 0 1 1 1 0 X 1 1 
1 1 0 1 1 1 1 X 1 1 
1 1 1 1 1 1 X X 0 1 
1 1 1 1 1 1 X 1 1 1 

Path found.

