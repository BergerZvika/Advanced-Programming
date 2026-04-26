// closures
//
// a closure is a function that "remembers" the variables
// from the scope in which it was created — even after that
// scope has finished executing.
//
// every JS function carries its lexical environment with it.
// that captured environment is the closure.

// 1) the simplest closure
// function makeGreeter(greeting) {
//     return function (name) {
//         // `greeting` is captured from the outer scope
//         return `${greeting}, ${name}!`;
//     };
// }

// const hello  = makeGreeter("Hello");
// const shalom = makeGreeter("Shalom");

// console.log(hello("world"));   // 'Hello, world!'
// console.log(shalom("Israel")); // 'Shalom, Israel!'
// // each greeter has its own captured `greeting`

// 2) closures hold *references*, not snapshots
// let value = 1;
// const showValue = () => console.log(value);

// showValue(); // 1
// value = 99;
// showValue(); // 99 — the closure sees the live binding

// 3) private state — the classic "counter" pattern
// function makeCounter() {
//     let count = 0;              // not visible from outside
//     return {
//         inc: () => ++count,
//         dec: () => --count,
//         get: () => count,
//     };
// }

// const c = makeCounter();
// console.log(c.inc()); // 1
// console.log(c.inc()); // 2
// console.log(c.dec()); // 1
// console.log(c.get()); // 1
// // c.count is undefined — fully encapsulated

// 4) IIFE — immediately invoked function expression
// runs once, exposes only what you choose
// const api = (function () {
//     const secret = "shhh";
//     return { reveal: () => secret };
// })();

// console.log(api.reveal()); // 'shhh'
// console.log(api.secret);   // undefined

// 5) the famous `var`-in-loop pitfall
// var binds at function scope — every callback closes over the *same* i
// for (var i = 0; i < 3; i++) {
//     setTimeout(() => console.log("var i =", i), 0);
// }
// // prints: 3, 3, 3

// // `let` binds per-iteration — each callback closes over its own i
// for (let i = 0; i < 3; i++) {
//     setTimeout(() => console.log("let i =", i), 0);
// }
// // prints: 0, 1, 2


// 6) closure as memoization — a function that remembers past results
function memoize(fn) {
    const cache = new Map(); // captured by the returned function
    return function (n) {
        if (cache.has(n)) return cache.get(n);
        const result = fn(n);
        cache.set(n, result);
        return result;
    };
}

const square = (n) => n * n;
const fastSquare = memoize(square);

console.log(fastSquare(7));  // computed -> 49
console.log(fastSquare(7));  // cached   -> 49
console.log(fastSquare(11)); // computed -> 121
