/*
 Standalone Sketch to use with a Arduino Fio and a 
 Sharp Optical Dust Sensor GP2Y1010AU0F
 
 Blog: http://arduinodev.woofex.net/2012/12/01/standalone-sharp-dust-sensor/
 Code: https://github.com/Trefex/arduino-airquality/
 For Pin connections, please check the Blog or the github project page
 Authors: Cyrille Médard de Chardon (serialC), Christophe Trefois (Trefex)
 Changelog:
   2012-Dec-01: Cleaned up code
   2012-Dec-13: Converted mg/m3 to ug/m3 which seems to be the accepted standard
 This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
 To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter 
 to Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA. 
 */
int measurePin = 0;
int ledPower = 2;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float dustDensityAvg = 0;

float dustDensitySamples[10] = {};
int sampleCount = 0;

#include <SPI.h>
#include <Wire.h>


void setup(){
  Serial.begin(9600);
  pinMode(ledPower,OUTPUT);
  
  takeDustSample();
}


void loop(){
  sampleCount = 0;
  while(sampleCount < 10) {
    takeDustSample();
    dustDensitySamples[sampleCount] = dustDensity;
    sampleCount++;
    delay(1000);
  }

  calculateAverageDustDensity();
  delay(60000);
}

void calculateAverageDustDensity() {
  dustDensityAvg = 0;
  sampleCount = 0;
  while(sampleCount < 10) {
    dustDensityAvg += dustDensitySamples[sampleCount];
    sampleCount++;
  }
  Serial.println(dustDensityAvg);
  dustDensityAvg = dustDensityAvg / 10.0;
}

void takeDustSample() {
  digitalWrite(ledPower,LOW); // power on the LED
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin); // read the dust value
  
  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH); // turn the LED off
  delayMicroseconds(sleepTime);

  // 0 - 5.0V mapped to 0 - 1023 integer values 
  calcVoltage = voMeasured * (3.0 / 1024.0); 
  
  // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
  // Chris Nafis (c) 2012
  dustDensity = (0.17 * calcVoltage - 0.1)*1000; 
  
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
  
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
  
  Serial.print(" - Dust Density [ug/m3]: ");
  Serial.println(dustDensity);
}

