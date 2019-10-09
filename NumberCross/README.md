# Discrete Mathematics
>* Q: How to build and run the programs?
>
> - A: Follow this step
> - Step 1. Type "make clean" and then type "make" to build a program. 
> - Step 2. The programs names are united as "NumberCross". So type like "./NumberCross <puzzle_file_name>". 
> - Then, the program will show the solution for <puzzle_file_name>'s puzzle.


- Example:

input:    
    
    20 23 30 29 34 6 9 21 19
    8 2 1 8 1 3 5 7 6 18
    9 1 4 2 5 6 3 1 7 28
    3 5 1 4 9 1 3 9 1 8
    8 6 6 3 5 1 1 4 1 4
    8 6 6 2 6 8 3 3 9 31
    8 7 8 8 4 5 2 1 1 18
    4 8 3 5 5 2 1 2 8 24
    1 2 8 8 8 3 7 2 7 22
    8 3 9 5 9 2 1 4 9 35


Step 1:

    s21400350@peace:~/D_Math/NumberCross$ make clean
    rm *.o NumberCross formula
    
    s21400350@peace:~/D_Math/NumberCross$ make
    gcc -c -o NumberCross.o NumberCross.c
    gcc -o NumberCross NumberCross.o


Step 2:

    s21400350@peace:~/D_Math/NumberCross$ ./NumberCross test


output:    
    
    1 1 0 1 0 0 1 0 0 
    0 1 1 0 1 0 0 0 0 
    1 1 1 0 1 0 0 1 1 
    1 1 1 1 1 1 1 0 1 
    0 0 0 1 1 0 0 1 1 
    0 1 1 1 0 0 1 1 0 
    0 0 1 0 0 0 1 1 1 
    1 1 1 1 0 1 0 1 0 
    0 0 0 0 1 1 0 1 0 


