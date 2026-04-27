import React, { useState } from 'react';
import { View, Text, StyleSheet } from 'react-native';
import { Picker } from '@react-native-picker/picker';

// npx expo install @react-native-picker/picker
const PickerExample = () => {
  // 1. State to hold the selected value
  const [selectedCourse, setSelectedCourse] = useState('react_native');

  return (
    <View style={styles.container}>
      <Text style={styles.label}>Select a Course to Learn:</Text>
      
      <View style={styles.pickerContainer}>
        <Picker
          selectedValue={selectedCourse}
          onValueChange={(itemValue) => setSelectedCourse(itemValue)}
          style={styles.picker}
          dropdownIconColor="#007AFF"
        >
          {/* 2. Defining the options */}
          <Picker.Item label="React Native" value="react_native" />
          <Picker.Item label="TypeScript" value="typescript" />
          <Picker.Item label="Android" value="android" />
          <Picker.Item label="MongoDB" value="mongodb" />
        </Picker>
      </View>

      {/* 3. Displaying the selection */}
      <View style={styles.resultBox}>
        <Text style={styles.resultText}>
          Currently studying: <Text style={styles.boldText}>{selectedCourse.replace('_', ' ')}</Text>
        </Text>
      </View>
    </View>
  );
};

export default PickerExample;

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    padding: 20,
    backgroundColor: '#fff',
  },
  label: {
    fontSize: 18,
    fontWeight: '600',
    marginBottom: 10,
    color: '#333',
  },
  pickerContainer: {
    borderWidth: 1,
    borderColor: '#ddd',
    borderRadius: 10,
    backgroundColor: '#f9f9f9',
    overflow: 'hidden', // Ensures the picker stays inside rounded corners
  },
  picker: {
    height: 50,
    width: '100%',
  },
  resultBox: {
    marginTop: 30,
    padding: 20,
    backgroundColor: '#E1F5FE',
    borderRadius: 8,
  },
  resultText: {
    fontSize: 16,
    color: '#01579B',
    textAlign: 'center',
  },
  boldText: {
    fontWeight: 'bold',
    textTransform: 'capitalize',
  },
});