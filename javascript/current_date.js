/* 
Write a JavaScript program to display the current day and time in the following format:
Today is: Tuesday.
Current time is: 11 PM : 30 : 38
*/


const daylist = ["Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"];

function logCurrentDate() {
    // get today's Date object
    const today = new Date();

    // get the day as a number
    const day = today.getDay();

    console.log(`Today is: ${daylist[day]}.`); // formatted string 

    // now for the time in the day

    let hour = today.getHours();
    const minute = today.getMinutes();
    const second = today.getSeconds();

    const prepand = (hour >= 12)? "PM": "AM" // instead of using if else
    
    hour = (hour >= 12)? hour - 12: hour 

    if (hour === 0 && prepand === 'PM') { 
        if (minute === 0 && second === 0) { 
            prepand = ' Noon';
        }

        hour = 12;
    }

  if (hour === 0 && prepand === 'AM') { 
    if (minute === 0 && second === 0) { 
      prepand = ' Midnight';
    } 
    
    hour = 12;
  }

  console.log(`Current Time: ${hour} ${prepand} : ${minute} : ${second}`)
};

// call the function
logCurrentDate()

