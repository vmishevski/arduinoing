#include <TMP36.h>

#include <avr/wdt.h>

#define LED_PIN A5

// volatile byte wdtVector = 0;
// int loop_count = 0;
float val = 0;

TMP36 sensor = TMP36(LED_PIN, 5.0);

void setup() {
  Serial.begin(9600);
  //setupWatchdog();
  // digitalWrite(LED_PIN, LOW);
}

void loop() {
  val = sensor.getTempC();
  Serial.print("Current pin value:");
  Serial.println(val);
  delay(2000);
  // digitalWrite(LED_PIN, LOW);
  // delay(1000);
  // for (int i = 0; i <= loop_count;i++){
  //   digitalWrite(13,HIGH);
  //   delay(100);
  //   digitalWrite(13,LOW);
  //   delay(100);
  // }
  // loop_count++;
  // wdt_reset();
  // Serial.print(loop_count);
  // Serial.print(". Watchdog fed in approx. ");
  // Serial.print(loop_count*200);
  // Serial.println(" milliseconds.");
}

void setupWatchdog() {
  cli();
  wdt_reset();

  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = (1<<WDIE) | (1<<WDE) | (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (1<<WDP0);;

  sei();
}

ISR(WDT_vect) {

}
