/**
 * SIMPLE PRIMITIVE TYPES
 */

let instructorName: string = "Zvika";
let studentCount: number = 45;
let isLabOpen: boolean = true;

console.log(`Name: ${instructorName}`);
console.log(`Class Size: ${studentCount}`);
console.log(`Is Open: ${isLabOpen}`);

// TypeScript infers 'string'
let username = "alice";

// TypeScript infers 'number'
let score = 100;

// TypeScript infers 'boolean'
let flags = true;

// TypeScript infers return type as 'number'
function add(a: number, b: number) {
return a + b;
}
