The program implements the Housing Problem

To run the program, enter the following command in terminal : ghci
Load the file in ghci -> :load housePlanner.hs

Some sample queries : 
1- design 1000 3 2    -> output : unused space = 0
2- design 730 1 1     -> output : unused space = 0
3- design 430 1 1     -> output : no possible design
4- design 2000 1 1    -> output : unused space = 636
5- design 2450 4 1    -> output : unused space = 0

The code takes at most 30s for each query.
Assumptions : 1- All bedrooms have same size.
              2- All Halls will have same size
              3- All Kitchens will have same size
              4- All Bathrooms will have same size

The code is well documented for understanding program logic