/*
Create a JS function that gets a number of seconds, then counts them down.

Example: 
--------
Got seconds = 60  

60
59
58
57
...
0

Time's Up!
 */

function countDown(seconds) {
    const oneSecond = 1000;

    console.log(`Time left ${seconds}`);

    for (let i = 1; i < seconds; i++) {
        setTimeout(updateClock, oneSecond * i, seconds - i);
    }

    setTimeout(() => {
        console.log("Time's Up!");
    }, oneSecond * seconds)
}

function updateClock(timeLeft) {
    console.log(`Time left: ${timeLeft}`);
}

// call the function
countDown(seconds = 5);
console.log(`Some Staff`);
