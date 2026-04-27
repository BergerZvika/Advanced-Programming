import React, { Component, memo } from "react";

// Regular Child Component (always re-renders)
const RegularChild = ({ value }) => {
  console.log("RegularChild Rendered");
  return <h3>Regular Child: {value}</h3>;
};

// Optimized Child Component (wrapped with React.memo)
const MemoizedChild = memo(({ value }) => {
  console.log("MemoizedChild Rendered");
  return <h3>Memoized Child: {value}</h3>;
});

// Parent Class Component
class App extends Component {
  constructor(props) {
    super(props);
    this.state = {
      count: 0,
      otherValue: 0,
    };
  }

  incrementCount = () => {
    this.setState((prevState) => ({ count: prevState.count + 1 }));
  };

  incrementOtherValue = () => {
    this.setState((prevState) => ({ otherValue: prevState.otherValue + 1 }));
  };

  render() {
    console.log("Parent Rendered");

    return (
      <div style={{ textAlign: "center", marginTop: "50px" }}>
        <h1>React.memo Example Without Hooks</h1>
        <button onClick={this.incrementCount} style={{ padding: "10px", margin: "10px" }}>
          Increment Count
        </button>
        <button onClick={this.incrementOtherValue} style={{ padding: "10px", margin: "10px" }}>
          Increment Other Value
        </button>

        <p>Parent Count: {this.state.count}</p>

        {/* Regular Child */}
        <RegularChild value={this.state.count} />

        {/* Memoized Child */}
        <MemoizedChild value={this.state.otherValue} />
      </div>
    );
  }
}

export default App;
