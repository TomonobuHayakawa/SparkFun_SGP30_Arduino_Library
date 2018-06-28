/*
  Library for the Sensirion SGP30 Indoor Air Quality Sensor
  By: Ciara Jekel
  SparkFun Electronics
  Date: June 28th, 2018
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

  SGP30 Datasheet: https://cdn.sparkfun.com/assets/4/7/d/f/b/Sensirion_SGP30_Datasheet.pdf

  Feel like supporting our work? Buy a board from SparkFun!
  https://www.sparkfun.com/products/14813

  This example reads the sensors calculated CO2 and
  TVOC values  and the raw values for H2 and ethanol.
*/

#include "SparkFun_SGP30_Library.h" // Click here to get the library: http://librarymanager/All#SparkFun_SGP30
#include <Wire.h>

SGP30 mySensor; //create an object of the SGP30 class

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //Sensor supports I2C speeds up to 400kHz
  Wire.setClock(400000);
  //Initialize sensor
  if (mySensor.begin() != SUCCESS) {
    Serial.println("No SGP30 Detected. Check connections.");
    while (1);
  }
  //Initializes sensor for air quality readings
  mySensor.initAirQuality();

}

void loop() {
  //First fifteen readings will be
  //CO2: 400 ppm  TVOC: 0 ppb
  delay(1000); //Wait 1 second
  //measure CO2 and TVOC levels
  mySensor.measureAirQuality();
  Serial.print("CO2: ");
  Serial.print(mySensor.CO2);
  Serial.print(" ppm\tTVOC: ");
  Serial.print(mySensor.TVOC);
  Serial.println(" ppb");
  //get raw values for H2 and Ethanol
  mySensor.measureRawSignals();
  Serial.print("Raw H2: ");
  Serial.print(mySensor.H2);
  Serial.print(" \tRaw Ethanol: ");
  Serial.println(mySensor.ethanol);
}