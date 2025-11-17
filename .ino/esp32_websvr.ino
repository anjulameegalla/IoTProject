// Include all required libraries
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <WiFi.h>
#include <AsyncTCP.h>      // --- NEW: Required for Async Web Server ---
#include <ESPAsyncWebServer.h> // --- NEW: The Async Web Server ---

// --- Your Wi-Fi Credentials ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// --- Sensor & Output Pins ---
#define DHTPIN 4
#define MQ_PIN 34
#define PIR_PIN 23
#define LED_PIN 25

// --- Sensor Objects ---
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// --- NEW: Async Web Server Object ---
AsyncWebServer server(80); // Server on port 80

// --- Global variables to store sensor data ---
float global_humidity = 0;
float global_temperature = 0;
int   global_gasValue = 0;
int   global_pirState = LOW;

// --- Non-Blocking Timer ---
unsigned long previousSensorRead = 0;
const long sensorInterval = 2000; // Read sensors every 2 seconds

void setup() {
  Serial.begin(115200);
  
  // Set pin modes
  pinMode(MQ_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  dht.begin();
  
  Serial.println("PIR calibrating (20s)...");
  delay(20000); // Give PIR time to stabilize
  Serial.println("Calibration complete.");

  // --- Connect to Wi-Fi ---
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // --- NEW: Start the Async Web Server ---
  // We no longer use a separate 'handleRoot' function.
  // We use a "lambda" function (the '[]' part) to handle the request.
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // Build the HTML page as a String
    String page = "<!DOCTYPE html><html><head>";
    page += "<title>ESP32 Sensor Dashboard</title>";
    // This meta tag auto-refreshes the page every 5 seconds
    page += "<meta http-equiv='refresh' content='5'>";
    page += "<style>body { font-family: sans-serif; text-align: center; }";
    page += "h1 { color: #00A; } .sensor { background: #EEE; padding: 15px; margin: 10px; border-radius: 10px; } </style>";
    page += "</head><body>";
    page += "<h1>My ESP32 Dashboard (Async)</h1>";
    
    // Display Sensor Data
    page += "<div class='sensor'><h2>Temperature</h2><p>" + String(global_temperature) + " &deg;C</p></div>";
    page += "<div class='sensor'><h2>Humidity</h2><p>" + String(global_humidity) + " %</p></div>";
    page += "<div class='sensor'><h2>Air Quality</h2><p>" + String(global_gasValue) + "</p></div>";
    
    // Display Motion Data
    page += "<div class='sensor'><h2>Motion</h2>";
    if (global_pirState == HIGH) {
      page += "<p style='color: red; font-weight: bold;'>DETECTED!</p>";
    } else {
      page += "<p>---</p>";
    }
    page += "</div>";
    
    page += "</body></html>";
    
    // Send the page to the client (the browser)
    request->send(200, "text/html", page);
  });
  
  server.begin(); // Start the server
  Serial.println("Async Web server started.");
}

void loop() {
  // --- REMOVED: server.handleClient(); ---
  // This is the biggest benefit! The server runs in the background.
  // Your loop is now clean and only handles sensor logic.

  // --- Non-Blocking sensor read ---
  unsigned long currentMillis = millis();
  if (currentMillis - previousSensorRead >= sensorInterval) {
    // Save the last read time
    previousSensorRead = currentMillis;

    // Read sensors and store in global variables
    global_humidity = dht.readHumidity();
    global_temperature = dht.readTemperature();
    global_gasValue = analogRead(MQ_PIN);
    
    // Print to Serial (for debugging)
    Serial.print("H: "); Serial.print(global_humidity);
    Serial.print(" | T: "); Serial.print(global_temperature);
    Serial.print(" | Gas: "); Serial.println(global_gasValue);
  }

  // --- PIR logic (runs every loop, so it's fast) ---
  global_pirState = digitalRead(PIR_PIN);
  if (global_pirState == HIGH) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}