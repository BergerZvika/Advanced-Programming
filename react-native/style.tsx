import { StyleSheet, View } from 'react-native';

export default function LayoutDemo() {
  return (
    <View style={styles.container}>
      <View style={styles.boxRed} />
      <View style={styles.boxBlue} />
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    flexDirection: 'row', // Horizontal
    justifyContent: 'center', // Main axis
    alignItems: 'center', // Cross axis
  },
  boxRed: { width: 50, height: 50, backgroundColor: 'red' },
  boxBlue: { width: 50, height: 50, backgroundColor: 'blue' },
});