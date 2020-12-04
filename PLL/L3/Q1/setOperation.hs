-- Import libraries to be used
import Data.List ( sort )
import System.IO ()

-- Store the sets as a list of numbers
set1 = [1,21,8,12,7,5]
set2 = [12,16,52,5,10,1,7]
set3 = []

-- Checks if given list is empty
isEmptySet :: [a] -> Bool
isEmptySet x = null x

-- Removes duplicate elements from a list
getUniqueElements :: Eq a => [a] -> [a]
-- If list is empty return the list
getUniqueElements [] = []
-- else if there are elements
getUniqueElements (x:xs) = x : [elem | elem <- getUniqueElements(xs), elem /= x]

-- Performs union operation on sorted list
-- If both input list are empty, return empty list
unionSet :: Ord a => [a] -> [a] -> [a]
unionSet [] [] = []
-- If first list is empty, return second list
unionSet [] (y:ys) = y:ys
-- If second list is empty, return first list
unionSet (x:xs) [] = x:xs
-- If no list is empty
unionSet (x:xs) (y:ys) 
    -- If both elements are equal,add only one of them to union list
    | x==y = x : unionSet xs ys
    -- If x<y, then add x to the union list and call union on remaining elements of x
    | x<y = x : unionSet xs (y:ys)
    -- If x>y, then add y to the union list and call union on remaining elements of y
    | otherwise = y : unionSet (x:xs) ys

-- Calls unionSet after sorting lists. 
-- Call this function to perform union operation

union :: Ord a => [a] -> [a] -> [a]
union x y = getUniqueElements (unionSet (sort (getUniqueElements x)) (sort (getUniqueElements y)))


intersectSet :: Ord a => [a] -> [a] -> [a]
-- If both sets are empty, return empty set
intersectSet [] [] = []
-- If first set is empty, return empty set
intersectSet [] _ = []
-- If second set is empty, return empty set
intersectSet _ [] = []
-- If none of the lists are empty
intersectSet (x:xs) (y:ys)
    -- If both elements are equal, add x to the output set
    | x==y = x : intersectSet xs ys
    -- If x<y, omit x from the output set
    | x<y = intersectSet xs (y:ys)
    -- If x>y, omit y from the list
    | otherwise = intersectSet (x:xs) ys

-- Calls subtractSet after sorting lists
-- Call this function for X-Y operation on set
intersection :: Ord a => [a] -> [a] -> [a]
intersection x y = getUniqueElements (intersectSet (sort (getUniqueElements x)) (sort (getUniqueElements y)))

-- If both sets are empty, return empty set
subtractSet :: Ord a => [a] -> [a] -> [a]
subtractSet [] [] = []
-- If first set is empty, return empty set
subtractSet [] (_:_) = []
-- If second set is empty, add all elements of first list to ans list
subtractSet (x:xs) [] = x:xs
-- If none of the lists are empty
subtractSet (x:xs) (y:ys)
    -- If both elements are equal, omit the element x from the output set
    | x==y = subtractSet xs ys
    -- If x<y, add x to the output set
    | x<y = x : subtractSet xs (y:ys)
    -- If x>y, call subtractSet again after omitting y from second list
    | otherwise = subtractSet (x:xs) ys

-- Calls subtractSet after sorting lists
-- Call this function for X-Y operation on set
subtraction :: Ord a => [a] -> [a] -> [a]
subtraction x y = getUniqueElements (subtractSet (sort (getUniqueElements x)) (sort (getUniqueElements y)))

-- If set Y is empty return empty list
addSet _ [] = []
-- Otherwise add x to each element of Y
addSet x (y:ys) = (x+y): addSet x ys

-- Calls addSet to add x to all elements of Y
-- Call this function for X+Y operation on set
addition :: [Int]->[Int]->[Int]
-- If both X and Y are empty, return empty list
addition [] [] = []
-- If either of X or Y is empty return empty list
addition [] (_:_) = []
addition (_:_) [] = []
addition (x:xs) (y:ys) = getUniqueElements (addSet x (y:ys) ++ addition xs (y:ys))
