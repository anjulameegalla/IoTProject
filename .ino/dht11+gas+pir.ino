// Include the required libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>

// --- DHT11 Sensor Setup ---
#define DHTPIN 4       // GPIO 4 (D4)
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- MQ Sensor Setup ---
#define MQ_PIN 34      // GPIO 34 (Analog input)

// --- NEW: PIR Sensor Setup ---
#define PIR_PIN 23     // GPIO 23 (Digital input)
int pirState = LOW;    // Variable to store the PIR status

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  Serial.println("DHT11, MQ Gas, and PIR Sensor Test!");

  // Initialize the DHT sensor
  dht.begin();
  
  // Set the pin modes
  pinMode(MQ_PIN, INPUT);
  pinMode(PIR_PIN, INPUT); // --- NEW ---
  
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

  // --- NEW: Read from PIR Sensor ---
  pirState = digitalRead(PIR_PIN);

  // --- Print all data to the Serial Monitor ---
  
  // Print DHT Data
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C");

  // Print MQ Data
  Serial.print("  |  Air Quality: ");
  Serial.print(gasValue);

  // Print PIR Data
  if (pirState == HIGH) {
    Serial.println("  |  Motion: DETECTED!");
  } else {
    Serial.println("  |  Motion: ---");
  }

  // Shorter delay so we can catch motion faster
  delay(1000); 
}