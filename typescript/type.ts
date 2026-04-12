/**
 * LESSON: Type Aliases
 * Using 'type' to create reusable definitions.
 * To compile: tsc type_aliases.ts --target ES2020
 */

// 1. Aliasing Primitives
// Makes code self-documenting for students.
type StudentID = string;
type NumericGrade = number;

let user: StudentID = "std_882";
let finalScore: NumericGrade = 95;


// 2. Aliasing Object Shapes
// Similar to an interface, but cannot be re-opened to add new properties.
type Point2D = {
    x: number;
    y: number;
};

const origin: Point2D = { x: 0, y: 0 };


// 3. Aliasing Unions (Extremely Powerful)
// This is where Type Aliases shine compared to Interfaces.
type ConnectionState = "connecting" | "connected" | "disconnected" | "error";

let currentStatus: ConnectionState = "connected";


// 4. Aliasing Tuples
// Useful for representing mathematical vectors or fixed data pairs.
type RGB = [red: number, green: number, blue: number];
const tomato: RGB = [255, 99, 71];


// 5. Aliasing Function Signatures
// Defining the "contract" for a function.
type MathOperation = (a: number, b: number) => number;

const add: MathOperation = (x, y) => x + y;
const multiply: MathOperation = (x, y) => x * y;


// 6. Intersection Types (Combining Aliases)
// Similar to "logical AND" in formal methods.
type Person = { name: string };
type Employee = { employeeID: number };

type StaffMember = Person & Employee; // Must have both sets of properties

const assistant: StaffMember = {
    name: "Zvika",
    employeeID: 12345
};