/**
 * TYPE: symbol
 * Symbols are unique and immutable.
 */

// 1. Basic Creation
// Every call to Symbol() returns a new, unique symbol.
const sym1: symbol = Symbol("key");
const sym2: symbol = Symbol("key");

console.log(sym1 === sym2); // false! Even with the same description.


// 2. unique symbol (The most "Advanced" variant)
// In TypeScript, 'unique symbol' is a subtype of symbol that can only 
// be used with 'const'. It links the type to that specific instance.
const INTERNAL_ID: unique symbol = Symbol("id");

interface SecureUser {
    [INTERNAL_ID]: number; // The key is the unique symbol itself
    name: string;
}

const user: SecureUser = {
    [INTERNAL_ID]: 999,
    name: "Zvika"
};

console.log(user[INTERNAL_ID]); // 999

// 3. The Symbol Registry (Global Symbols)
// If you actually WANT to share a symbol across files, use Symbol.for()
const globalSym1 = Symbol.for("app.api.key");
const globalSym2 = Symbol.for("app.api.key");

console.log(globalSym1 === globalSym2); // true