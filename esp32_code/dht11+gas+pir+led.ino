// Include the required libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>

// --- Sensor & Output Pins ---
#define DHTPIN 4       // GPIO 4 (DHT11)
#define MQ_PIN 34      // GPIO 34 (MQ Sensor)
#define PIR_PIN 23     // GPIO 23 (PIR Sensor)
#define LED_PIN 25     // --- NEW: GPIO 25 (LED) ---

// --- Sensor Objects & Variables ---
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int pirState = LOW;

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  Serial.println("DHT11, MQ Gas, PIR, and LED Test!");

  // Initialize the DHT sensor
  dht.begin();
  
  // Set the pin modes
  pinMode(MQ_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT); // --- NEW: Set LED pin as an OUTPUT ---
  
  Serial.println("Sensors initializing... (PIR needs ~10s to calibrate)");
  delay(10000); // Give the PIR sensor 10 seconds to stabilize
  Serial.println("Ready.");
}

void loop() {
  // --- Read from DHT11 ---
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // --- Read from MQ Sensor ---
  int gasValue = analogRead(MQ_PIN);

  // --- Read from PIR Sensor ---
  pirState = digitalRead(PIR_PIN);

  // --- Print all data to the Serial Monitor ---
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C");
  Serial.print("  |  Air Quality: ");
  Serial.print(gasValue);

  // --- NEW: Control LED based on PIR state ---
  if (pirState == HIGH) {
    Serial.println("  |  Motion: DETECTED!");
    digitalWrite(LED_PIN, HIGH); // Turn the LED ON
  } else {
    Serial.println("  |  Motion: ---");
    digitalWrite(LED_PIN, LOW);  // Turn the LED OFF
  }

  // Shorter delay so we can catch motion faster
  delay(1000); 
}