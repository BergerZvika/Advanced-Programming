/**
 * Type Casting (Assertions)
 * How to override TypeScript's inferred types.
 * To compile: tsc type_casting.ts --target ES2020
 */

// 1. The 'as' Syntax (Recommended)
// Imagine receiving data from an external API or research tool.
let someValue: unknown = "Hello";

// We know it's a string, but the compiler doesn't.
let strLength: number = (someValue as string).length;


// 2. The Angle-Bracket Syntax
// This is identical to 'as', but cannot be used in .tsx (React) files.
let anotherValue: unknown = "Logic is fun";
let strUpper = (<string>anotherValue).toUpperCase();


// 3. Casting with the DOM (Very common)
// getElementById returns 'HTMLElement | null'.
// We cast it to a specific element to access specific properties (like .value).

// Quick setup so the demo has an input to read from:
const created = document.createElement("input");
created.id = "user-email";
created.value = "zvi@example.com";
document.body.appendChild(created);

const input = document.getElementById("user-email") as HTMLInputElement;
// Now we can access .value without a compiler error
console.log(input.value);


// 4. The "Impossible" Cast (Double Casting)
// TypeScript prevents you from casting a 'string' directly to a 'number' 
// because it knows that's likely a mistake.
let myAge: string = "30";
// let numAge = myAge as number; // ERROR: Conversion of type 'string' to 'number' may be a mistake.

// To force it, cast to 'unknown' or 'any' first. (Use with caution!)
let forcedNum = (myAge as unknown) as number;


// 5. Const Assertions (The 'as const' syntax)
// This makes the entire structure deeply readonly and literal.
let settings = {
    theme: "dark",
    version: 1.0
} as const;

// settings.theme = "light"; // ERROR: Readonly property.