// a const is a variable defined in current scope (just like let)
// but it's value can't be changed

// for example
//  
// const x = 3

// console.log(x)

// x=5
// console.log(x)

// if we have declared an array we can't set another array into the same const variable!
// const arr = new Array(1, 2, 3) // same as: const arr = [1, 2, 3]

// console.log(arr)

// arr = new Array(4, 5, 6) // error! 

// BUT we can change values inside it!
// const arr = new Array(1, 2, 3); // same as: const arr = [1, 2, 3]

// console.log(`Before: ${arr}`); // prints 'Before: 1,2,3'

// arr[0] = 8;

// console.log(`After: ${arr}`); // prints 'After: 8,2,3'

// same with const 'objects'
// const car = {type: "Fiat", model: "500", color: "white"};
// console.log(`Before: ${car.color}`); // prints 'Before: white'

// car.color = "red"; // works! 
// console.log(`After: ${car.color}`); // prints 'After: red'

// we can declare const vars with the same names in different scopes 
// const x = "Global";

// {
//     const x = "Inner 1"; // works!
//     console.log(x); // prints 'Inner 1'
// }

// {
//     const x = "Inner 2"; // works!
//     console.log(x); // prints 'Inner 2'
// }

// console.log(x); // prints 'Global'

// you can add methods and attributes to a const object

// const obj = {a: 'A', b: 'B', c: 'C'}  // define a const object

// obj.d = 'D'

// console.log(obj);  // prints { a: 'A', b: 'B', c: 'C', d: 'D' }

// obj.foo = function (){
//     console.log(`${this.a.repeat(1)}${this.b.repeat(2)}${this.c.repeat(3)}${this.d.repeat(4)}`)
// }

// obj.foo();
