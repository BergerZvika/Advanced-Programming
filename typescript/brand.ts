/**
 * LESSON: Branded Types (Nominal Typing)
 * Preventing logical errors by distinguishing between structurally identical types.
 */

// A helper utility to "Brand" a type. 
// It intersects the base type (K) with a unique literal object.
type Brand<K, T> = K & { __brand: T };

// Suppose we have User IDs and Project IDs. 
// Both are numbers, but logically, they should never be mixed.
type UserId = Brand<number, "UserId">;
type ProjectId = Brand<number, "ProjectId">;

// Critical System Functions
function deleteUser(id: UserId) {
    console.log(`User ${id} deleted successfully.`);
}

function archiveProject(id: ProjectId) {
    console.log(`Project ${id} archived successfully.`);
}

// --- Usage ---

// To create a Branded type, we use a Type Assertion (Casting)
const myUserId = 101 as UserId;
const myProjectId = 5005 as ProjectId;

// Valid usage:
deleteUser(myUserId);
archiveProject(myProjectId);

// --- THE LOGICAL PROTECTION ---
// Without Branding, the following line would compile (since both are just numbers).
// With Branding, the compiler prevents this logical error:
// deleteUser(myProjectId); 
// Error: Argument of type 'ProjectId' is not assignable to parameter of type 'UserId'.