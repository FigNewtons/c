                ITCS 3146: Assigment 2
        Type Justification in Word Processing

            Author: Daniel Gruszczynski
            Date:   March 16, 2016

What is it?
----------------

Given a text file and the number of characters per line, the program 
outputs each paragraph in a type-justified format. 


Description
----------------

This project contains the following files:
    - justify.c (the main program)
    - queue.h   (queue implementation)
    
Data structure
    - Queue (linked-list implementation): I exploit the FIFO property
      to feed in word tokens and output them in the same order of
      occurrence.

Algorithm

    - Take user input (valid file name and no. of characters per line)
    - Tokenize the file contents and insert into the queue
    - Pass the queue and the no. of characters per line to the 
      justify() method. Output the justified text.

Design choices

    The queue uses a linked list and has all of the necessary methods to handle
    its  creation,  use,  and destruction (including dynamically allocating and
    freeing  memory  as  needed). The queue stores a pointer to the front node,
    the  back  node,  and  its length. Each node contains just the string and a
    pointer  to  the next word. When enqueued, the word is copied and this copy
    is  what's  referenced  by the node; this gives the queue full control over
    its internal state. 

    I  chose  to  read  the  file line by line as opposed to one character at a
    time.  This  allowed  me  to use strtok() on tabs and whitespaces. The only
    tricky  part  was  stripping  the trailing newline on the last token of the
    current  line.  For counting purposes, this means that if the next token is
    just "\n", then this is a new paragraph. 

    Combining  the above comments, I chose to use a single queue for the entire
    file. This turned out to be ideal for two reasons: 

    (1)  I  did  not have to worry about how many paragraphs the file contained
    (so less wasted space), and 

    (2) I could treat "\n\n" as a word token signaling a new paragraph. 

    So  how does the justifying work? I try to fit as many words in the current
    line  as  possible.  If  we  have the first word of the line, then the min.
    space needed is the strlen(word). Otherwise, we must include strlen(word) +
    1 for a space to the left of the word. Thus, we dequeue words into a buffer
    until  the  amount  of  space  left can't accomodate the next word. At this
    point,  we  compute  the  number  of spaces leftover needed to complete the
    line.  If  there's  excess,  we  distribute the spaces evenly (from left to
    right)  and  output  accordingly.  We  then  reset  the buffer and sentinel
    variables  for  the  next  line.  If we encounter "\n\n", then we empty the
    buffer  and  output  the last line of the current paragraph and begin a new
    paragraph.  This  continues  until the queue is empty, which means we clear
    the buffer/output the remaining words and finish. 

Usage
----------------

To compile, type 
> gcc -o justify justify.c

Then, simply run 
> ./justify


