#define INCOMING 7
#define ADDR 0x5B
#define WAKE_PIN  4

void setup() {
  // put your setup code here, to run once:
  pinMode(INCOMING, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Value is:");
  Serial.println(digitalRead(INCOMING));
  delay(1000);
}
