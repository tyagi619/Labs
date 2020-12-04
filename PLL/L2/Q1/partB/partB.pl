% Facts

% parent predicate
parent(jatin,avantika).
parent(jolly,jatin).
parent(jolly,katappa).
parent(manisha,avantika).
parent(manisha,shivkami).
parent(bahubali,shivkami).

% male predicate
male(katappa).
male(jolly).
male(bahubali).

% female predicate
female(shivkami).
female(avantika).

% Rules

% Half Sister has no blood relation but is related through the marriage 
% of one of their parents

% X is the half sister of Y if and only if
% X is a female and X and Y have a common parent
% X and Y must also have a non common parent other
% than the common parent.
% For eg: if A and B are parent of X and 
% A and C are parent of Y given all A,B,C are
% distinct, then X is a half sister of Y if 
% X is a female

halfsister(X,Y) :- ( 
                     female(X),               % X should be a female
                     parent(A,X),parent(A,Y), % X an Y must have a common parent A
                     parent(B,X),             % X must have a non common parent B 
                     parent(C,Y),             % Y must have a non common parent C
                     not(A=B),                % A, B and C must be distinct
                     not(B=C),
                     not(A=C)
                   ).