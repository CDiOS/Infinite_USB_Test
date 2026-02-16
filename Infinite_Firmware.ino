/*
USB HID Controller
Open-source USB HID hardware  USB input integration across a variety of simulation
platforms and in-game vehicle types.

This project exists for development, testing, and compatibility
validation.

  USB HID functionality implemented using the Arduino
  Joystick Library by Matthew Heironimus (MIT License).
  https://github.com/MHeironimus/ArduinoJoystickLibrary
*/

#include <Joystick.h>

/* -------- USB Identity -------- */
#define USB_MANUFACTURER "Infinite Design Works"
#define USB_PRODUCT      "Infinite Cab"
#define USB_SERIAL       "GHC-DEV-001"

/* -------- Joystick Definition --------
   Simple, widely-compatible layout:
   - 2 axes
   - 8 buttons
*/
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  8,    // Button count
  0,    // Hat switches
  true, // X Axis
  true, // Y Axis
  false,// Z
  false,// Rx
  false,// Ry
  false,// Rz
  false,// Rudder
  false,// Throttle
  false,// Accelerator
  false,// Brake
  false // Steering
);

void setup() {
  Joystick.begin();

  // Standard axis ranges
  Joystick.setXAxisRange(0, 1023);
  Joystick.setYAxisRange(0, 1023);
}

void loop() {
  /* -------- Axis Test --------
     Continuous sweep to verify detection
  */
  static int axisValue = 0;
  static int direction = 1;

  axisValue += direction * 5;
  if (axisValue >= 1023 || axisValue <= 0) {
    direction = -direction;
  }

  Joystick.setXAxis(axisValue);
  Joystick.setYAxis(1023 - axisValue);

  /* -------- Button Test --------
     Toggle button 0 every second
  */
  static unsigned long lastToggle = 0;
  static bool buttonState = false;

  if (millis() - lastToggle > 1000) {
    lastToggle = millis();
    buttonState = !buttonState;
    Joystick.setButton(0, buttonState);
  }

  delay(10);
}
