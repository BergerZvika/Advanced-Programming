/*
1) Write a JS program to find the 
   first occurrence of a number inside a given array. 

2) Write a JS program that counts the number of occurrences of a given item.

3) Write a JS program that returns true if an item is 
   found in a given array and false otherwise.

4) Write a JS program that filters an array by a filter function.

5) Write a JS program that multiplies each element of an array by a given number

6) Write a JS function that returns an array of random numbers with a given length.
*/


// 1)
function findFirstOccurrence(array, item) {
    let index = null;

    for (let i = 0; i < array.length; i++) {
        if (array[i] == item) {
            index = i;
            break;
        }
    } 

    return index;
}


// 2)
function countItemOccurrence(array, item) {
    let counter = 0;

    // we can use forEach for that
    array.forEach(x => {
        if (x == item) {
            counter++;
        }
    })

    return counter
}

// 3) 
function isItemInArray(array, item) {
    // we can use the previous functions:
    // return !(findFirstOccurrence(array, item) === null)
    let found = false;

    for (let i = 0; i < array.length; i++) {
        if (array[i] == item) {
            found = true;
            break; // can't use break inside forEach
        }
    }

    return found
}


// 4) 
function filterArray(array, filterFunction) {
    // this function exsits in JS 
    // return array.filter(filterFunction)

    let filteredArray = new Array(); // it is possible to define an array with '[]' as well

    array.forEach(x => {
        if (filterFunction(x) === true) {
            filteredArray.push(x)
        }
    })

    return filteredArray
}

// 5) 
function multiplyEachElement(array, multiplier) {
    let newArray = [];

    array.forEach(x => {
        newArray.push(x * multiplier);
    })

    return newArray;
}

// 6) 
function getRandomArray(arrayLength, low, high) {
    let randomArray = [];

    for (let i = 0; i < arrayLength; i++) {
        const randomNumber = (Math.random() * (high - low)) + low;

        randomArray.push(randomNumber);
    }

    return randomArray
}

let array = [1, 2, 3, '3'];

console.log(filterArray([1, 2, 3, '3'], x => x == '3'));

console.log(multiplyEachElement([1, 2, '3', "a"], 5))

console.log(getRandomArray(5, 2, 10));





// if ([] == 0) {
//    console.log("[] == 0")
// }

// if ("\t" == 0) {
//    console.log("\t == 0")
// }

// if ("0" == 0) {
//    console.log("'0' == 0")
// }

// if ([] == "0") {
//    console.log("[] == 0")
// }
