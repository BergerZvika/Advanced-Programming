
import React from 'react';
import ReactDOM from 'react-dom/client';

function HelloReact2(props) {
    return <h1>Hello React again { props.val}!</h1>;
  }
  
  function HelloReact(props) {
    return <h1>Hello React { props.val}!</h1>;
  }

function Hello(props) {
    const flag = props.flag;
    if (flag) {
      return <HelloReact val={props.val} />;
    }
    return <HelloReact2 val={props.val}/>;
  }
  
  const root = ReactDOM.createRoot(document.getElementById('root'));
  root.render(<Hello flag={true}  val={5} />);