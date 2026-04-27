import 'react-native-gesture-handler';
import React from 'react';
import { TouchableOpacity, Text, StyleSheet, View } from 'react-native';
import { NavigationContainer } from '@react-navigation/native';
import { createStackNavigator } from '@react-navigation/stack';

// Screens
import HomeScreen from './src/screens/HomeScreen';
import SettingsScreen from './src/screens/SettingsScreen';
import ProfileScreen from './src/screens/ProfileScreen';
import NotificationsScreen from './src/screens/NotificationsScreen';

const Stack = createStackNavigator();

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator 
        initialRouteName="Home"
        screenOptions={({ navigation }) => ({
          headerStyle: { backgroundColor: '#bc2b78', height: 100 },
          headerTintColor: '#fff',
          headerTitleStyle: { fontWeight: 'bold' },
          headerTitleAlign: 'center',

          // 1. LEFT SIDE: Settings
          headerLeft: () => (
              <TouchableOpacity onPress={() => navigation.navigate('Home')}>
                <Text style={styles.iconText}>🏠</Text>
              </TouchableOpacity>
          ),

          // 2. RIGHT SIDE: Home, Notifications, Profile
          headerRight: () => (
            <View style={styles.rightToolbar}>
              <TouchableOpacity 
              style={styles.leftIcon} 
              onPress={() => navigation.navigate('Settings')}>
              <Text style={styles.iconText}>⚙️</Text>
            </TouchableOpacity>
              
              <TouchableOpacity onPress={() => navigation.navigate('Notifications')}>
                <Text style={styles.iconText}>🔔</Text>
              </TouchableOpacity>
              
              <TouchableOpacity onPress={() => navigation.navigate('Profile')}>
                <Text style={styles.iconText}>👤</Text>
              </TouchableOpacity>
            </View>
          ),
        })}
      >
        <Stack.Screen name="Home" component={HomeScreen} options={{ title: 'MAIN' }} />
        <Stack.Screen name="Settings" component={SettingsScreen} options={{ title: 'CONFIG' }} />
        <Stack.Screen name="Profile" component={ProfileScreen} options={{ title: 'USER' }} />
        <Stack.Screen name="Notifications" component={NotificationsScreen} options={{ title: 'ALERTS' }} />
      </Stack.Navigator>
    </NavigationContainer>
  );
}

const styles = StyleSheet.create({
  rightToolbar: {
    flexDirection: 'row',
    alignItems: 'center',
    marginRight: 15,
  },
  leftIcon: {
    marginLeft: 15,
  },
  iconText: {
    fontSize: 22,
    marginHorizontal: 8,
    color: '#fff',
  }
});