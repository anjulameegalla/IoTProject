// Include the required libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Define the pin you connected the DATA pin to. We chose GPIO 4 (D4).
#define DHTPIN 4 

// Define the type of sensor you are using (DHT11)
#define DHTTYPE DHT11

// Initialize the DHT sensor object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the Serial Monitor at 115200 baud
  Serial.begin(115200);
  Serial.println("DHT11 Test Start!");

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Wait 2 seconds between readings. The DHT11 is slow!
  delay(2000);

  // Read the humidity
  float h = dht.readHumidity();
  // Read the temperature as Celsius
  float t = dht.readTemperature();
  // Read the temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any readings failed and exit early to try again.
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // --- If the readings were successful, print them! ---
  
  // Print the data to the Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("%  |  ");
  
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print("°C  |  ");
  Serial.print(f);
  Serial.println("°F");
}