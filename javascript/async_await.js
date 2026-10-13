// async / await
//
// async / await is syntax over Promises — nothing new underneath.
//   async function  -> ALWAYS returns a Promise
//   await promise   -> pauses THIS function until the promise settles,
//                      then gives you its value (or throws its error)
// while the function is paused, the rest of the program keeps running.

// 1) an async function always returns a Promise
// async function getNumber() {
//     return 42;                      // wrapped: Promise.resolve(42)
// }
// console.log(getNumber());           // Promise { ... } — not 42!
// getNumber().then(n => console.log("then:", n));

// 2) await unwraps the value
// const delay = (ms, v) => new Promise(r => setTimeout(() => r(v), ms));
//
// async function demo() {
//     console.log("start");
//     const a = await delay(150, "first");
//     console.log("after 150ms:", a);
//     const b = await delay(150, "second");
//     console.log("after another 150ms:", b);
// }
// demo();

// 3) the same flow — .then chain vs async/await
// const delay = (ms, v) => new Promise(r => setTimeout(() => r(v), ms));
//
// function withThen() {
//     return delay(100, 1)
//         .then(a => delay(100, a + 1))
//         .then(b => console.log("then chain:", b));
// }
// async function withAwait() {
//     const a = await delay(100, 1);
//     const b = await delay(100, a + 1);
//     console.log("async/await:", b);
// }
// withThen();
// withAwait();

// 4) error handling — try / catch / finally around await
// async function risky() {
//     try {
//         const v = await Promise.reject(new Error("nope"));
//         console.log(v); // never runs
//     } catch (err) {
//         console.log("caught:", err.message);
//     } finally {
//         console.log("cleanup runs either way");
//     }
// }
// risky();

// 5) throw inside async == rejected promise
// async function fails() {
//     throw new Error("thrown inside async");
// }
// fails().catch(e => console.log("caller sees a rejection:", e.message));

// 6) sequential vs parallel — the most common pitfall
// const delay = (ms, v) => new Promise(r => setTimeout(() => r(v), ms));
//
// async function sequential() {
//     const t0 = performance.now();
//     const a = await delay(150, 1);  // 150ms
//     const b = await delay(150, 2);  // +150ms
//     console.log("sequential:", a + b, ((performance.now() - t0) | 0) + "ms"); // ~300ms
// }
// async function parallel() {
//     const t0 = performance.now();
//     const pa = delay(150, 1);       // both start NOW
//     const pb = delay(150, 2);
//     const [a, b] = await Promise.all([pa, pb]);
//     console.log("parallel  :", a + b, ((performance.now() - t0) | 0) + "ms"); // ~150ms
// }
// sequential().then(parallel);

// 7) loops — for...of awaits one by one, .map + Promise.all runs together
// const delay = (ms, v) => new Promise(r => setTimeout(() => r(v), ms));
// const ids = [1, 2, 3];
//
// async function oneByOne() {
//     for (const id of ids) {
//         const v = await delay(100, id * 10);
//         console.log("for...of got", v);
//     }
// }
// async function allAtOnce() {
//     const values = await Promise.all(ids.map(id => delay(100, id * 10)));
//     console.log("Promise.all got", values);
// }
// oneByOne().then(allAtOnce);
// // careful: ids.forEach(async id => await ...) does NOT wait — forEach ignores promises

// 8) forgetting await — you get the Promise, not the value
// async function getUser() { return { name: "Ada" }; }
//
// async function main() {
//     const wrong = getUser();          // forgot await
//     console.log("wrong:", wrong.name); // undefined — it's a Promise
//     const right = await getUser();
//     console.log("right:", right.name); // Ada
// }
// main();


// 9) active demo — a tiny async pipeline with error handling
function delay(ms, value) {
    return new Promise(resolve => setTimeout(() => resolve(value), ms));
}

async function fetchUser(id) {
    if (id <= 0) throw new Error("invalid id: " + id);
    await delay(120); // pretend this is a network call
    return { id, name: "User#" + id };
}

async function main() {
    try {
        // these two run in parallel — total wait ~120ms, not 240ms
        const [u1, u2] = await Promise.all([fetchUser(1), fetchUser(2)]);
        console.log("loaded in parallel:", u1, u2);

        // and a sequential one
        const u3 = await fetchUser(3);
        console.log("then loaded:", u3);

        // this throws — `await` re-throws rejections so try/catch catches it
        await fetchUser(-1);
    } catch (err) {
        console.log("caught:", err.message);
    } finally {
        console.log("done");
    }
}

main();
