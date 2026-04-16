#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <WiFi.h>

// Pinouts
#define DHTPIN       4
#define DHTTYPE      DHT11     
#define POT_PIN      34          // analog input
#define LED_RED      12
#define LED_GREEN   13
#define LED_BLUE     14
#define LED_WHITE    27

// OLED setup
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Sensor setup
DHT dht(DHTPIN, DHTTYPE);

// Wifi
const char* ssid     = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

// Thresholds (adjusted by potentiometer)
float tempThreshold  = 30.0;   // potentiometer shifts this
float humidThreshold = 70.0;   // fixed

void setup() {
  Serial.begin(115200);

  // LED pins
  pinMode(LED_BLUE,  OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(LED_RED,    OUTPUT);

  // OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED not found!");
    while (true);
  }
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  // Sensor
  dht.begin();

  // WiFi 
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  unsigned long t = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t < 8000) {
    delay(500); Serial.print(".");
  }
  Serial.println(WiFi.status() == WL_CONNECTED ? "\nConnected!" : "\nWiFi skipped.");
}

void setLEDs(bool b, bool g, bool w, bool r) {
  digitalWrite(LED_BLUE,  b);
  digitalWrite(LED_GREEN, g);
  digitalWrite(LED_WHITE, w);
  digitalWrite(LED_RED,    r);
}

void updateDisplay(float temp, float humidity, float threshold) {
  display.clearDisplay();

  // Title
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Bobo Weather Station");

  // Temperature
  display.setTextSize(2);
  display.setCursor(0, 14);
  display.print(temp, 1);
  display.print((char)247);  
  display.println("C");

  // Humidity
  display.setTextSize(1);
  display.setCursor(0, 36);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println("%");

  // Threshold
  display.setCursor(0, 48);
  display.print("Alert at: ");
  display.print(threshold, 1);
  display.print((char)247);
  display.println("C");

  display.display();
}

void loop() {
  // Read potentiometer to map to temp threshold (20–40 C)
  int potVal = analogRead(POT_PIN);                  
  tempThreshold = map(potVal, 0, 4095, 20, 40);

  // Read DHT sensor
  float humidity    = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Sensor read failed!");
    return;
  }

  Serial.printf("Temp: %.1f°C  Humidity: %.1f%%  Threshold: %.0f°C\n",
                temperature, humidity, tempThreshold);

  // Update display
  updateDisplay(temperature, humidity, tempThreshold);

  // LED logic
  bool tooHot   = temperature >= tempThreshold;
  bool tooHumid = humidity    >= humidThreshold;

  if (tooHot && tooHumid) {
    setLEDs(0, 0, 0, 1);   // RED - danger
  } else if (tooHot) {
    setLEDs(0, 1, 0, 0);   // green- warm
  } else if (tooHumid) {
    setLEDs(0, 0, 1, 0);   // BLUE - humid
  } else {
    setLEDs(1, 0, 0, 0);   // White - all good
  }

  delay(2000);   // DHT22 max sample rate is 0.5 Hz
}
