#include <OneWire.h>
#include <DallasTemperature.h>

#define TMP_SENSOR 7    // select the input pin for the potentiometer
#define LED_PIN 13     // select the pin for the LED

int sensorValue = 0;  // variable to store the value coming from the sensor

OneWire oneWire(TMP_SENSOR);
DallasTemperature sensors(&oneWire);

void setup() {
  // declare the LED_PIN as an OUTPUT:
  pinMode(LED_PIN, OUTPUT);
  pinMode(TMP_SENSOR, INPUT);
  Serial.begin(9600);
  sensors.begin(); 
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  sensors.requestTemperatures();
  sensorValue = sensors.getTempCByIndex(0);
  delay(100);
  digitalWrite(LED_PIN, LOW);


  Serial.print("Temperature is:");
  Serial.println(sensorValue);
  
  delay(2000);
  
  Serial.println("Looping...");
}

