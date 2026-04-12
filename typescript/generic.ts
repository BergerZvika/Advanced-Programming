/**
 * Generics (<T>)
 * Writing reusable, type-safe logic.
 * To compile: tsc type_generics.ts --target ES2020
 */

// 1. Why Generics? (The Problem)
// Without generics, we use 'any', which is unsafe.
function getLastItemAny(items: any[]): any {
    return items[items.length - 1];
}

// 2. The Generic Solution
// <T> is a placeholder for the Type. 
// When we call the function, T becomes the type of the array we passed.
function getLastItem<T>(items: T[]): T {
    return items[items.length - 1];
}

const lastNum = getLastItem([10, 20, 30]);      // T is 'number'
const lastStr = getLastItem(["a", "b", "c"]);  // T is 'string'


// 3. Generic Interfaces
// Useful for modeling API responses or data containers.
interface Box<T> {
    content: T;
    id: number;
}

const stringBox: Box<string> = { content: "Research Data", id: 101 };
const numberBox: Box<number> = { content: 555, id: 102 };


// 4. Generic Constraints (extends)
// Sometimes we want a generic, but it must have certain properties.
// Example: The type MUST have a .length property.
interface HasLength {
    length: number;
}

function logLength<T extends HasLength>(item: T): void {
    console.log(`Length: ${item.length}`);
}

logLength("Hello");       // OK: strings have .length
logLength([1, 2, 3]);    // OK: arrays have .length
// logLength(123);       // ERROR: numbers don't have .length


// 5. Generics in Classes
// Perfect for Data Structures like Stacks, Queues, or Trees.
class Stack<T> {
    private items: T[] = [];

    push(val: T) {
        this.items.push(val);
    }

    pop(): T | undefined {
        return this.items.pop();
    }
}

const plateStack = new Stack<string>();
plateStack.push("Plate 1");


// 6. Multiple Type Parameters
// Example: A function that merges two different objects.
function merge<T extends object, U extends object>(obj1: T, obj2: U): T & U {
    return { ...obj1, ...obj2 };
}

const merged = merge({ name: "Zvika" }, { role: "TA" });
console.log(merged.name, merged.role);