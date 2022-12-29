/*
    regardless of which position we're at, it makes to go to either the position
    that's on our immediate left, or on our immediate right, 'cause otherwise, 
    we'd just be wasting time travelling past a cow and not picking it up.
    
    let dp[l][r][last_cow] be the minimum damage done when have picked up all the cows
    from pos[l] to pos[r] inclusive, and the last cow came from the left(0) or the
    right(1).
    
    one (incorrect) way to approach this would be if we considered dp[l][r] to hold
    the minimum damage done by only the cows from pos[l] to pos[r] inclusive. then,
    to calculate the additional damage done by the next cow we'd need to know the 
    time ew reached the last cow. since this varies depending on the sequence
    of the visited cows, the time we visited the last cow would have to be an 
    additional dp state. since time could be a very lage value, this is not the way
    to go.
    
    instead, let dp[l][r][last_cow] be the mminimum damage done by ALL the cows when
    we've only visited cows from pos[l] to pos[r] and the lst cow we visited came from
    left/right.
    
    let's say we're at position 3 and we want to go to position 7, and we have 3 cows
    (including the cow and position 7) to pick up. for every second that we take 
    to travel from position 3 to position 7 (that is, 4 seconds) each of the other
    cows is causing 4 units of damage. 
    
    so the damage caused by all cows when we have visited cows from pos[l] to pos[r]
    = number of un-visited cows * distance to next cow to be visited + dp
    
*/
