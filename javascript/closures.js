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

// 2) private state — the classic "counter" pattern
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

// // a second counter gets its own, separate `count`
// const c2 = makeCounter();
// console.log(c2.inc()); // 1
// console.log(c2.inc()); // 2
// console.log(c2.inc()); // 3
// console.log(c.get());  // 1 — c is unaffected

// 3) the famous `var`-in-loop pitfall
// // var binds at function scope — every callback closes over the *same* i
// for (var i = 0; i < 3; i++) {
//     setTimeout(() => console.log("var i =", i), 0);
// }
// // prints: 3, 3, 3

// // `let` binds per-iteration — each callback closes over its own i
// for (let i = 0; i < 3; i++) {
//     setTimeout(() => console.log("let i =", i), 0);
// }
// // prints: 0, 1, 2


// 4) fibonacci — naive recursion vs. memoization
function fibonacci(n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

function fibonacci_dm(n, memo = {}) {
    if (n in memo) {
        return memo[n];
    }
    if (n <= 1) {
        return BigInt(n);
    }
    memo[n] = fibonacci_dm(n - 1, memo) + fibonacci_dm(n - 2, memo);
    return memo[n];
}

// Example usage:
// console.log(fibonacci(300));

// Example usage:
console.log(fibonacci_dm(300));
// console.log(fibonacci_dm(301));
