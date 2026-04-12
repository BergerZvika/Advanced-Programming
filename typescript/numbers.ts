/**
 * TYPE: number
 * Representing integers, floats, and different bases.
 */

// 1. Different Bases (Literals)
const decimal: number = 2026;
const hex: number = 0xf00d;      // Hexadecimal (starts with 0x)
const binary: number = 0b1010;   // Binary (starts with 0b)
const octal: number = 0o744;     // Octal (starts with 0o)

console.log(`Bases: ${decimal}, ${hex}, ${binary}, ${octal}`);


// 2. Large Number Readability (Numeric Separators)
// Use underscores to make large numbers readable for students.
const billion: number = 1_000_000_000;
const bytes: number = 0b1101_0010_1011_0001;


// 3. Special Numeric Values (Non-trivial)
// These are all of type 'number', which can be counter-intuitive.
const infinity: number = Infinity;
const negInfinity: number = -Infinity;
const notANumber: number = NaN; // Result of "hello" * 5

// compile with --lib ES2015,DOM for Numbers.isFinite
function checkPurity(value: number) {
    if (!Number.isFinite(value)) {
        console.log("This is an infinite or NaN value!");
    }
} 


// 4. Literal Number Types (Highly useful for logic)
// Restricting a variable to ONLY specific numeric values.
type DieRoll = 1 | 2 | 3 | 4 | 5 | 6;

function movePlayer(roll: DieRoll) {
    console.log(`Moving ${roll} spaces.`);
}

movePlayer(5); // OK
// movePlayer(7); // Error: Argument of type '7' is not assignable to 'DieRoll'


// 5. Floating Point Precision Awareness
// A classic trap for CS students: 0.1 + 0.2 is NOT 0.3 in IEEE 754.
const x: number = 0.1;
const y: number = 0.2;
const result: number = x + y;

console.log(`0.1 + 0.2 = ${result}`); // Output: 0.30000000000000004

// Proper way to handle currency/precision:
const isCorrect: boolean = Math.abs(result - 0.3) < Number.EPSILON;
console.log(`Is it close enough to 0.3? ${isCorrect}`);


// 6. Bigint Represents whole numbers larger than 2^53 - 1.
// compile with --target ES2020
let bigIntVal: bigint = 9007199254740991n; 
const hugeNumber = BigInt(9007199254740991); 