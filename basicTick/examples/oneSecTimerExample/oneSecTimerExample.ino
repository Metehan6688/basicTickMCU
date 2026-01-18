#include <basicTick.h>

void setup() {
  Serial.begin(9600);
  basicTick_init();
}

void loop() {
  Serial.println(basicTick_get());
  delay(1000);
  //Drift 1ms/5s, hardware problem
}
