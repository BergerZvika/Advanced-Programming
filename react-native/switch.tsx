import React, { useState } from 'react';
import { View, Text, Switch, StyleSheet, SafeAreaView } from 'react-native';

const SwitchExample = () => {
  // 1. Initialize the state (false = Light Mode, true = Dark Mode)
  const [isEnabled, setIsEnabled] = useState(false);

  // 2. Function to handle the toggle
  const toggleSwitch = () => setIsEnabled(previousState => !previousState);

  return (
    <SafeAreaView style={[styles.container, isEnabled ? styles.darkBg : styles.lightBg]}>
      <View style={styles.content}>
        <Text style={[styles.statusText, { color: isEnabled ? '#fff' : '#000' }]}>
          {isEnabled ? 'Dark Mode is ON' : 'Light Mode is ON'}
        </Text>

        {/* 3. The Switch Component */}
        <Switch
          trackColor={{ false: '#767577', true: '#81b0ff' }} // Background color when off/on
          thumbColor={isEnabled ? '#f5dd4b' : '#f4f3f4'}    // Circle color
          ios_backgroundColor="#3e3e3e"
          onValueChange={toggleSwitch}
          value={isEnabled}
        />
      </View>
    </SafeAreaView>
  );
};

export default SwitchExample;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
  },
  lightBg: {
    backgroundColor: '#ffffff',
  },
  darkBg: {
    backgroundColor: '#121212',
  },
  content: {
    alignItems: 'center',
    padding: 20,
    borderRadius: 15,
    backgroundColor: 'rgba(150, 150, 150, 0.1)',
  },
  statusText: {
    fontSize: 20,
    fontWeight: 'bold',
    marginBottom: 20,
  },
});