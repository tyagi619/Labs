The program implements the basic set operations namely - empty,union,intersection,subtraction and addition

To run the program, enter the following command in terminal : ghci
Load the file in ghci -> :load setOperation.hs

Some sample queries : 
1- union [1,2,3] [2,3,4]              ->    output : [1,2,3,4]
2- intersection [1,2,3] [2,3,4]       ->    output : [2,3]
3- subtraction [1,2,3] [2,3,4]        ->    output : [1]
4- addition [1,2,3] [2,3,4]           ->    output : [3,4,5,6,7]
5- isEmptySet []                      ->    output : True
6- isEmptySet [1,2]                   ->    output : False 

The code throws an exception if the operation cannot be performed on a particular set type

The code is well documented for understanding program logic