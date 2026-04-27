import React from 'react';
import { Text, View } from 'react-native';


const Greeting = ({ name }) => <Text>Hello {name}!</Text>;

export default class App extends React.Component {
  state = {
      myState: "zvika state",
      count: 0
   }

    render() {
return (
    <View style={{ flex: 1, padding: 50 }}>
      <Greeting name="Student" />
      <Greeting name="Teaching Assistant" />
    </View>
    );
  }
}
