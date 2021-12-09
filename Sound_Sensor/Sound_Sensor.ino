// generated by mBlock5 for mBot Ranger
// codes make you happy

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MeAuriga.h>

MeLightSensor lightsensor_12(12);
MeSoundSensor soundsensor_14(14);
MeBuzzer buzzer;

void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void setup() {
  Serial.begin(9600);
  randomSeed((unsigned long)(lightsensor_12.read() * 123456));
  buzzer.setpin(45);
  while(1) {
      Serial.print(soundsensor_14.strength());
      Serial.print("\n");
      if(soundsensor_14.strength() > 500){

        buzzer.tone(262, 0.25 * 1000);
        _delay(0.02);

      }

      _loop();
  }

}

void _loop() {
}

void loop() {
  _loop();
}
