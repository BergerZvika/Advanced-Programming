// promises
//
// a Promise is an object that stands for a value that isn't ready yet.
// it starts "pending" and settles exactly ONCE, to either:
//   fulfilled  — resolve(value) was called
//   rejected   — reject(reason) was called, or the executor threw
// once settled it never changes again.

// 1) creating a Promise — the executor runs IMMEDIATELY (synchronously)
// console.log("before");
// const p = new Promise((resolve, reject) => {
//     console.log("executor runs now");
//     setTimeout(() => resolve("ready!"), 200);
// });
// console.log("after — p is still pending");
// p.then(value => console.log("then got:", value));

// 2) settling only happens once — later calls are ignored
// const once = new Promise((resolve, reject) => {
//     resolve("first");
//     resolve("second");          // ignored
//     reject(new Error("nope"));  // ignored too
// });
// once.then(v => console.log(v)); // first

// 3) rejecting — throw inside the executor == reject
// const bad = new Promise(() => {
//     throw new Error("executor blew up");
// });
// bad.catch(err => console.log("caught:", err.message));

// 4) then / catch / finally
// function coinFlip() {
//     return new Promise((resolve, reject) => {
//         setTimeout(() => Math.random() < 0.5
//             ? resolve("heads")
//             : reject(new Error("tails")), 100);
//     });
// }
// coinFlip()
//     .then(v => console.log("won:", v))
//     .catch(e => console.log("lost:", e.message))
//     .finally(() => console.log("finally runs either way"));

// 5) chaining — each .then returns a NEW Promise
// //    return a value  -> next .then gets that value
// //    return a Promise -> the chain WAITS for it
// //    throw           -> skips to the next .catch
// Promise.resolve(2)
//     .then(n => n * 10)                                       // 20
//     .then(n => new Promise(r => setTimeout(() => r(n + 1), 100))) // waits, 21
//     .then(n => { if (n > 20) throw new Error("too big: " + n); return n; })
//     .then(n => console.log("never runs", n))
//     .catch(e => { console.log("caught:", e.message); return 0; })
//     .then(n => console.log("recovered with", n));            // 0

// 6) the classic mistake — forgetting to RETURN inside .then
// Promise.resolve(1)
//     .then(n => { Promise.resolve(n + 1); })   // no return -> undefined
//     .then(n => console.log("forgot return:", n));
// Promise.resolve(1)
//     .then(n => Promise.resolve(n + 1))        // returned -> 2
//     .then(n => console.log("with return:  ", n));

// 7) turning a callback API into a Promise ("promisify")
// function readConfig(name, callback) {           // old node-style API
//     setTimeout(() => name
//         ? callback(null, { name, debug: true })
//         : callback(new Error("no name")), 100);
// }
// function readConfigAsync(name) {
//     return new Promise((resolve, reject) => {
//         readConfig(name, (err, data) => err ? reject(err) : resolve(data));
//     });
// }
// readConfigAsync("app").then(cfg => console.log("config:", cfg));
// readConfigAsync("").catch(e => console.log("error:", e.message));

// 8) the combinators — all / allSettled / race / any
// const wait = (ms, v, fail) => new Promise((res, rej) =>
//     setTimeout(() => fail ? rej(new Error(v)) : res(v), ms));
//
// // all: every one must succeed; fails FAST on the first rejection
// Promise.all([wait(100, "a"), wait(50, "b")])
//     .then(v => console.log("all       :", v));                 // ["a","b"] (input order!)
// Promise.all([wait(100, "a"), wait(50, "x", true)])
//     .catch(e => console.log("all fail  :", e.message));        // x
//
// // allSettled: never rejects — reports every outcome
// Promise.allSettled([wait(100, "a"), wait(50, "x", true)])
//     .then(r => console.log("allSettled:", r.map(x => x.status)));
//
// // race: first to SETTLE wins (success or failure)
// Promise.race([wait(100, "slow"), wait(50, "fast")])
//     .then(v => console.log("race      :", v));                 // fast
//
// // any: first to SUCCEED wins; rejects only if ALL fail
// Promise.any([wait(30, "x", true), wait(80, "ok")])
//     .then(v => console.log("any       :", v));                 // ok


// 9) active demo — a timeout wrapper built from Promise.race
function wait(ms, value) {
    return new Promise(resolve => setTimeout(() => resolve(value), ms));
}

function withTimeout(promise, ms) {
    const timeout = new Promise((_, reject) =>
        setTimeout(() => reject(new Error("timed out after " + ms + "ms")), ms));
    return Promise.race([promise, timeout]);
}

withTimeout(wait(100, "fast response"), 300)
    .then(v => console.log("ok:", v))
    .catch(e => console.log("error:", e.message));

withTimeout(wait(500, "slow response"), 300)
    .then(v => console.log("ok:", v))
    .catch(e => console.log("error:", e.message));
