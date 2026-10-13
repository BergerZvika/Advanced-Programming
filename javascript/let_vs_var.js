// let vs. var
// let defines a BLOCK scoped variable    — lives inside the nearest { }
// var defines a FUNCTION scoped variable — ignores { } blocks, only functions stop it
//
// lines that would throw an ERROR are left commented out ( // // ... )
// so every step runs — uncomment one to see the error yourself.

// 1) let — using it before the declaration is an ERROR
// // let IS hoisted, but stays in the "temporal dead zone" (TDZ)
// // until the line `let x = ...` actually runs
// // console.log(x); // ERROR: Cannot access 'x' before initialization
// let x = 5;
// console.log(x); // 5

// 2) var — using it before the declaration is just undefined
// // var is hoisted AND initialized to undefined — no error, which hides bugs
// console.log(y); // undefined
// var y = 5;
// console.log(y); // 5
// y = "3";        // var (and let) can change value and even type
// console.log(y); // "3"

// 3) let in a for loop — i exists only inside the loop
// for (let i = 0; i < 3; i++) {
//     console.log(`i = ${i}`);
// }
// // console.log(`after loop i = ${i}`); // ERROR: i is not defined

// 4) var in a for loop — i leaks out of the loop
// for (var i = 0; i < 3; i++) {
//     console.log(`i = ${i}`);
// }
// console.log(`after loop i = ${i}`); // no error — i is 3

// 5) let inside a function — invisible outside it
// function useLet() {
//     let a = 3;
//     console.log("inside useLet:", a);
// }
// useLet();
// // console.log(a); // ERROR: a is not defined

// 6) var inside a function — ALSO invisible outside it
// // var is function scoped, so a function stops it just like let
// function useVar() {
//     var b = 3;
//     console.log("inside useVar:", b);
// }
// useVar();
// // console.log(b); // ERROR: b is not defined (again!)

// 7) let in a block — the inner x is a NEW variable
// let x = 7;
// { // opening a block
//     let x = 11;        // shadows the outer x, only inside these { }
//     console.log(x);    // 11
// }
// console.log(x);        // 7 — the outer x was never touched

// 8) var in a block — there is only ONE x
// // a block { } is NOT a function, so var ignores it
// var x = 7;
// { // opening a block
//     var x = 11;        // same x as outside — overwrites it
//     console.log(x);    // 11
// }
// console.log(x);        // 11 — changed outside too!

// 9) no keyword at all — NOT let, it creates a GLOBAL
// // console.log(z); // ERROR: z is not defined — reading before any assignment
// z = 5;                 // no let / var / const -> becomes window.z (global)
// console.log(z);        // 5
// z = 7;
// console.log(z);        // 7
// // in 'use strict' mode `z = 5` would be an ERROR — always declare your variables

// 10) redeclaring — only var allows it
// // let twice in the same scope is a SyntaxError — the whole script refuses to run:
// // let a = 1;
// // let a = 2;  // ERROR: Identifier 'a' has already been declared
// // mixing let and var is the same error:
// // let b = 1;
// // var b = 2;  // ERROR: Identifier 'b' has already been declared
//
// // const can't be redeclared OR reassigned
// const c = 2;
// console.log(c); // 2
// // c = 3;      // ERROR: Assignment to constant variable.

// 11) var twice — allowed (one more reason to prefer let)
var v = 2;
console.log(v); // 2
var v = 3;      // silently redeclares — no error
console.log(v); // 3
