// let vs. var
// let defines a block scoped variable
// var defines a function scoped variable

// 1)
// example of let:
// console.log(x); // trying to use x before initialization - ERROR!
// let x = 5;
// console.log(x);

// same with var
// trying to use x before initialization - this time there's no error 
// x is simply 'undefined'
// console.log(x);
// var x = 5;
// console.log(x);
// x = '3'

// 2)
// let in for loop
// for (let i = 0; i < 3; i++) {
//     console.log(`i = ${i}`);
// }

// console.log(`i = ${i}`); // trying to log i but it is not defined in the outer scope

// same with var
// for (var i = 0; i < 3; i++) {
//     console.log(`i = ${i}`);
// }

// console.log(`i = ${i}`); // no error - i is defined

// 3)
// use let in function
// function foo() {
//     let x = 3;

//     console.log(x);
// }

// foo();

// // console.log(x); // accessing x from outer scope couses an ERROR!

// // same with var
// function foo() {
//     var x = 3;

//     console.log(x);
// }

// // var defines a function scoped variable
// console.log(x); // accessing x from outer scope couses an ERROR! (AGAIN!)

// 4)
// blocked scoping with let
// let x = 7;

// { // opening a block 

//     let x = 11;

//     console.log(x) // print '11'
// }

// console.log(x) // print '7'

// same with var
// var x = 7;
 
// { // opening a block 

//     x = 11; // can't redeclare using var! ERROR! 

//     console.log(x) 
// }

// console.log(x)
 
// { // opening a block 

//     var x = 11;

//     console.log(x) // prints '11'
// }

// console.log(x) // prints '11'

// default is let!

// console.log(x); // ERROR x is not defined 
// x = 5;
// console.log(x); // if reached will output '5'
// x = 7; // x is not a const => we can change its value
// console.log(x); // if reached will output '7'


// NOTE:
// you can't redeclare the same variable 
// in the same scope using let or a combination of let & var
// unless you are using var twice:

// will not work
// const x = 2;

// console.log(x);

// x = 3;

// console.log(x);

// will work
var x = 2;

console.log(x);

var x = 3;

console.log(x);


