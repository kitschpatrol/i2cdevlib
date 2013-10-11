#include <Wire.h>
#include "I2Cdev.h"
#include "MS561101BA.h"

MS561101BA alt1(MS561101BA_ADDRESS_CSB_LOW, MS561101BA_OSR_4096);

void setup() {
  Wire.begin();
  Serial.begin(9600);

  Serial.println("Initializing I2C device...");
  alt1.initialize();

  // Verify connection
  Serial.println("Testing device connections...");
  Serial.println(alt1.testConnection() ? "MS5611 connection successful" : "MS5611 connection failed");  
}

void loop() {  
  float pressure = 0;
  float temperature = 0;
  
  alt1.readValues(&pressure, &temperature);
  
  Serial.print("Pressure: ");
  Serial.print(pressure);  
  Serial.print("\tTemperature: ");
  Serial.print(temperature);
  
  float altitude = calculateAltitude(pressure, temperature, 1016.8);
  Serial.print("\tAltitude: ");  
  Serial.println(altitude);  
}

float calculateAltitude(float pressure, float temperature, float localSeaLevelPressure) {
  // Hypsometric formula
  return ((pow(localSeaLevelPressure / pressure, 1.0 / 5.257) - 1.0) * (temperature + 273.15)) / 0.0065;
}




