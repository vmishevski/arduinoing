#define IntPin 5
#define LedPin 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IntPin, OUTPUT);
  pinMode(LedPin, OUTPUT);
  digitalWrite(IntPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Sending interupt");
  digitalWrite(IntPin, HIGH);
  digitalWrite(LedPin, HIGH);
  delay(1000);
  digitalWrite(IntPin, LOW);
  digitalWrite(LedPin, LOW);
  delay(10000);
}
