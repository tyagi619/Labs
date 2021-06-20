% intermediate gate interconnections and corresponding distance
path(g1,g5,4).
path(g2,g5,6).
path(g3,g5,8).
path(g4,g5,9).
path(g1,g6,10).
path(g2,g6,9).
path(g3,g6,3).
path(g4,g6,5).
path(g5,g7,3).
path(g5,g10,4).
path(g5,g11,6).
path(g5,g12,7).
path(g5,g6,7).
path(g5,g8,9).
path(g6,g8,2).
path(g6,g12,3).
path(g6,g11,5).
path(g6,g10,9).
path(g6,g7,10).
path(g7,g10,2).
path(g7,g11,5).
path(g7,g12,7).
path(g7,g8,10).
path(g8,g9,3).
path(g8,g12,3).
path(g8,g11,4).
path(g8,g10,8).
path(g10,g15,5).
path(g10,g11,2).
path(g10,g12,5).
path(g11,g15,4).
path(g11,g13,5).
path(g11,g12,4).
path(g12,g13,7).
path(g12,g14,8).
path(g15,g13,3).
path(g13,g14,4).
path(g14,g17,5).
path(g14,g18,4).
path(g17,g18,8).

% start gates. Marks the start gates
start(g1).
start(g2).
start(g3).
start(g4).

% end gates. Mark the end gates
end(g17).

% calculates length of list
length_list(0,[]).
% pop one element at a time from list and update the size by 1
length_list(L+1, [H|T]) :- length_list(L,T).

% Prints the path given as a list
printAllPath([Gate|Tail]) :- (
    % get length of list and store the size in L
    length_list(X,[Gate|Tail]),
    L is X,
    % open the file in append to write the result
    open('allPath.txt', append, Stream),
    write(Stream, Gate),
    % print the current gate
    write(Gate),
    (
        % if the list has only 1 element print new line character
        % else print and arrow and call printPath to print remaining gates in path
        not(L==1) -> (
        	write(" -> "),
        	write(Stream," -> "),
        	% close the file after writing
    		close(Stream),
        	printAllPath(Tail)
        );
        % add newline character since one path is complete
        nl(Stream),
        % close the file after writing
    	close(Stream),
        writeln("")
    )
).

% Performs DFS to find all possible paths
dfs(X,Visited,Distance) :- (
    % if X is not visited currently
    not(member(X,Visited)) -> (
        % add the gate X to the visited list
        append(Visited,[X],VisitedUpdated),
        (
            % if X is the end gate
            end(X) -> ( 
                % print the current path that was followed till X
                printAllPath(VisitedUpdated)
            ) ;
            % else if X is not the end gate
            forall(
                % loop for all path starting from X
                path(X,Gate,Dis);path(Gate,X,Dis),
                (
                    % New distance = old distance + distance of the next path
                    NewDistance is Distance + Dis,
                    % call dfs starting from Gate
                    dfs(Gate,VisitedUpdated,NewDistance)
                )
            )
        )
    ) ; true % else return true
).

% finds all possible route from start gates to end gates
allPath() :- (
    % open the output file and clear it
    open('allPath.txt',write, Stream),
    write(Stream, ""),
    % close the file after clearing it
    close(Stream),
    % loop for all possible start gates
    forall(
        start(X),
        % call dfs to find all possible paths
        dfs(X,[],0)
    )
).

% Prints the path given as a list
printPath([Gate|Tail]) :- (
    % get length of list and store the size in L
    length_list(X,[Gate|Tail]),
    L is X,
    % print the current gate
    write(Gate),
    (
        % if the list has only 1 element print new line character
        % else print and arrow and call printPath to print remaining gates in path
        not(L==1) -> (write(" -> "),printPath(Tail));writeln("")
    )
).


% visits all possible paths from start to end and stores the 
% optimal path based on the distance from start to end 
optimalEscapeRoute(X,Visited,Distance) :- (
    % if X has not been visited yet
    not(member(X,Visited)) -> (
        % add X to the visited list
        append(Visited,[X],VisitedUpdated),
        (
            % if X is the end gate
            end(X) -> ( 
                % get the current Minimum distance from start to end
                nb_getval(minDistance,CurMinDistance),
                (
                    % if current minimum distance is greater than the distance
                    (CurMinDistance > Distance) -> (
                        % update the minimum distance to distance
                        nb_setval(minDistance,Distance),
                        % update the optimal route to the current route
                        nb_setval(visitedPlaces,VisitedUpdated)
                    )   ; true % else return true
                )
            ) ;
            % else if X is not the end gate
            % loop for all paths starting from X
            forall(
                path(X,Gate,Dis);path(Gate,X,Dis),
                (
                    % update the new distance
                    NewDistance is Distance + Dis,
                    % call optimalEscapeRoute to find route starting from Gate 
                    optimalEscapeRoute(Gate,VisitedUpdated,NewDistance)
                )
            )
        )
    ) ; true % else return true
).

% Find the optimal path from start to end based on the distance
optimal() :- (
    % set minimum distance to arbitary large value
    nb_setval(minDistance,10000),
    % gates that have been visited during the optimal path
    nb_setval(visitedPlaces,[]),

    % starting from all start gates, iterate over all possible paths
    % and get the optimal path based on the distance from start to end
    forall(
        start(X),
        optimalEscapeRoute(X,[],0)
    ),

    % get the minimum distance
    nb_getval(minDistance, AnsDistance),
    % get the gates in the optimal path
    nb_getval(visitedPlaces,AnsStops),

    % print the optimal distance from start to end
    write("Optimal Distance : "),
    writeln(AnsDistance),

    % print the optimal route 
    printPath(AnsStops)
).

% If there is only one gate in path and the gate
% is both the start and end gate. This function
% handles that special case
checkPath([Gate]) :- (
    end(Gate)
).

% Validates the path checking if each consecutive
% gates have a path between them and the last gate
% is the end gate
checkPath([Gate1,Gate2|Tail]) :- (
    % get the length of the current list of remaining gates in path
    length_list(X,[Gate1,Gate2|Tail]),
    % X is a expression of sum. Evaluate the expression to get the length 
    L is X,
    (
        % if length of list is 2
        (L==2) ->( 
            % check if there is a path between the 2 gates
            (path(Gate1,Gate2,_);path(Gate2,Gate1,_)),
            % the last gate should be a end gate
            end(Gate2)
        );
        % if length of list is greater than 2
        (
            % check if there is a path between the two consecutive gates
            (path(Gate1,Gate2,_);path(Gate2,Gate1,_)),
            % call checkPath to validate the remaining path starting from Gate2
            checkPath([Gate2|Tail])
        )
    )
).

% Check if the given path is valid or not
% The path is given as a list
valid([ StartGate | Tail ]) :- (
    (
        % check that the first gate is the start gate
        start(StartGate),
        % call checkPath that validates the rest of the path
        checkPath([ StartGate | Tail ]),
        writeln("Valid Path")
    ) ;
    writeln("Invalid Path")
).
