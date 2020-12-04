The program finds:
a) all possible escape path from the prison
b) optimal escape path from the prision based on minimum distance policy
c) if a given escape path is valid or not

To run the program : swipl -s escape.pl

Some sample queries : 
1- allPath().   (finds all possible escape paths from prison. Writes the result to terminal as well as "allPath.txt")
2- optimal().   (finds optimal escape path from prison)
3- valid([g4,g6,g7,g8,g12,g14,g17]).
4- valid([g1,g17]).
5- valid([g4,g6,g7,g8,g12,g14,g12,g14,g17]).   

The code is well documented for understanding program logic
