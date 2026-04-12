/**
 * 1. Step 1: Install Node.js
 * node -v
 * npm -v
 * 
 * Step 2: Install TypeScript Compiler (tsc)
 * npm install -g typescript
 * 
 * Step 3: Initialize a Project
 * mkdir ts-tutorial && cd ts-tutorial
 * npx tsc --init
 * 
 * Step 4: Compile & Run
 * tsc hello_ts.ts
 * node hello_ts.js
 */

// Primitive Types
let username: string = "Zvika";
let age: number = 30;
let isTA: boolean = true;

// Functions with typed parameters and return values
function greet(name: string, year: number): string {
    return `Hello ${name}, welcome to the class of ${year}!`;
}

console.log(greet(username, 2026));

// Error Case: This will be caught by the compiler
// greet("Student", "2026"); // Error: Argument of type 'string' is not assignable to parameter of type 'number'.