/**
 * LESSON: The "Special" Types
 * Explaining Null, Undefined, Any, Unknown, Never, Object, and Void.
 * * To compile: tsc special_types_comparison.ts --target ES2020
 */

// ==========================================
// 1. NULL vs. UNDEFINED (The "Nothing" Types)
// ==========================================

// Undefined: Variable is declared but has no value yet.
let notInitialized: undefined; 

// Null: An intentional assignment representing "no value".
let intentionallyEmpty: null = null; 

function checkNothing(val: string | null | undefined) {
    if (val === undefined) console.log("Value was never provided.");
    if (val === null) console.log("Value was explicitly set to null.");
}

// ==========================================
// 2. ANY vs. UNKNOWN (The "Top" Types)
// ==========================================

// ANY: The "Escape Hatch". Disables all type checking.
// DANGEROUS: Avoid this in your students' code.
let insecure: any = { greet: () => "Hi" };
try {
    insecure.doAnything(); // NO COMPILE ERROR, but crashes at runtime!
} catch (e) {
    console.log("any crashed at runtime:", (e as Error).message);
}

// UNKNOWN: The "Safe Any". You cannot use it until you prove what it is.
let secure: unknown = "I am a string";

// secure.toUpperCase(); // ERROR: Object is of type 'unknown'.

if (typeof secure === "string") {
    console.log(secure.toUpperCase()); // OK: Logic "proved" it is a string.
}

// ==========================================
// 3. VOID vs. NEVER (The "Function" Types)
// ==========================================

// VOID: A function that returns nothing (it finishes, but returns undefined).
function logStatus(msg: string): void {
    console.log("Status:", msg);
    return; // Optional
}

// NEVER: A function that NEVER returns.
// 1. It throws an error OR 2. It has an infinite loop.
function panic(errorMsg: string): never {
    throw new Error(errorMsg);
}

// ==========================================
// 4. OBJECT (The "Non-Primitive" Type)
// ==========================================

// 'object' (lowercase) represents any non-primitive type.
// It is NOT a number, string, boolean, symbol, null, or undefined.
let dataContainer: object;
dataContainer = { id: 1 };
dataContainer = [1, 2, 3]; // Arrays are objects
// dataContainer = 42;      // ERROR: Type 'number' is not assignable to 'object'.
