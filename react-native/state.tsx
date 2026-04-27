import React from 'react';
import { Text, View, Button } from 'react-native';

export default class App extends React.Component {
  state = {
      myState: "zvika state",
      count: 0
   }

    render() {
      return (
      <View style={{ flex: 1, justifyContent: 'center', alignItems: 'center' }}>
        <Text> {this.state.myState} </Text>
        <Text>Count: {this.state.count}</Text>
        <Button title="Increase"onPress={() => this.setState({ count: this.state.count + 1 })} />
      </View>
    );
  }
}
