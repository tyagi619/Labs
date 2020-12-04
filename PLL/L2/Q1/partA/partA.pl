% Facts

parent(ram,bha).
parent(ram,bir).
parent(ram,sat).
parent(bha,nar).
parent(bha,par).
parent(sat,st).
parent(pre,st).
parent(sat,ju).
parent(sat,ch).
parent(rsh,ju).
parent(pre,ch).
parent(bir,bhu).
parent(bir,jy).
parent(sum,jy).
parent(sum,bhu).
parent(rsh,nar).
parent(rsh,par).
parent(x,pre).
parent(hz,sum).
male(ram).
male(bha).
male(bir).
male(sat).
male(nar).
male(par).
male(x).
male(bhu).
male(st).
female(ju).
female(ch).
female(jy).
female(sum).
female(pre).
female(rsh).
female(shti).

% Rules

% An uncle is a male relative who is a sibling of a parent 

% X is the uncle of Y if and only if
% X is the brother of Y's parent.
% In other words, X is the uncle of Y
% if X and Y's parent have a common parent
% and X is a male
uncle(X,Y) :-  ( 
                 parent(A,Y),               % A be the parent of Y
                 parent(B,A),parent(B,X),   % A and X must have a common parent
                 not(A=X),                  % A and X must not be same
                 male(X)                    % X must be a male
               ).
