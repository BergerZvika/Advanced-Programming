/**
 * ARRAYS AND TUPLES
 */
// Array of numbers
const list: number[] = [1, 2, 3];

const names: string[] = [];
names.push("Zvi"); // no error
// names.push(3); // Error: Argument of type 'number' is not assignable to parameter of type 'string'.

const str_array: readonly string[] = ["Zvi"];
// names.push("Berger"); // Error: Property 'push' does not exist on type 'readonly string[]'.


// Tuple: Fixed length and fixed types at specific indices
let tuple: [string, number];
tuple = ["hello", 10]; 
// tuple = [10, "hello"]; // Error!

/**
 * ENUMS
 * Useful for sets of constants (like HTTP status codes or directions)
 */
enum Role {
    Admin,   // 0
    User,    // 1
    Guest    // 2
}
let currentRole: Role = Role.Admin;

/**
 * OBJECTS AND INTERFACES
 * Interfaces define the "shape" of an object.
 */
const car: { type: string, model: string, year: number } = {
  type: "Toyota",
  model: "Corolla",
  year: 2009
};

interface Professor {
    readonly id: number; // Cannot be modified
    name: string;
    department?: string; // Optional property
}

const instructor: Professor = {
    id: 1,
    name: "Dr. Smith"
};

/**
 * UNION AND INTERSECTION TYPES
 */
// Union: Can be one type OR another
let result: string | number;
result = "Success";
result = 200;

// Intersection: Combines multiple types into one
interface Loggable { log(): void }
interface Serializable { toJSON(): string }

type StorageItem = Loggable & Serializable;

// 1. The 'keyof' Operator
interface Student {
    id: number;
    name: string;
    age: number;
}

// StudentKeys is now "id" | "name" | "age"
// Extracting keys from an object type to create a Union.
// To compile: tsc type_keyof.ts --target ES2020
type StudentKeys = keyof Student;

let myKey: StudentKeys = "name"; // OK
// myKey = "address"; // ERROR: "address" is not a key of Student.