
#include <PulseSensorPlayground.h>

//PulseSensorPlayground pulse;

unsigned long thisTime;
unsigned long thatTime;

void setup() {
  Serial.begin(250000);
  delay(100);
  Serial.println("Pulse Sensor Playground Test");
  delay(100);
  thatTime = micros();
  pulse.begin();


}

void loop() {

  if(pulse.testBool == true){
    thisTime = micros();
    Serial.println(thisTime - thatTime);
    thatTime = thisTime;
    
    pulse.testBool = false;
    
  }

}
