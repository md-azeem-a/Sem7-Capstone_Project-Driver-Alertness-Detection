#include <Wire.h>         // For I2C communication
#include <Adafruit_Sensor.h> // For Adafruit sensor library
#include <Adafruit_ADXL345_U.h>  // For ADXL345 sensor

const int blinkSensorPin = 7;  // Eye blink sensor connected to D2
const int buzzer = 8;          // LED connected to D4 (for direct control if needed)
const int ledPin = 4;          // LED connected to D4 (for direct control if needed) 
const int vib = 6;          

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

int16_t ax, ay, az;  // Accelerometer readings for X, Y, and Z axis
int data[2]; // Array to hold X and Y axis data

const int SLEEP_THRESHOLD1 = 10;
const int SLEEP_THRESHOLD2 = -10;  
const int SLEEP_THRESHOLD3 = -10; 

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize I2C communication
  Wire.begin();
  
  pinMode(blinkSensorPin, INPUT);     // Eye blink sensor as input
  pinMode(ledPin, OUTPUT);            // LED as output
  pinMode(buzzer, OUTPUT);  
  pinMode(vib, OUTPUT); 
  

  // Initialize the ADXL345 sensor
  if (!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while (1);
  }

  // Print initialization message
  Serial.println("ADXL345 connected and ready!");
  
  digitalWrite(vib, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);       
}
void adxl() {
  // Read accelerometer values from the ADXL345
  sensors_event_t event;
  accel.getEvent(&event);

  // Map the accelerometer data to more manageable ranges
  data[0] = event.acceleration.x;  // X-axis data
  data[1] = event.acceleration.y;  // Y-axis data

  // Print the mapped data for debugging
  Serial.print("X: ");
  Serial.print(data[0]);
  Serial.print(" Y: ");
  Serial.println(data[1]);

  // Trigger conditions based on accelerometer data
 if (data[0] >= SLEEP_THRESHOLD1) {
  delay (2000);
    digitalWrite(vib, HIGH);
  }
  else if (data[0] <= SLEEP_THRESHOLD2) {
    delay (2000);
   digitalWrite(vib, HIGH);
  }
  else if (data[1] <= SLEEP_THRESHOLD3) {
    delay (2000);
   digitalWrite(vib, HIGH);
  }
  else {
        digitalWrite(vib, LOW);
     }
}

void loop() {
  adxl();
   int sensorValue = digitalRead(blinkSensorPin);  // Read the eye blink sensor
    if (sensorValue == LOW) {  // If eye is closed (sensor output is high)
      delay(2000);
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);       // Turn on LED if controlled separately
     
}
else{
  digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);       // Turn on LED if controlled separately
     delay(1000);
  
  }

  
}
