#define TMP_PIN 0

int tmp;

void setup() {
  // put your setup code here, to run once:
  pinMode(TMP_PIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  tmp = (((analogRead(TMP_PIN) * 5.0) / 1024.0) - 0.5) * 100;

  Serial.print("Temperature is: ");
  Serial.println(tmp);
  
}
