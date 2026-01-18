#include <basicTickESP.h>

void setup() {
  Serial.begin(115200);
  basicTick_init();
}

void loop() {
  Serial.println(basicTick_get());
  delay(1000);
}
