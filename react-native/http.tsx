import React, { useEffect, useState } from 'react';
import { ActivityIndicator, Text, View } from 'react-native';

export default function HttpDemo() {
  const [data, setData] = useState(null);

  // https://jsonplaceholder.typicode.com/
  useEffect(() => {
    fetch('https://jsonplaceholder.typicode.com/posts/1')
      .then(res => res.json())
      .then(json => setData(json));
  }, []);

  return (
    <View style={{ flex: 1, justifyContent: 'center' }}>
      {!data ? <ActivityIndicator /> : <Text>{data.title}</Text>}
    </View>
  );
}