#define INT_LED 4

void setup() {
  // put your setup code here, to run once:
  pinMode(INT_LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  digitalWrite(INT_LED, HIGH);

  delay(1000);

  digitalWrite(INT_LED, LOW);

  delay(1000);

  Serial.println("Hi from wemos d1");
  
}
