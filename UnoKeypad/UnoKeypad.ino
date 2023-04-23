#include <Keypad.h>

// Define the keypad layout
const byte ROWS = 4;
const byte COLS = 3;
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3}; // Connect to the column pinouts of the keypad

// Define the solenoid lock pin
const int solenoidPin = 2;

// Define the correct password
const char password[] = "123#";

// Define a variable to keep track of the current input password
String currentPassword = "";

// Initialize the keypad library
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // Set the solenoid lock pin as an output
  pinMode(solenoidPin, OUTPUT);
  // Initialize the serial communication
  Serial.begin(9600);
}

void loop() {
  // Get the next key from the keypad
  char key = keypad.getKey();
  if (key) {
    // A key has been pressed, add it to the current input password
    currentPassword += key;
    // Print the current input password to the serial monitor
    Serial.println(currentPassword);
    // Check if the current input password matches the correct password
    if (currentPassword == password) {
      // The password is correct, unlock the solenoid lock
      digitalWrite(solenoidPin, HIGH);
      delay(1000); // Wait for 1 second
      digitalWrite(solenoidPin, LOW);
      // Clear the current input password
      currentPassword = "";
    } else if (currentPassword.length() >= sizeof(password) - 1) {
      // The input password is too long, clear it
      currentPassword = "";
    }
  }
}
