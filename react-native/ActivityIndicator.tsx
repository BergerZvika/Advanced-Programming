import React, { useState } from 'react';
import { ActivityIndicator, View, Text, TouchableOpacity, StyleSheet } from 'react-native';

const ActivityIndicatorExample = () => {
  // 1. State to track if the indicator is spinning
  const [animating, setAnimating] = useState(true);

  // 2. Function to toggle the state
  const toggleActivityIndicator = () => {
    setAnimating(!animating);
  };

  return (
    <View style={styles.container}>
      {/* The Activity Indicator */}
      <ActivityIndicator
        animating={animating}
        color="#bc2b78"
        size="large"
        style={styles.activityIndicator}
      />

      {/* The Control Button */}
      <TouchableOpacity 
        style={[styles.button, { backgroundColor: animating ? '#FF3B30' : '#34C759' }]} 
        onPress={toggleActivityIndicator}
      >
        <Text style={styles.buttonText}>
          {animating ? "Pause Animation" : "Start Animation"}
        </Text>
      </TouchableOpacity>
    </View>
  );
};

export default ActivityIndicatorExample;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#f5f5f5',
  },
  activityIndicator: {
    height: 80,
    marginBottom: 20,
  },
  button: {
    paddingVertical: 12,
    paddingHorizontal: 30,
    borderRadius: 25,
    elevation: 3, // Android shadow
    shadowColor: '#000', // iOS shadow
    shadowOffset: { width: 0, height: 2 },
    shadowOpacity: 0.25,
  },
  buttonText: {
    color: '#ffffff',
    fontSize: 16,
    fontWeight: 'bold',
  },
});