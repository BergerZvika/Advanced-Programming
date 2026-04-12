/**
 * Mapped Types
 * The 'for-each' loop of the TypeScript type system.
 * To compile: tsc master_mapped_types.ts --target ES2020
 */

// --- THE BASE INTERFACE ---
interface SystemState {
    id: number;
    label: string;
    isActive: boolean;
}

// 1. BASIC MAPPING
// Create a "Mask" where every value in SystemState becomes a boolean.
type StateMask = {
    [K in keyof SystemState]: boolean;
};

// 2. THE MODIFIER MAPS (+ and -)
// This is how built-in types like Readonly and Partial are made.

// 2a. Make everything Readonly and Optional
type ReadonlyPartialState = {
    readonly [K in keyof SystemState]?: SystemState[K];
};

// 2b. The "Stripper" Map: Remove Readonly and Remove Optional
// Note: We use '-readonly' and '-?' to force strictness.
type AbsoluteState = {
    -readonly [K in keyof SystemState]-?: SystemState[K];
};


// 3. WRAPPER MAPPING
// Wrap every property in a specific generic container.
type AsyncState = {
    [K in keyof SystemState]: Promise<SystemState[K]>;
};


// 4. KEY REMAPPING (Using the 'as' clause)
// This allows you to change the NAMES of the keys. 
// Extremely common for generating Getters and Setters.

type StateGetters = {
    [K in keyof SystemState as `get${Capitalize<string & K>}`]: () => SystemState[K];
};

/* Resulting Type for StateGetters:
{
    getId: () => number;
    getLabel: () => string;
    getIsActive: () => boolean;
}
*/


// 5. FILTERING DURING MAPPING
// You can use the 'as' clause with 'never' to filter out specific types.
// Only keep properties that are strings.
type OnlyStrings<T> = {
    [K in keyof T as T[K] extends string ? K : never]: T[K];
};

type StringFields = OnlyStrings<SystemState>; // Result: { label: string }

// 6. Built-in Utility Types
interface User {
    id: number;
    name: string;
    email: string;
    phoneNumber?: string; // Optional property
    isAdmin: boolean;
    secretToken: string;  // Sensitive data
}

// Partial<T> - Makes all properties optional
// Essential for "Update" or "Patch" functions where users change only some fields.
type UserUpdate = Partial<User>;

const updateName: UserUpdate = { name: "Zvika" }; // Valid: no other fields required


// Required<T> - The opposite of Partial; removes all '?' modifiers
// Useful for ensuring a model is fully populated before saving to a database.
type FinalUser = Required<User>;


// Pick<T, Keys> - Selects only a specific subset of keys
// Used to create "View Models" or DTOs (Data Transfer Objects).
type UserProfile = Pick<User, "id" | "name" | "email">;

const profile: UserProfile = {
    id: 1,
    name: "Alice",
    email: "alice@univ.ac.il"
};


// Omit<T, Keys> - Removes specific keys
// The best way to create a "Safe" version of an object by stripping sensitive fields.
type SafeUser = Omit<User, "secretToken" | "isAdmin">;


// Record<Keys, Type> - Creates a Dictionary/Map structure
// Ideal for indexing data by an ID (e.g., in a Cache or Registry).
type UserRegistry = Record<number, User>;

const users: UserRegistry = {
    101: { id: 101, name: "Zvi", email: "z@z.com", isAdmin: true, secretToken: "123" },
    102: { id: 102, name: "Dan", email: "d@d.com", isAdmin: false, secretToken: "456" }
};