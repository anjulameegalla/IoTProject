// Include the required libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>

// --- DHT11 Sensor Setup ---
#define DHTPIN 4       // GPIO 4 (D4)
#define DHTTYPE DHT11  // Sensor type
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor

// --- MQ Sensor Setup ---
// GPIO 34 is a great pin for analog inputs on ESP32
#define MQ_PIN 34      // GPIO 34 (Analog input)

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  Serial.println("DHT11 & MQ Gas Sensor Test Start!");

  // Initialize the DHT sensor
  dht.begin();
  
  // Set the MQ pin as an input
  // (Not strictly needed for analogRead, but good practice)
  pinMode(MQ_PIN, INPUT);
}

void loop() {
  // Wait 2 seconds between readings
  delay(2000);

  // --- Read from DHT11 ---
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  // --- Read from MQ Sensor ---
  // Read the analog value from the sensor
  // ESP32 ADC has 12-bit resolution, so the value is 0-4095
  int gasValue = analogRead(MQ_PIN);

  // Check if DHT readings failed
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  // --- Print all data to the Serial Monitor ---
  
  // Print DHT Data
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C  |  ");
  Serial.print(f);
  Serial.print("°F");

  // Print MQ Data
  Serial.print("  |  Air Quality: ");
  Serial.println(gasValue); // This will be a number from 0-4095
}