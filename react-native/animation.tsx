import React, { useRef } from 'react';
import { Animated, View, Button } from 'react-native';

export default function AnimDemo() {
  const fadeAnim = useRef(new Animated.Value(0)).current;

  const fadeIn = () => {
    Animated.timing(fadeAnim, { toValue: 1, duration: 2000, useNativeDriver: true }).start();
  };

  return (
    <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
      <Animated.View style={{ opacity: fadeAnim, width: 100, height: 100, backgroundColor: 'purple' }} />
      <Button title="Fade In" onPress={fadeIn} />
    </View>
  );
}