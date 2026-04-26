// destructuring & spread / rest
//
// destructuring unpacks values from arrays and objects into variables.
// spread (...) expands an iterable; rest (...) collects the leftovers.
// same syntax — meaning depends on context.

// 1) array destructuring
// const point = [3, 4];
// const [x, y] = point;
// console.log(x, y); // 3 4

// // skip elements with a hole
// const colors = ["red", "green", "blue"];
// const [, second] = colors;
// console.log(second); // 'green'

// // default values when the slot is undefined
// const [a = 10, b = 20] = [1];
// console.log(a, b); // 1 20

// // swap two variables — no temp needed
// let p = 1, q = 2;
// [p, q] = [q, p];
// console.log(p, q); // 2 1

// 2) object destructuring
// const user = { name: "Israel", age: 77, city: "TLV" };
// const { name, city } = user;
// console.log(name, city); // 'Israel' 'TLV'

// // rename: { source: target }
// const { name: fullName } = user;
// console.log(fullName); // 'Israel'

// // default values + rename together
// const { country: country = "IL" } = user;
// console.log(country); // 'IL'

// 3) nested destructuring
// const order = { id: 1, customer: { name: "Avi", email: "a@x.com" } };
// const { customer: { email } } = order;
// console.log(email); // 'a@x.com'

// 4) rest in destructuring — collect "the rest"
// const [head, ...tail] = [1, 2, 3, 4];
// console.log(head, tail); // 1  [2, 3, 4]

// const { name: n, ...others } = { name: "Avi", age: 30, city: "TLV" };
// console.log(n, others); // 'Avi'  { age: 30, city: 'TLV' }

// 5) destructuring function parameters (very common in modern JS)
// function greet({ name, greeting = "Hello" }) {
//     return `${greeting}, ${name}`;
// }
// console.log(greet({ name: "Avi" }));                  // 'Hello, Avi'
// console.log(greet({ name: "Dana", greeting: "Hi" })); // 'Hi, Dana'

// 6) spread — arrays
// const arr1 = [1, 2, 3];
// const arr2 = [4, 5, 6];
// const merged = [...arr1, ...arr2];      // [1,2,3,4,5,6]
// const copy   = [...arr1];               // shallow copy
// console.log(merged, copy);

// // spread into a function call
// console.log(Math.max(...[7, 2, 9, 5])); // 9

// 7) spread — objects (shallow merge / override)
// const defaults  = { theme: "dark", size: "md" };
// const overrides = { size: "lg" };
// const settings  = { ...defaults, ...overrides };
// console.log(settings); // { theme: 'dark', size: 'lg' }
// // last writer wins — order matters

// 8) rest parameters in function definitions
function sum(...nums) {
    // `nums` is a real Array, not the old `arguments` object
    return nums.reduce((acc, n) => acc + n, 0);
}

console.log(sum(1, 2, 3));         // 6
console.log(sum(...[10, 20, 30])); // 60 — spread feeds rest


// active demo: combine destructuring + spread to update an object immutably
const original = { id: 1, name: "Avi", role: "user" };
const updated  = { ...original, role: "admin" };

console.log("original:", original); // unchanged
console.log("updated :", updated);

// and the same idea for arrays — append without mutating
const list = [1, 2, 3];
const longer = [...list, 4];

console.log("list  :", list);   // [1, 2, 3]
console.log("longer:", longer); // [1, 2, 3, 4]
