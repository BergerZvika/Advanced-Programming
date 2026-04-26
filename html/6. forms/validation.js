function isPositiveInteger(str) {
    if (typeof str !== "string") {
        return false; // we only process strings! 
    } 

    // turn the string into a number
    const inputAsNum = Number(str); 
    
    if (isNaN(inputAsNum)) {
        return false;  // parsing into a number failed
    }

    if (Number.isInteger(inputAsNum) && inputAsNum > 0)
        return true;

    return false;
}