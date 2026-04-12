// 'use strict';  // to use strict mode. 
// // read: https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Strict_mode

// // objects contain attributes and methods
// // if you want to define an object you
// // can simply declare one using the following syntax:

// const my_obj = {attribute1: 'value1', attribute2: 'value2'} // this is called an `object literal`

// // and print it
// console.log(my_obj)  // prints { attribute1: 'value1', attribute2: 'value2' }

// // BTW this is a cool JS feature,
// // use console.table instead of log
// // to output a nice table describing the object  
// console.table(my_obj) 

// // you can access object attributes in the following ways:
// // 1)
// let attr1 = my_obj.attribute1  // object_name.attribute_name

// // // 2)
// let attr2 = my_obj['attribute2']  // object_name['attribute_name']

// console.log(attr1, attr2)  // prints `value1 value2`   // log adds a space

// // objects can have methods
// const person = {
//     firstName: "Israel",
//     lastName : "Israeli",
//     id       : 1948,
//     fullName : function() {
//         // we use `this` to reference the object that its `fullName` method is invoked
//         return this.firstName + " " + this.lastName; 
//     }
//   };

// console.log(person.fullName());

// // // another way of creating an object is by defining a class

// class Car {
//     #fuel_capacity;
//     #current_fuel;

//     constructor (name, year, fuel_capacity) {
//         this.name = name;
//         this.year = year;
//         this.#fuel_capacity = fuel_capacity;  // private attribute
//         this.#current_fuel = 0;
//     }

//     fuel_car(fuel_amount) {
//         const new_current_fuel = this.#current_fuel + fuel_amount

//         if (new_current_fuel <= this.#fuel_capacity)
//             this.#current_fuel = new_current_fuel
//     }

//     current_fuel() {
//         return this.#current_fuel
//     }
// }

// const car = new Car("Mazda", 1998, 500)

// car.fuel_car(20)
// console.log(car.current_fuel())

// // // you can add new attributes or methods to an object at runtime
// car.color = "blue"

// car.paint = function (new_color) {
//     this.color = new_color
// }

// console.log(car)

// car.paint("red")

// console.log(car)

// // we can `freeze` objects to make them immutable
frozen_object = {a: 'a', b: 'b'} 

Object.freeze(frozen_object)

frozen_object.a = 'not a'  // error (only in stricy mode - otherwise the operation will do nothing)

console.log(frozen_object)
