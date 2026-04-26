// promises & async / await
//
// JS is single-threaded. anything that "waits" (timers, network,
// disk) is expressed as a Promise — a value that will arrive later.
// async / await is just sweeter syntax over the same Promises.

// 1) creating a Promise from scratch
// const p = new Promise((resolve, reject) => {
//     setTimeout(() => resolve("done!"), 200);
// });
//
// // a Promise has 3 states:
// //   pending -> fulfilled (resolve called)
// //           -> rejected  (reject called or an error is thrown)
// p.then(value => console.log("got:", value));

// 2) Promise.resolve / Promise.reject — instant promises
// Promise.resolve(42).then(v => console.log(v)); // 42
// Promise.reject(new Error("boom")).catch(e => console.log("caught:", e.message));

// 3) chaining — each .then returns a NEW Promise
// Promise.resolve(2)
//     .then(n => n * 10)
//     .then(n => n + 1)
//     .then(n => console.log(n)); // 21

// 4) async / await — read top-to-bottom like sync code
// function delay(ms) {
//     return new Promise(resolve => setTimeout(resolve, ms));
// }
//
// async function demo() {
//     console.log("start");
//     await delay(150);
//     console.log("after 150ms");
//     await delay(150);
//     console.log("after another 150ms");
// }
// demo();
// // an async function ALWAYS returns a Promise — even if you don't return one explicitly

// 5) error handling — try / catch around await
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

// 6) Promise.all — wait for several in PARALLEL
// async function inParallel() {
//     const [a, b, c] = await Promise.all([
//         delay(100).then(() => "A"),
//         delay(100).then(() => "B"),
//         delay(100).then(() => "C"),
//     ]);
//     console.log(a, b, c); // A B C — total ~100ms (not 300)
// }
// inParallel();

// 7) sequential vs parallel — a very common pitfall
// async function sequential() {
//     const t0 = performance.now();
//     const a = await delay(100).then(() => 1); // 100ms
//     const b = await delay(100).then(() => 2); // +100ms
//     console.log("sequential:", a + b, ((performance.now() - t0) | 0) + "ms"); // ~200ms
// }
//
// async function parallel() {
//     const t0 = performance.now();
//     const [a, b] = await Promise.all([    // both start NOW
//         delay(100).then(() => 1),
//         delay(100).then(() => 2),
//     ]);
//     console.log("parallel  :", a + b, ((performance.now() - t0) | 0) + "ms"); // ~100ms
// }
// sequential();
// parallel();


// active demo: a tiny async pipeline with error handling
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
