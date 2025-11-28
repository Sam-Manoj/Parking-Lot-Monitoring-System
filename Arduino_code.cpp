#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Sensor pins (6 sensors)
int sensorPins[6] = {2, 3, 4, 5, 6, 7}; 
int occupied = 0;
int totalSpots = 6;

void setup() {
  Serial.begin(9600);

  // Initialize sensors
  for (int i = 0; i < 6; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed to start!");
    while (1);
  }
  delay(1000);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  occupied = 0;

  // Read sensors
  for (int i = 0; i < 6; i++) {
    int sensorValue = digitalRead(sensorPins[i]);
    
    // TCRT5000: LOW = Object detected
    if (sensorValue == LOW) {
      occupied++;
    }
  }

  int vacant = totalSpots - occupied;

  // Display Result
  display.clearDisplay();
  display.setCursor(0, 10);
  display.print("Occupied: ");
  display.println(occupied);

  display.setCursor(0, 35);
  display.print("Vacant: ");
  display.println(vacant);

  display.display();
  delay(500);
}
