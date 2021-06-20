import Data.List(sortBy)
import System.IO()

--Data Structure for storing results of search1 -> bedroom,hall,kitchen and bathroom  
data Structure1 = Structure1 {
    bedroomDim :: [Integer],  -- dimensions of bedroom in design
    hallDim :: [Integer],     -- dimensions of hall in design
    kitchenDim :: [Integer],  -- dimensions of kitchen in design
    bathroomDim :: [Integer], -- dimensions of bathroom in design
    area1 :: Integer          -- combined area of bedroom,hall,kitchen and bathroom
}

-- Data STructure for storing results for search2 -> balcony,garden
data Structure2 = Structure2 {
    balconyDim :: [Integer], -- dimensions of balcony in design
    gardenDim :: [Integer],  -- dimensions of garden in design
    area2 :: Integer         -- combined area of balcony and garden
}

-- Data Structure for storing final design plan including all components
data FinalDesignPlan = FinalDesignPlan {
    bedroomDims :: [Integer],  -- dimensions of bedroom in design
    hallDims :: [Integer],     -- dimensions of hall in design
    kitchenDims :: [Integer],  -- dimensions of kitchen in design
    bathroomDims :: [Integer], -- dimensions of bathroom in design
    balconyDims :: [Integer],  -- dimensions of balcony in design
    gardenDims :: [Integer],   -- dimensions of garden in design
    areaNet :: Integer,        -- combined area of all the components in design  
    unusedArea :: Integer      -- unused area in the design
}

-- Custom sort function to sort the list of 'Structure1' elements based on increasing area
sortOrderStruct1 elem1 elem2
    | area1 elem1 <= area1 elem2 = LT    -- If area of elem1 <= area of elem2, then return Less Than
    | otherwise = GT                     -- else return Greater Than

-- Custom sort function to sort the list of 'Structure2' elements based on decreasing area
sortOrderStruct2 elem1 elem2
    | area2 elem1 <= area2 elem2 = GT    -- If area of elem1 <= area of elem2, then return Greater Than
    | otherwise = LT                     -- else return Less Than

-- search all possible gardens with area less than remArea
-- (x:xs) -> list of room dimensions. Here x is the dimension of garden
-- (y:ys) -> list of room count. Here y is the number of gardens
-- remArea -> area remaining which is need to be filled
-- elemStruct -> type 'Structure2'. It stores the dimension of balcony and area of balcony
-- mode -> Used to prevent overlapping of cases
searchGarden (x:xs) (y:ys) remArea elemStruct mode = do 
    let gardenArea = (x!!0)*(x!!1)*y              -- garden area with dimension x=[l,b]
    let newRemArea = remArea - gardenArea         -- area remaining after adding the garden
    let dimBalcony = balconyDim elemStruct        -- dimension of balcony
    if x!!0 <= 20 && x!!1 <= 20 && newRemArea>=0  -- if the dimensions of garden is less than max possible and area remaining is a non negative value
    then do
        -- Create a instance of 'Structure2' with the dimension of balcony and garden the the total area of the two
        let elemStructNew = Structure2{balconyDim = dimBalcony,gardenDim = x,area2 = gardenArea + area2 elemStruct}
        -- If mode is 0, call search garden with garden.length + 1 and then with garden.width + 1
        if mode == 0
        then do
            -- try other possible choices of garden by increasing the dimensions one at a time
            let possibleDesign1 = searchGarden ([x!!0 + 1,x!!1]:xs) (y:ys) remArea elemStruct 0
            let possibleDesign2 = searchGarden ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
            -- return the current design choice and the one returned from searchGarden
            [elemStructNew] ++ possibleDesign1 ++ possibleDesign2
        -- else only call search garden with garden.width + 1
        else do
            -- try other possible choices of garden by increasing the width
            let possibleDesign1 = searchGarden ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
            -- return the current design choice and the one returned from searchGarden
            [elemStructNew] ++ possibleDesign1
    else []  -- else return an empty list since the current design choice is invalid

-- search all possible gardens with area less than remArea
-- (x:xs) -> list of room dimensions. Here x is the dimension of balcony
-- (y:ys) -> list of room count. Here y is the number of balcony
-- remArea -> area remaining which is need to be filled
-- mode -> Used to prevent overlapping of cases
searchBalcony (x:xs) (y:ys) remArea mode = do
    let balconyArea = (x!!0)*(x!!1)*y          -- balcony area with dimension x=[l,b]
    let newRemArea = remArea -  balconyArea    -- area remaining after adding the balcony
    if x!!0 <= 10 && x!!1<=10 && newRemArea>=0 -- if the dimensions of balcony is less than max possible and area remaining is a non negative value
    -- Create a instance of 'Structure2' with the dimension of balcony and area of the balcony
    then do
        let elemStructNew = Structure2{balconyDim = x,gardenDim = [],area2 = balconyArea}
        -- Call searchGarden with current choice of balcony dimensions
        let possibleDesign = searchGarden xs ys newRemArea elemStructNew 0
        -- If mode is 0, call searchBalcony with balcony.length + 1 and then with balcony.width + 1
        if mode == 0
        then do
            -- try other possible choices of balcony by increasing the dimensions one at a time
            let possibleDesign1 = searchBalcony ([x!!0 + 1,x!!1]:xs) (y:ys) remArea 0
            let possibleDesign2 = searchBalcony ([x!!0,x!!1 + 1]:xs) (y:ys) remArea 1
            -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign2 ++ possibleDesign
        -- else only call searchGarden with only balcony.width + 1
        else do
            -- try other possible choices of balcony by increasing the width
            let possibleDesign1 = searchBalcony ([x!!0,x!!1 + 1]:xs) (y:ys) remArea 1
            -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign
    else []  --else return empty list as current design choice is invalid 

-- search all possible gardens with area less than remArea
-- (x:xs) -> list of room dimensions. Here x is the dimension of bathroom
-- (y:ys) -> list of room count. Here y is the number of bathroom
-- remArea -> area remaining which is need to be filled
-- elemStruct -> type 'Structure1'. It stores the dimension of bedroom,hall,kitchen and area of the 3 combined
-- mode -> Used to prevent overlapping of cases
searchBathroom (x:xs) (y:ys) remArea elemStruct mode = do 
    let bathroomArea = (x!!0)*(x!!1)*y       -- bathroom area with dimension x=[l,b]
    let newRemArea = remArea - bathroomArea  -- area remaining after adding the balcony
    let dimBedroom = bedroomDim elemStruct   -- dimension of bedroom chosen
    let dimHall = hallDim elemStruct         -- dimension of hall chosen
    let dimKitchen = kitchenDim elemStruct   -- dimension of kitchen chosen
    -- If the dimesnions of bathroom are less than the maximum possible and
    -- the dimensions of bathroom are less than equal to dimensions of kitchen and
    -- The bathroom fits within the remaining area
    if x!!0 <= 8 && x!!1 <= 9 && x!!0 <= dimKitchen!!0 && x!!1 <= dimKitchen!!1 && newRemArea>=0
    then do
         -- Create a instance of 'Structure1' with the dimension of bathroom,kitchen,hall and bedroom and area of all these components combined
        let elemStructNew = Structure1{bedroomDim = dimBedroom,hallDim = dimHall,kitchenDim = dimKitchen,bathroomDim = x,area1 = bathroomArea + area1 elemStruct}
        -- If mode is 0, call searchBathroom with bathroom.length + 1 and then with bathroom.width + 1
        if mode == 0
        then do
            -- try other possible choices of bathroom by increasing the dimensions one at a time
            let possibleDesign1 = searchBathroom ([x!!0 + 1,x!!1]:xs) (y:ys) remArea elemStruct 0
            let possibleDesign2 = searchBathroom ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
            -- return the current design as well as list of possible choices returned by all possible searches
            [elemStructNew] ++ possibleDesign1 ++ possibleDesign2
        -- else only call searchBathroom with only bathroom.width + 1
        else do
            -- try other possible choices of bathroom by increasing the width
            let possibleDesign1 = searchBathroom ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
            -- return the current design as well as list of possible choices returned by all possible searches
            [elemStructNew] ++ possibleDesign1
    else [] --else return empty list as current design choice is invalid

-- search all possible gardens with area less than remArea
-- (x:xs) -> list of room dimensions. Here x is the dimension of kitchen
-- (y:ys) -> list of room count. Here y is the number of kitchen
-- remArea -> area remaining which is need to be filled
-- elemStruct -> type 'Structure1'. It stores the dimension of bedroom,hall and area of the 2 combined
-- mode -> Used to prevent overlapping of cases
searchKitchen (x:xs) (y:ys) remArea elemStruct mode = do 
    let kitchenArea = (x!!0)*(x!!1)*y         -- kitchen area with dimension x=[l,b]
    let newRemArea = remArea - kitchenArea    -- area remaining after adding the kitchen
    let dimBedroom = bedroomDim elemStruct    -- dimension of bedroom chosen
    let dimHall = hallDim elemStruct          -- dimension of hall chosen
    -- If the dimesnions of kitchen are less than the maximum possible and
    -- the dimensions of kitchen are less than equal to dimensions of bedroom and hall and
    -- The kitchen fits within the remaining area
    if x!!0 <= 15 && x!!1 <= 13 && x!!0 <= dimBedroom!!0 && x!!1 <= dimBedroom!!1 && x!!0 <= dimHall!!0 && x!!1 <= dimHall!!1  && newRemArea>=0
    then do
        -- Create a instance of 'Structure1' with the dimension of kitchen,hall and bedroom and area of all these components combined
        let elemStructNew = Structure1{bedroomDim = dimBedroom,hallDim = dimHall,kitchenDim = x,bathroomDim = [],area1 = kitchenArea + area1 elemStruct}
         -- Call searchBathroom with current choice of kitchen,hall and bedroom dimensions
        let possibleDesign = searchBathroom xs ys newRemArea elemStructNew 0
        -- If mode is 0, call searchKitchen with kitchen.length + 1 and then with kitchen.width + 1
        if mode == 0
        then do
            -- try other possible choices of kitchen by increasing the dimensions one at a time
            let possibleDesign1 = searchKitchen ([x!!0 + 1,x!!1]:xs) (y:ys) remArea elemStruct 0
            let possibleDesign2 = searchKitchen ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
            -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign2 ++ possibleDesign
         -- else only call searchKitchen with only kitchen.width + 1
        else do
            -- try other possible choices of kitchen by increasing the width
            let possibleDesign1 = searchKitchen ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
            -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign
    else [] --else return empty list as current design choice is invalid

-- search all possible gardens with area less than remArea
-- (x:xs) -> list of room dimensions. Here x is the dimension of hall
-- (y:ys) -> list of room count. Here y is the number of hall
-- remArea -> area remaining which is need to be filled
-- elemStruct -> type 'Structure1'. It stores the dimension of bedroom and area of bedroom
-- mode -> Used to prevent overlapping of cases
searchHall (x:xs) (y:ys) remArea elemStruct mode = do
    let hallArea = (x!!0)*(x!!1)*y                -- hall area with dimension x=[l,b]
    let newRemArea = remArea - hallArea           -- area remaining after adding the hall
    let dimBedroom = bedroomDim elemStruct        -- dimension of bedroom chosen
    if x!!0 <= 20 && x!!1 <= 15 && newRemArea>=0  -- if the dimensions of hall is less than max possible and area remaining is a non negative value
    then do
        -- Create a instance of 'Structure1' with the dimension of hall and bedroom and area of all these components combined
        let elemStructNew = Structure1{bedroomDim = dimBedroom,hallDim = x,kitchenDim = [],bathroomDim = [],area1 = hallArea + area1 elemStruct}
         -- Call searchKitchen with current choice of hall and bedroom dimensions
        let possibleDesign = searchKitchen xs ys newRemArea elemStructNew 0
        -- If mode is 0, call searchHall with hall.length + 1 and then with hall.width + 1
        if mode == 0
        then do
            -- try other possible choices of halls by increasing the dimensions one at a time
            let possibleDesign1 = searchHall ([x!!0 + 1,x!!1]:xs) (y:ys) remArea elemStruct 0
            let possibleDesign2 = searchHall ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
             -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign2 ++ possibleDesign
        -- else only call searchHall with only hall.width + 1
        else do
            -- try other possible choices of hall by increasing the width
            let possibleDesign1 = searchHall ([x!!0,x!!1 + 1]:xs) (y:ys) remArea elemStruct 1
            -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign
    else [] --else return empty list as current design choice is invalid

-- search all possible gardens with area less than remArea
-- (x:xs) -> list of room dimensions. Here x is the dimension of bedroom
-- (y:ys) -> list of room count. Here y is the number of bedroom
-- remArea -> area remaining which is need to be filled
-- mode -> Used to prevent overlapping of cases
searchBedroom (x:xs) (y:ys) remArea mode = do
    let bedroomArea = (x!!0)*(x!!1)*y        -- bedroom area with dimension x=[l,b]
    let newRemArea = remArea -  bedroomArea  -- area remaining after adding the bedroom
    if x!!0 <= 15 && x!!1<=15 && newRemArea >= 0 -- if the dimensions of bedroom is less than max possible and area remaining is a non negative value
    then do
        -- Create a instance of 'Structure1' with the dimension of bedroom and area of bedroom
        let elemStructNew = Structure1{bedroomDim = x,hallDim = [],kitchenDim = [],bathroomDim = [],area1 = bedroomArea}
        -- Call searchHall with current choice of bedroom dimensions
        let possibleDesign = searchHall xs ys newRemArea elemStructNew 0
        -- If mode is 0, call searchBedroom with bedroom.length + 1 and then with bedroom.width + 1
        if mode == 0
        then do
            -- try other possible choices of bedroom by increasing the dimensions one at a time
            let possibleDesign1 = searchBedroom ([x!!0 + 1,x!!1]:xs) (y:ys) remArea 0
            let possibleDesign2 = searchBedroom ([x!!0,x!!1 + 1]:xs) (y:ys) remArea 1
            -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign2 ++ possibleDesign
        -- else only call searchBedroom with only bedroom.width + 1
        else do
            -- try other possible choices of bedroom by increasing the width
            let possibleDesign1 = searchBedroom ([x!!0,x!!1 + 1]:xs) (y:ys) remArea 1
            -- return the list of possible choices returned by all possible searches
            possibleDesign1 ++ possibleDesign
    else [] --else return empty list as current design choice is invalid

-- Merges the two independent design choices (bedroom,hall,kitchen,bathroom) and (balcony,garden)
-- Returns a final design comprising of all the components and having minimum unused space
mergeDesigns :: [Structure1] -> [Structure2] -> Integer -> FinalDesignPlan -> FinalDesignPlan
-- If any of the lists goes empty, then return the current best design upto now 
mergeDesigns [] _ _ curBestDesign = curBestDesign
mergeDesigns _ [] _ curBestDesign = curBestDesign
-- If there are still elements in the list
-- (x:xs) -> list of structure1
-- (y:ys) -> list of structure2
-- netArea -> area of the plot given
-- curBestDesign -> current best design seen upto now
mergeDesigns (x:xs) (y:ys) netArea curBestDesign = do
    let dimBedroom = bedroomDim x      --dimension of bedroom
    let dimHall = hallDim x            --dimension of hall
    let dimKitchen = kitchenDim x      --dimension of kitchen
    let dimBathroom = bathroomDim x    --dimension of bathroom
    let dimBalcony = balconyDim y      --dimension of balcony
    let dimGarden = gardenDim y        --dimension of garden
    let areaDesign = area1 x + area2 y --total area of all the components
    let unusedAreaDesign = netArea - areaDesign --unused area in the design
    -- Create an instance of FinalDesignPlan with the dimensions of components, area of the total combination and unused area
    let newPlan = FinalDesignPlan{bedroomDims = dimBedroom,hallDims = dimHall,kitchenDims = dimKitchen,bathroomDims = dimBathroom,balconyDims = dimBalcony,gardenDims = dimGarden,areaNet = areaDesign,unusedArea = unusedAreaDesign}
    -- If unused area if non negative and unused area is less than unused area of current best design
    if unusedAreaDesign >= 0 && unusedAreaDesign <= unusedArea curBestDesign
    then do  -- update the current best design to current design
        -- If area of design < net area of plot
        if areaDesign < netArea
        then mergeDesigns xs (y:ys) netArea newPlan --Pop x from the list and call mergeDesigns
        else mergeDesigns (x:xs) ys netArea newPlan --Pop y from the list and call mergeDesigns
    else do -- else keep the current best design unchanged
        -- If area of design < net area of plot
        if areaDesign < netArea
        then mergeDesigns xs (y:ys) netArea curBestDesign --Pop x from the list and call mergeDesigns
        else mergeDesigns (x:xs) ys netArea curBestDesign --Pop y from the list and call mergeDesigns

--Function finds optimal dimension of all the components with a plot of given 'area' and given number of bedroom and halls
-- area -> area of the plot
-- numBedroom -> number of bedroom required
-- numHall -> number of halls required 
design area numBedroom numHall = do
    -- calculate number of kitchen. 1 kitchen per 3 bedroom
    let numKitchen = (numBedroom + 2) `div` 3
    -- calculate number of bathroom
    let numBathroom = numBedroom + 1
    -- minimum dimensions of bedroom,all,kitchen and bathroom
    let dimBedroom = [10,10]
    let dimHall = [15,10]
    let dimKitchen = [7,5]
    let dimBathroom = [4,5]
    -- search for all possible combinations of (bedroom,hall,kitchen,bathroom) with given 'area'
    let search1 = searchBedroom [dimBedroom,dimHall,dimKitchen,dimBathroom] [numBedroom,numHall,numKitchen,numBathroom] area 0
    -- sort the result with increasing area of designs
    let sortedList1 = sortBy sortOrderStruct1 search1

    let numBalcony = 1  -- 1 balcony per house
    let numGarden = 1   -- 1 garden per house
    -- minimum dimensions of garden and balcony
    let dimBalcony = [5,5]
    let dimGarden = [10,10]
    -- search for all possible combinations of (balcony,garden) with given 'area'
    let search2 = searchBalcony [dimBalcony,dimGarden] [numBalcony,numGarden] area 0
    -- sort the result with decreasing area of designs
    let sortedList2 = sortBy sortOrderStruct2 search2

    -- Set the current best design as empty with unused area = 'area' (area of plot)
    let curBestDesign = FinalDesignPlan{bedroomDims = [],hallDims = [],kitchenDims = [],bathroomDims = [],balconyDims = [],gardenDims = [],areaNet = 0,unusedArea = area}
    -- merge the designs obtained by two list to build a complete design within 'area'
    let bestPossibleDesign = mergeDesigns sortedList1 sortedList2 area curBestDesign
        
    putStrLn " "
    putStrLn " "
    -- If the unused area in the best fit design is less that the area, i.e. a possible valid design
    if unusedArea bestPossibleDesign < area
    then do
        -- get the dimensions of the final design plan
        let ansUnusedArea = "Unused Space : " ++ show (unusedArea bestPossibleDesign)
        let ansBedroom = "Bedroom : ( " ++ show (bedroomDims bestPossibleDesign !! 0) ++ " , " ++ show (bedroomDims bestPossibleDesign !! 1) ++ ") x " ++ show numBedroom
        let ansHall = "Hall : ( " ++ show (hallDims bestPossibleDesign !! 0) ++ " , " ++ show (hallDims bestPossibleDesign !! 1) ++ ") x " ++ show numHall
        let ansKitchen = "Kitchen : ( " ++ show (kitchenDims bestPossibleDesign !! 0) ++ " , " ++ show (kitchenDims bestPossibleDesign !! 1) ++ ") x " ++ show numKitchen
        let ansBathroom = "Bathroom : ( " ++ show (bathroomDims bestPossibleDesign !! 0) ++ " , " ++ show (bathroomDims bestPossibleDesign !! 1) ++ ") x " ++ show numBathroom
        let ansBalcony = "Balcony : ( " ++ show (balconyDims bestPossibleDesign !! 0) ++ " , " ++ show (balconyDims bestPossibleDesign !! 1) ++ ") x " ++ show numBalcony
        let ansGarden = "Garden : ( " ++ show (gardenDims bestPossibleDesign !! 0) ++ " , " ++ show (gardenDims bestPossibleDesign !! 1) ++ ") x " ++ show numGarden
        -- print the output
        putStrLn ansBedroom
        putStrLn ansHall
        putStrLn ansKitchen
        putStrLn ansBathroom
        putStrLn ansBalcony
        putStrLn ansGarden
        putStrLn ansUnusedArea
    else
        -- else print no possible design can be found
        putStrLn "No Possible Design found for given area"
    putStrLn " "
    putStrLn " "