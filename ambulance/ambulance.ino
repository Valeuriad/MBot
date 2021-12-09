#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);
MeRGBLed rgbled_7(7, 2);
MeBuzzer buzzer;

void move(int direction, int speed) {
  int leftSpeed = 0;
  int rightSpeed = 0;
  if(direction == 1) {
    leftSpeed = speed;
    rightSpeed = speed;
  } else if(direction == 2) {
    leftSpeed = -speed;
    rightSpeed = -speed;
  } else if(direction == 3) {
    leftSpeed = -speed;
    rightSpeed = speed;
  } else if(direction == 4) {
    leftSpeed = speed;
    rightSpeed = -speed;
  }
  motor_9.run((9) == M1 ? -(leftSpeed) : (leftSpeed));
  motor_10.run((10) == M1 ? -(rightSpeed) : (rightSpeed));
}

void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void setup() {
  pinMode(A7, INPUT);
  rgbled_7.fillPixelsBak(0, 2, 1);
  while(!((0 ^ (analogRead(A7) > 10 ? 0 : 1))))
  {
    _loop();
  }

  move(1, 80 / 100.0 * 255);
  for(int count=0;count<5;count++){

    rgbled_7.setColor(0, 0, 0, 0);
    rgbled_7.show();

    rgbled_7.setColor(2, 0, 0, 60);
    rgbled_7.show();

    buzzer.tone(950, 0.6 * 1000);

    rgbled_7.setColor(0, 0, 0, 0);
    rgbled_7.show();

    rgbled_7.setColor(1, 0, 0, 60);
    rgbled_7.show();

    buzzer.tone(700, 0.4 * 1000);
  }
  motor_9.run(0);
  motor_10.run(0);

}

void _loop() {
}

void loop() {
  _loop();
}
