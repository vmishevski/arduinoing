/***************************************************************************
  This is a library for the CCS811 air 

  This sketch reads the sensor

  Designed specifically to work with the Adafruit CCS811 breakout
  ----> http://www.adafruit.com/products/3566

  These sensors use I2C to communicate. The device's I2C address is 0x5A

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include "Adafruit_CCS811.h"
//#include <ESP8266WiFi.h>
//#include <PubSubClient.h>
#define CCS811_ADDRESS (0x5A)

Adafruit_CCS811 ccs;

//const char* ssid = "Mishevski Doma";
//const char* password = "Bumbar312";
//const char* mqtt_server = "192.168.0.19";

//WiFiClient espClient;
//PubSubClient client(espClient);

float co2 = 0;
char co2Str[20];
float tvoc = 0;

void setup() {
  Wire.setClockStretchLimit(460);
  pinMode(2, OUTPUT);
  Serial.begin(9600);
  
  Serial.println("CCS811 test");
  
  if(!ccs.begin()){ 
    Serial.println("Failed to start sensor! Please check your wiring.");
    Serial.println(ccs.checkError());
    while(1);
  }

  //calibrate temperature sensor
  while(!ccs.available());
  float temp = ccs.calculateTemperature();
  ccs.setTempOffset(temp - 25.0);

  //setup_wifi();
  //client.setServer(mqtt_server, 1883);
}

void loop() {
  if(ccs.available()){
    //float temp = ccs.calculateTemperature();
    if(!ccs.readData()){
      co2 = ccs.geteCO2();
      tvoc = ccs.getTVOC();
      Serial.print("CO2: ");
      Serial.print(co2);
      Serial.print("ppm, TVOC: ");
      Serial.print(tvoc);
      Serial.print("ppb, [");
      Serial.print((int)millis() / 1000);
      Serial.println(" s]");
      //Serial.println(temp);

      //sendCO2();
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
  delay(2000);
}

//void setup_wifi() {
//
//  delay(10);
//  // We start by connecting to a WiFi network
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//
//  WiFi.begin(ssid, password);
//
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//}
//
//void sendCO2() {
//  // Loop until we're reconnected
//  while (!client.connected()) {
//    Serial.print("Attempting MQTT connection...");
//    // Attempt to connect
//    if (client.connect("co2-sensor-1", "voislav", "Konfiskacija312")) {
//      Serial.println("connected");
//    } else {
//      Serial.print("failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 5 seconds");
//      // Wait 5 seconds before retrying
//      delay(5000);
//    }
//  }
//
//  digitalWrite(2, LOW);
//  delay(50);
//  digitalWrite(2, HIGH);
//
//  // Once connected, publish an announcement...
//  snprintf(co2Str, sizeof(co2Str), "%f", co2);
//  client.publish("living-room/co2", co2Str);
//}
