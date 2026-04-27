import React from 'react';
import { StyleSheet, Text, View, Image, ScrollView, SafeAreaView } from 'react-native';

export default function ImageExample() {
  return (
    <SafeAreaView style={styles.container}>
      <ScrollView contentContainerStyle={styles.centerContent}>
        
        <Text style={styles.title}>Image Demonstration</Text>

        {/* 1. Displaying a Local Asset */}
        <Text style={styles.label}>Local Asset (icon.png):</Text>
        <Image 
          source={require('./assets/icon.png')} 
          style={styles.localImage} 
        />

        {/* 2. Displaying a Network Image from a URL */}
        <Text style={styles.label}>Network Image (from URL):</Text>
        <Image 
          source={{ uri: 'https://reactnative.dev/img/tiny_logo.png' }} 
          style={styles.networkImage} 
        />

      </ScrollView>
    </SafeAreaView>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
  },
  centerContent: {
    alignItems: 'center',
    padding: 20,
  },
  title: {
    fontSize: 24,
    fontWeight: 'bold',
    marginBottom: 20,
  },
  label: {
    fontSize: 16,
    fontWeight: '600',
    marginTop: 20,
    marginBottom: 10,
    alignSelf: 'flex-start',
  },
  localImage: {
    width: 100,
    height: 100,
    borderRadius: 20, // Making it rounded
  },
  networkImage: {
    width: 100,
    height: 100,
  },
  bannerImage: {
    width: '100%',
    height: 200,
    borderRadius: 10,
    borderWidth: 2,
    borderColor: '#ddd',
  },
});