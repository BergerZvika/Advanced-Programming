/*
Creating a React App
Use the create-react-app command to set up a new React project:

  npx create-react-app my-app
  cd my-app
  npm start

This starts the development server, and you can view your app at http://localhost:3000.
React in wsl: https://learn.microsoft.com/en-us/windows/dev-environment/javascript/react-on-wsl 
*/

import React from 'react';
import ReactDOM from 'react-dom/client';

// Functional Component:
function Hello(props) {
  return <h1>Hello React!</h1>;
}

// Class Component:
// class Hello extends React.Component {
//   render() {
//     return <h1>Welcome to React!</h1>;
//   }
// }

const container = document.getElementById("root");
const root = ReactDOM.createRoot(container);
root.render(<Hello />);

