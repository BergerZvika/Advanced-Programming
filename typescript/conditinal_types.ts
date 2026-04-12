/**
 * Conditional Types
 * Logic-based type transformations.
 * To compile: tsc type_conditional.ts --target ES2020
 */

// 1. Basic Conditional Type
// A type that returns "string" if passed a string, and "number" otherwise.
//Conditional types use the form T extends U ? X : Y, which means:
// "if type T extends (or is assignable to) type U, use type X, otherwise use type Y".
type IsString<T> = T extends string ? string : number;

type A = IsString<string>;
type B = IsString<number>; 


// 2. Non-Trivial Example: API Response Unwrapper
// In research tools, you might have a wrapper. Let's unwrap it.
interface DataWrapper<T> {
    data: T;
}

type Unwrap<T> = T extends DataWrapper<infer U> ? U : T;

type TypedData = Unwrap<DataWrapper<number[]>>; // Result: number[]
type SimpleData = Unwrap<string>;               // Result: string


// 3. Distributive Conditional Types
// When you pass a Union to a conditional type, TS applies it to each member.
type ToArray<T> = T extends any ? T[] : never;

type StrOrNumArray = ToArray<string | number>; 
// Result: string[] | number[]


// 4. Filtering Types (The "Exclude" Logic)
// Create a type that removes 'null' and 'undefined' from a union.
type NonNullableCustom<T> = T extends null | undefined ? never : T;

type Cleaned = NonNullableCustom<string | null | number>; 
// Result: string | number (because 'never' is removed from unions)


// 5. Practical Example: Formal Methods Result
// Modeling a solver that returns different payload shapes based on the result status.
type SolverResult<T> = T extends "SAT" 
    ? { model: string } 
    : { conflict: string[] };

function handleSolver<S extends "SAT" | "UNSAT">(status: S): SolverResult<S> {
    throw "Implementation here";
}

const res = handleSolver("SAT");
// res.model exists here, but res.conflict does not.