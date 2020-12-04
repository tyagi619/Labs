% list of buses
bus(123, amingaon, jalukbari, 14.5, 15, 10, 50).
bus(133, jalukbari, paltanbazar, 16, 18, 10, 6).
bus(100, amingaon, paltanbazar, 15, 17.5, 30, 62).
bus(171, paltanbazar, panbazar, 12, 13.5, 6, 12).
bus(162, amingaon, panbazar, 9,11.5, 32,80).
bus(182,panbazar,railwaystation,16,16.5,7,8).

% calculates length of list
length_list(0,[]).
% pop one element at a time from list and update the size by 1
length_list(L+1, [H|T]) :- length_list(L,T).

% Print the last place in the path
printPath([Place]) :- (
    writeln(Place)
).

% Print the path along with bus ID
printPath([Place,BusId|Tail]) :- (
    write(Place),
    write(","),
    write(BusId),
    write(" -> "),
    printPath(Tail)
).

% update the distance, time, cost and route for optimal path
updateOptimalCost(Distance,Cost,Time,Route) :- (
    % get the current minimum cost from global variable
    nb_getval(minCost,CurMinCost),
    % if current minimum time is greater than time
    (CurMinCost > Cost) -> (
        % set the distance to distance
        nb_setval(minDistance,Distance),
        % set the cost to the current cost encountered
        nb_setval(minCost,Cost),
        % set the minimum time to current time taken
        nb_setval(minTime,Time),
        % update optimal path to current path taken
        nb_setval(visitedPlaces,Route)
    )   ; true % else return true
).

% When the source is same as destination, a possible path has been found
% Update the optimal cost and other parameters
dfsCost(X,X,Route,Distance,Time,Cost,_) :- (
    % append the ending place to the list
    append(Route,[X],RouteUpdated),
    % Update the optimal distance and other variables
    updateOptimalCost(Distance,Cost,Time,RouteUpdated)
).

% performs dfs and updates optimal path based on cost
dfsCost(X,Y,Route,Distance,Time,Cost,PrevStopTime) :- (
    % if X is not visited on the current route
    not(member(X,Route)) -> (
        % add X to the current path
        append(Route,[X],RouteUpdated),
        (
		    forall(
		        % loop over all buses starting from X
		        bus(BusId,X,Destination,DepTime,ArrTime,Dis,JourneyCost),
		        (
                    % append the busId to the route
		            append(RouteUpdated,[BusId],NewRoute),
                        
		            % update the distance after taking the bus
		            NewDistance is Distance + Dis,
		            % update the cost after taking the bus
		            NewCost is Cost + JourneyCost,

		            % if this is the 1st bus, the passenger does not wait for the bus
		            % else the passenger has to wait from the time he got off from previous
		            % bus till the time the next bus comes
		            (not(PrevStopTime == -1) -> (WaitTime is DepTime - PrevStopTime);WaitTime is 0),
		            
		            % if wait time is less than 0, that indicates that there is a change of
		            % day and add 24 to get the actual wait time.
		            (WaitTime < 0 -> NewWaitTime is 24 + WaitTime;NewWaitTime is WaitTime),
		            
		            % Journey time is the time travelled on the bus
		            JourneyTime is ArrTime - DepTime,
		            % if journey time is less than 0, that indicates there is a change of
		            % day and add 24 to get the actual journey time
		            (JourneyTime < 0 -> NewJourneyTime is 24 + JourneyTime;NewJourneyTime is JourneyTime),
		            
		            % Update the total time of journey by adding the journey time and wait time
		            NewTime is Time + NewJourneyTime,
		            FinalTime is NewTime + NewWaitTime,
		            
		            %call dfs now with the updated parameter
		            dfsCost(Destination,Y,NewRoute,NewDistance,FinalTime,NewCost,ArrTime)
		        )
		    )
        )
    )   ; true
).

% find the optimal path based on cost
optimalCost(X,Y) :- (
            % set distance travelled on optimal path to 0
            nb_setval(minDistance,0),
            % set time taken on optimal path to 0
            nb_setval(minTime,0),
            % set minimum cost to arbitary large value
            nb_setval(minCost,10000),
            % set the places visited on optimal path to empty list
            nb_setval(visitedPlaces,[]),

            % find optimal path based on distance
            dfsCost(X,Y,[],0,0,0,-1),

            % get the values of the global values
            nb_getval(minDistance,AnsDistance),
            nb_getval(minTime,AnsTime),
            nb_getval(minCost,AnsCost),
            nb_getval(visitedPlaces,AnsRoute),

            % if the route list is empty, no path exists
            length_list(Len,AnsRoute),
            L is Len,
            ((L==0) -> false;true),

            % print the output
            writeln("Optimal Cost :"),
            printPath(AnsRoute),
            write("Distance = "),
            write(AnsDistance),
            write(" , Time = "),
            write(AnsTime),
            write(" , Cost = "),
            writeln(AnsCost)
).

% update the distance, time, cost and route for optimal path
updateOptimalTime(Distance,Cost,Time,Route) :- (
    % get the current minimum time from global variable
    nb_getval(minTime,CurMinTime),
    % if current minimum time is greater than time
    (CurMinTime > Time) -> (
        % set the distance to distance
        nb_setval(minDistance,Distance),
        % set the cost to the current cost encountered
        nb_setval(minCost,Cost),
        % set the minimum time to current time taken
        nb_setval(minTime,Time),
        % update optimal path to current path taken
        nb_setval(visitedPlaces,Route)
    )   ; true % else return true
).

% When the source is same as destination, a possible path has been found
% Update the optimal time and otheer parameters
dfsTime(X,X,Route,Distance,Time,Cost,_) :- (
    % append the ending place to the list
    append(Route,[X],RouteUpdated),
    % Update the optimal distance and other variables
    updateOptimalTime(Distance,Cost,Time,RouteUpdated)
).

% performs dfs and updates optimal path based on time
dfsTime(X,Y,Route,Distance,Time,Cost,PrevStopTime) :- (
    % if X is not visited on the current route
    not(member(X,Route)) -> (
        % add X to the current path
        append(Route,[X],RouteUpdated),
        (
            forall(
                % loop over all buses starting from X
                bus(BusId,X,Destination,DepTime,ArrTime,Dis,JourneyCost),
                (
                    % append the busId to the route
                    append(RouteUpdated,[BusId],NewRoute),

                    % update distance after taking the bus
                    NewDistance is Distance + Dis,
                    % update cost of journey after taking the bus
                    NewCost is Cost + JourneyCost,

                    % if this is the 1st bus, the passenger does not wait for the bus
                    % else the passenger has to wait from the time he got off from previous
                    % bus till the time the next bus comes
                    (not(PrevStopTime == -1) -> (WaitTime is DepTime - PrevStopTime);WaitTime is 0),
                    
                    % if wait time is less than 0, that indicates that there is a change of
                    % day and add 24 to get the actual wait time.
                    (WaitTime < 0 -> NewWaitTime is 24 + WaitTime;NewWaitTime is WaitTime),
                    
                    % Journey time is the time travelled on the bus
                    JourneyTime is ArrTime - DepTime,
                    % if journey time is less than 0, that indicates there is a change of
                    % day and add 24 to get the actual journey time
                    (JourneyTime < 0 -> NewJourneyTime is 24 + JourneyTime;NewJourneyTime is JourneyTime),
                    
                    % Update the total time of journey by adding the journey time and wait time
                    NewTime is Time + NewJourneyTime,
                    FinalTime is NewTime + NewWaitTime,

                    %call dfs now with the updated parameter
                    dfsTime(Destination,Y,NewRoute,NewDistance,FinalTime,NewCost,ArrTime)
                )
            ) 
        ) 
    )   ; true
).

% calculates optimal path based on time
optimalTime(X,Y) :- (
            % set distance travelled on optimal path to 0
            nb_setval(minDistance,0),
            % set minimum time to arbitary large value
            nb_setval(minTime,10000),
            % set cost encountered on optimal path to 0
            nb_setval(minCost,0),
            % set the places visited on optimal path to empty list
            nb_setval(visitedPlaces,[]),

            % find optimal path based on time
            dfsTime(X,Y,[],0,0,0,-1),

            % get the values of global variables
            nb_getval(minDistance,AnsDistance),
            nb_getval(minTime,AnsTime),
            nb_getval(minCost,AnsCost),
            nb_getval(visitedPlaces,AnsRoute),

            % if the route list is empty, no path exists
            length_list(Len,AnsRoute),
            L is Len,
            ((L==0) -> false;true),
            
            % print the output
            writeln("Optimal Time :"),
            printPath(AnsRoute),
            write("Distance = "),
            write(AnsDistance),
            write(" , Time = "),
            write(AnsTime),
            write(" , Cost = "),
            writeln(AnsCost)
).

% update the distance, time, cost and route for optimal path
updateOptimalDistance(Distance,Cost,Time,Route) :- (
    % get Current minimum distance
    nb_getval(minDistance,CurMinDistance),
    % if current minimum distance is greater than distance
    (CurMinDistance > Distance) -> (
        % set the minimum distance to distance
        nb_setval(minDistance,Distance),
        % set the cost to the current cost encountered
        nb_setval(minCost,Cost),
        % set the time taken to current time taken
        nb_setval(minTime,Time),
        % update optimal path to current path taken
        nb_setval(visitedPlaces,Route)
    )   ; true % else return true
).

% When the source is same as destination, a possible path has been found
% update the optimal distance and other parameters
dfsDistance(X,X,Route,Distance,Time,Cost,_) :- (
    % append the ending place to the list
    append(Route,[X],RouteUpdated),
    % Update the optimal distance and other variables
    updateOptimalDistance(Distance,Cost,Time,RouteUpdated)
).

% performs dfs and updates optimal path based on distance
dfsDistance(X,Y,Route,Distance,Time,Cost,PrevStopTime) :- (
    % if X is not visited on the current route
    not(member(X,Route)) -> (
        % add X to the current path
        append(Route,[X],RouteUpdated),
        (
            forall(
                % loop over all buses starting from X
                bus(BusId,X,Destination,DepTime,ArrTime,Dis,JourneyCost),
                (   
                    % append the busId to the route
                    append(RouteUpdated,[BusId],NewRoute),

                    % update the distance after taking the bus
                    NewDistance is Distance + Dis,
                    % update the cost after taking the bus
                    NewCost is Cost + JourneyCost,

                    % if this is the 1st bus, the passenger does not wait for the bus
                    % else the passenger has to wait from the time he got off from previous
                    % bus till the time the next bus comes
                    (not(PrevStopTime == -1) -> (WaitTime is DepTime - PrevStopTime);WaitTime is 0),
                    
                    % if wait time is less than 0, that indicates that there is a change of
                    % day and add 24 to get the actual wait time.
                    (WaitTime < 0 -> NewWaitTime is 24 + WaitTime;NewWaitTime is WaitTime),
                    
                    % Journey time is the time travelled on the bus
                    JourneyTime is ArrTime - DepTime,
                    % if journey time is less than 0, that indicates there is a change of
                    % day and add 24 to get the actual journey time
                    (JourneyTime < 0 -> NewJourneyTime is 24 + JourneyTime;NewJourneyTime is JourneyTime),
                    
                    % Update the total time of journey by adding the journey time and wait time
                    NewTime is Time + NewJourneyTime,
                    FinalTime is NewTime + NewWaitTime,

                    %call dfs now with the updated parameter
                    dfsDistance(Destination,Y,NewRoute,NewDistance,FinalTime,NewCost,ArrTime)
                )
            ) 
        )
    ) ; true
).

% calculates optimal path based on distance
optimalDistance(X,Y) :- (
            % set minimum Distance to arbitary large value
            nb_setval(minDistance,10000),
            % set time taken on optimal path to 0
            nb_setval(minTime,0),
            % set cost encountered on optimal path to 0
            nb_setval(minCost,0),
            % set the places visited on optimal path to empty list
            nb_setval(visitedPlaces,[]),

            % call dfs to calculate the optimal path based on distance
            dfsDistance(X,Y,[],0,0,0,-1),

            %get the values of the global variables
            nb_getval(minDistance,AnsDistance),
            nb_getval(minTime,AnsTime),
            nb_getval(minCost,AnsCost),
            nb_getval(visitedPlaces,AnsRoute),
            
            % if the route list is empty, no path exists
            length_list(Len,AnsRoute),
            L is Len,
            ((L==0) -> false;true),

            % print the output
            writeln("Optimal Distance :"),
            printPath(AnsRoute),
            write("Distance = "),
            write(AnsDistance),
            write(" , Time = "),
            write(AnsTime),
            write(" , Cost = "),
            writeln(AnsCost)
).

% finds a route along with the busID from X to Y
route(X,Y) :- (
        (
            % calculate optimal path based on distance
            optimalDistance(X,Y),
            % calculate optimal path based on time
            optimalTime(X,Y),
            % calculate optimal path based on cost
            optimalCost(X,Y)
        );
        writeln("No Path exists")
).

