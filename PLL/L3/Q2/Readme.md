The program implements the IITG Football problem

To run the program, enter the following command in terminal : ghci
Load the file in ghci -> :load football.hs

Some sample queries : 
1- fixture "all"     -> run this query first to generate all the fixtures
2- fixture "BS"      -> returns the match details of BS
3- nextMatch 1 13.25 -> return the next match after 1 dec 1:25 pm 

if a wrong team is entered in query 2, the code throws an error showing the message that "team name is not valid"

To generate another random fixture, run ->   :load football.hs
and try all the above queries to see the effect

The code is well documented for understanding program logic