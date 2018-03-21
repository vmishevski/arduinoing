#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/************************* WiFi Access Point *********************************/
#define WLAN_SSID       "Mishevski Doma"
#define WLAN_PASS       "Bumbar312"

/************************* Adafruit.io Setup *********************************/
#define SERVER      "192.168.0.14"
#define SERVERPORT  1883
#define LED 2

char temperatureMsg[50];

WiFiClient espClient;

PubSubClient client(espClient);


void setup() {
  Serial.begin(9600);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  client.setServer(SERVER, SERVERPORT);
  client.setCallback(messageCallback);
}

void loop() {
  if (!client.connected()) {
    mqttReConnect();
  }

  if (client.connected()) {
    delay(5000);
    client.publish("home/living-room/temperature", "10");
    Serial.println("message sent");
    blinkLed();
  }

  client.loop();
  
}

void messageCallback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Received msg:");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  blinkLed();
}

void mqttReConnect() {
  byte retries = 5;
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("arduino-node-1")) {
      Serial.println("Connected");
      blinkLed();
    } else {
      Serial.println("Connection failed");
      retries--;
      if (retries <= 0) {
        break;
      }
    }
    delay(1000);
  }
}

void blinkLed() {
  byte times = 1;
  while (times > 0) {
    digitalWrite(LED, LOW);
    delay(50);
    digitalWrite(LED, HIGH);
    delay(50);
    times--;
  }
}

