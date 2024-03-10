#include <TimedAction.h> // Include the TimedAction library for scheduling timed actions
#define ADC_VREF_mV    5000.0 // in millivolt
#define ADC_RESOLUTION 1024.0
#define PIN_LM35 A0
#define PIN_LED 2

const int thresholdTemperature = 30; // Define threshold temperature

// Initialize variables
int currentTemperature = 0;

// Initialize TimedAction for LED blinking
TimedAction blinkAction = TimedAction(1000, blinkLed); // Default blink interval is 1000ms

// Setup function
void setup() {
  // Set LM35 pin as input and LED pin as output
  pinMode(PIN_LM35, INPUT);
  pinMode(PIN_LED, OUTPUT);

  // Begin serial communication
  Serial.begin(9600);

  // Turn on LED initially
  digitalWrite(PIN_LED, HIGH);
}

// Main loop function
void loop() {
  int adcVal = analogRead(PIN_LM35);  // Read ADC value from LM35 temperature sensor
  float milliVolt = adcVal * (ADC_VREF_mV / ADC_RESOLUTION);   // Convert ADC value to voltage in millivolt
  currentTemperature = milliVolt / 10; // Convert voltage to temperature in Celsius
  Serial.print(currentTemperature);  // Print current temperature to serial monitor
  Serial.println(" C");

  // Adjust LED blink interval based on temperature
  if (currentTemperature < thresholdTemperature) {
    blinkAction.setInterval(250); // Set blink interval to 250ms
  } else {
    blinkAction.setInterval(500); // Set blink interval to 500ms
  }

  // Check if it's time to run the blink action
  blinkAction.check();
}

// Function to blink LED
void blinkLed() {
  static bool ledState = HIGH; // Variable to track LED state
  ledState = !ledState; // Toggle LED state
  digitalWrite(PIN_LED, ledState); // Set LED state
  Serial.println("Blinking"); // Print message indicating LED blinking
}
