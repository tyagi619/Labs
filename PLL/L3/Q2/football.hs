-- import statements
import Data.List()
import System.IO.Unsafe ( unsafePerformIO ) 
import System.Random (randomRIO)
import Data.Text.Internal (mul)

-- list of participating teams
teams = ["BS","CM","CH","CV","CS","DS","EE","HU","MA","ME","PH","ST"]

-- SHuffles the teams list to generate draws
shuffle :: [a] -> IO [a]
shuffle teamList = 
    -- If the list contains only a single element
    if length teamList <= 1
        -- Return the list since there is no more shuffling possible
        then return teamList
    --Else if there is more than 1 element in the list 
    else do
    -- Generate a random number between 0 and length of teamList-1
    i <- randomRIO (0,length teamList - 1)
    -- Remove the ith element from the list and pass the remaining list to shuffle
    r <- shuffle (take i teamList ++ drop (i+1) teamList)
    -- Append the ith element to the result of shuffle
    return(teamList!!i : r)

{-# NOINLINE shuffledTeams #-}
-- Calls shuffle list and then stores the result of IO to shuffled teams
-- Adjacent teams in the shuffled list are paired for a match. So index of
-- teams paired are : (0,1), (2,3), (4,5), (6,7), (8,9), (10,11). The matches
-- are scheduled in the same order 
shuffledTeams = unsafePerformIO (shuffle teams)

-- Print the complete fixture for the first round
printFixture:: [[Char]]->Integer->Char->Integer->IO()
-- If the list of teams is empty return nothing
printFixture [] _ _ _ = do return()
-- If the list of teams is non-empty
-- (x:xs) -> list of remaining teams with x as head
-- date -> date for which the match has to be scheduled
-- session -> Morning or Evening session of the day 
-- teamcount -> count of number of teams that have been placed in the current match slot. Maximum of 2 teams per slot
printFixture (x:xs) date session teamcount  = do
    -- Print the team name at the front of list
    putStr x
    putStr " "
    -- If this team is the 2nd team in the slot and the session is Morning
    if teamcount==2 && session=='M'
    then do
        -- Print the date and morning time
        putStrLn ("   " ++ show date ++ "-12-2020   9:30")
        -- Call print fixture on remaining teams with same date for evening slot and teamcount=1
        printFixture xs date 'E' 1
    else
        -- If this team is 2nd team in the slot and session is Evening
        if teamcount==2 && session=='E'
        then do
            -- Print the date and evening time
            putStrLn ("   " ++ show date ++ "-12-2020   7:30")
            -- Call print fixture with next date and morning slot and teamcount=1
            printFixture xs (date+1) 'M' 1
        else
            -- This is the 1st team in slot
            -- Call print fixture with same date and session and teamcount=2
            printFixture xs date session 2

-- Get the index of the team in the shuffled list
-- The index uniquely identifies the date and time of the match for ith team
getIndex [] _ _ = error "No such team exists. Please try with a valid team name"
getIndex (x:xs) teamName idx 
    -- If x is the teamName, return index value
    | x==teamName = idx
    -- Otherwise call getIndex on remaining list and idx+1
    | otherwise = getIndex xs teamName (idx+1)

-- Print fixture for a particular team
printTeamFixture teams teamName = do
    -- get the index of the team in the match list
    let i = getIndex teams teamName 0
    -- If the index is odd
    if i `mod` 2 == 1
    then do
        -- set opponent team as team at index i-1
        let teamIdx1 = i-1
        -- set the current team as team at index i
        let teamIdx2 = i
        -- date of the match is (i/4) + 1. This can be proved mathematically
        let date = (i `div` 4) + 1
        -- If the index gives remainder >=2 with 4, then the match is for evening slot
        if i `mod` 4 >= 2
        then putStrLn (teams!!teamIdx1 ++ " " ++ teams!!teamIdx2 ++ "    " ++ show date ++ "-12-2020   7:30")
        -- Else match is for morning slot
        else putStrLn (teams!!teamIdx1 ++ " " ++ teams!!teamIdx2 ++ "    " ++ show date ++ "-12-2020   9:30")
    -- If index i is even
    else do
        -- set the current team as team at index i
        let teamIdx1 = i
        -- set the opponent team as team at index i+1
        let teamIdx2 = i+1
        -- get the date of the match by using index of team in matchlist
        let date = (i `div` 4) + 1
        -- If the index gives remainder >=2 with 4, then the match is for evening slot
        if i `mod` 4 >= 2
        then putStrLn (teams!!teamIdx1 ++ " " ++ teams!!teamIdx2 ++ "    " ++ show date ++ "-12-2020   7:30")
        -- Else match is for morning slot
        else putStrLn (teams!!teamIdx1 ++ " " ++ teams!!teamIdx2 ++ "    " ++ show date ++ "-12-2020   9:30")

-- Call this function to print fixtures
-- action="all" -> print complete fixture
-- action="teamName" -> print match details for particular team with name 'teamName'
fixture action
    | action=="all" = printFixture shuffledTeams 1 'M' 1
    | otherwise = printTeamFixture shuffledTeams action

-- Gets the next match after the particular date and time
nextMatch :: Integer->Float->IO()
nextMatch date time = do 
    -- Get start index of the 4 teams planned for the match at particular 'date'
    -- The 1st 4 teams are for day 1, next 4 for day 2, and last 4 for day 3
    let startIdx = fromIntegral (date-1) `mul` (4::Int)
    -- get shuffled list of teams
    let teams = shuffledTeams
    -- If date is between 1 and 3 and time less than 9:30, then the next match is the morning match for 'date'
    if date >=1 && date <= 3 && time < 9.30
    then do
        -- first team index
        let teamIdx1 = startIdx
        -- second team index
        let teamIdx2 = startIdx + 1
        -- print the match date and time
        putStrLn (teams!!teamIdx1 ++ " " ++ teams!!teamIdx2 ++ "    " ++ show date ++ "-12-2020   9:30")
    else do
        -- If date is between 1 and 3 and time is between morning and evening match time
        -- next match will be the evening match for 'date
        if date >=1 && date <= 3 && time >= 9.30 && time < 19.30
        then do
            -- first team
            let teamIdx1 = startIdx + 2
            -- second team
            let teamIdx2 = startIdx + 3
            -- print the match date and time
            putStrLn (teams!!teamIdx1 ++ " " ++ teams!!teamIdx2 ++ "    " ++ show date ++ "-12-2020   7:30")
        else do
            -- if date is between 1 and 2 and time in after evening match,
            -- next match is the morning match for (date+1) and hence date must be < 3 
            if date >= 1 && date < 3 && time >= 19.30
            then do
                -- first team
                let teamIdx1 = startIdx + 4
                -- second team
                let teamIdx2 = startIdx + 5
                -- print the next match date and time 
                putStrLn (teams!!teamIdx1 ++ " " ++ teams!!teamIdx2 ++ "    " ++ show (date+1) ++ "-12-2020   9:30")
            else
                -- Else there is no match after this date and time
                putStrLn "No First Round Match after this"