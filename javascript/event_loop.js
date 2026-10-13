// the event loop
//
// JS runs on ONE thread with ONE call stack. waiting (timers, network,
// clicks) happens outside JS; when it's done, a callback is queued.
//
//   call stack       — the code running right now
//   microtask queue  — promise callbacks (.then/await), queueMicrotask
//   task queue       — setTimeout, setInterval, events, I/O  ("macrotasks")
//
// the loop, forever:
//   1. run the current task until the call stack is EMPTY
//   2. run ALL microtasks (including ones added while draining)
//   3. (browser) maybe render a frame
//   4. take the NEXT task from the task queue -> back to 1

// 1) sync code always finishes first
// console.log("A");
// setTimeout(() => console.log("C — timer, even with 0ms"), 0);
// console.log("B");
// // A, B, C

// 2) microtasks beat tasks
// setTimeout(() => console.log("3. setTimeout (task)"), 0);
// Promise.resolve().then(() => console.log("2. promise (microtask)"));
// console.log("1. sync");

// 3) the classic quiz — guess the order before you run it
// console.log("1");
// setTimeout(() => console.log("2"), 0);
// Promise.resolve()
//     .then(() => console.log("3"))
//     .then(() => console.log("4"));
// queueMicrotask(() => console.log("5"));
// console.log("6");
// // answer: 1 6 3 5 4 2
// //   sync: 1 6 | microtasks: 3 5, then 4 (queued when 3 finished) | task: 2

// 4) await = "pause here, continue in a microtask"
// async function worker() {
//     console.log("b. worker starts (sync!)");
//     await null;
//     console.log("d. worker resumes (microtask)");
// }
// console.log("a. start");
// worker();
// console.log("c. end of script");

// 5) setTimeout's delay is a MINIMUM, not a promise
// const t0 = performance.now();
// setTimeout(() => {
//     console.log("asked for 0ms, got", (performance.now() - t0).toFixed(0) + "ms");
// }, 0);
// const end = Date.now() + 200;
// while (Date.now() < end) {}   // block the call stack for 200ms
// console.log("busy loop done");

// 6) blocking the thread blocks EVERYTHING — timers, clicks, rendering
// let ticks = 0;
// const id = setInterval(() => console.log("tick", ++ticks), 50);
// setTimeout(() => {
//     console.log("--- blocking for 300ms ---");
//     const end = Date.now() + 300;
//     while (Date.now() < end) {}
//     console.log("--- unblocked ---");
// }, 120);
// setTimeout(() => clearInterval(id), 600);
// // notice: no ticks while blocked, then only ONE catches up (intervals don't pile up)

// 7) chunking long work so the loop can breathe
// function sumInChunks(n, chunk) {
//     return new Promise(resolve => {
//         let i = 0, total = 0, slices = 0;
//         (function step() {
//             const stop = Math.min(i + chunk, n);
//             for (; i < stop; i++) total += i;
//             slices++;
//             if (i < n) setTimeout(step, 0);  // yield to the loop, then continue
//             else resolve({ total, slices });
//         })();
//     });
// }
// setTimeout(() => console.log("a timer squeezed in between chunks"), 0);
// sumInChunks(1_000_000, 250_000).then(r => console.log("sum:", r.total, "in", r.slices, "slices"));

// 8) microtasks can STARVE the loop — they all run before the next task
// let count = 0;
// function again() {
//     if (++count < 100_000) queueMicrotask(again);  // re-queues itself
//     else console.log("microtasks done:", count);
// }
// setTimeout(() => console.log("timer finally runs"), 0);
// queueMicrotask(again);
// // the 0ms timer waits for all 100k microtasks (an infinite version would freeze the page)


// 9) active demo — label every callback with the queue it came from
const log = (queue, msg) => console.log(queue.padEnd(10), "|", msg);

log("sync", "script start");

setTimeout(() => {
    log("task", "timeout 1");
    Promise.resolve().then(() => log("microtask", "promise inside timeout 1"));
}, 0);

setTimeout(() => log("task", "timeout 2"), 0);

Promise.resolve().then(() => {
    log("microtask", "promise 1");
    setTimeout(() => log("task", "timeout queued by promise 1"), 0);
});

(async () => {
    log("sync", "async fn body (before await)");
    await null;
    log("microtask", "async fn after await");
})();

log("sync", "script end");
