// Arduino Multi-LED Sequential Blink
// Author: Sameeran

// Define LED pins in an array
int ledPins[] = {13, 12, 8, 7, 4, 2};
int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
//int numleds = 6;

void setup() {
  // Set all pins as output
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);  // Turn LED ON
    delay(200);                     // Wait 1 sec
    digitalWrite(ledPins[i], LOW);   // Turn LED OFF
    delay(200);                     // Wait 1 sec
  }
   for (int i = numLeds-1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);  // Turn LED ON
    delay(200);                     // Wait 1 sec
    digitalWrite(ledPins[i], LOW);   // Turn LED OFF
    delay(200);                     // Wait 1 sec
  }
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(ledPins[i], HIGH);  // Turn LED ON
    delay(100);                     // Wait 1 sec
    digitalWrite(ledPins[i], LOW);   // Turn LED OFF
    delay(100);                     // Wait 1 sec
  }
}
