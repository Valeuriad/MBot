#ifndef WALLE
#define WALLE

#include <Arduino.h>
#include <MeAuriga.h>
#include <MePort.h>
#include <SoftwareSerial.h>

#define GAUCHE_NOIR_DROIT_NOIR    0
#define GAUCHE_NOIR_DROIT_BLANC   1
#define GAUCHE_BLANC_DROIT_NOIR   2
#define GAUCHE_BLANC_DROIT_BLANC  3

#define DIRECTION_TOUT_DROIT      1
#define DIRECTION_MARCHE_ARRIERE  2
#define DIRECTION_GAUCHE          3
#define DIRECTION_DROITE          4

#define DISTANCE_OBSTACLE_AVANT_COLLISION   50

MeEncoderOnBoard capteurGauche(SLOT1);
MeEncoderOnBoard capteurDroit(SLOT2);
MeLineFollower capteurLigne(9);
MeUltrasonicSensor capteurObstacle(10);
MeBuzzer buzzer;

int direction;
float vitesse;

void initialisation() {
  Serial.begin(115200);
  capteurGauche.reset(SLOT1);
  capteurDroit.reset(SLOT2);
  buzzer.setpin(45);

  //Set PWM 8KHz
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}

void debug(String message) {
  Serial.print(message);
  Serial.print("\n");
}

int recuperer_couleur_de_la_ligne() {
  return capteurLigne.readSensors();
}

int recuperer_distance_obstacle() {
  return capteurObstacle.distanceCm();
}

void avancer() {
  direction = DIRECTION_TOUT_DROIT;
  vitesse = 150;
}

void tourner_a_gauche() {
  direction = DIRECTION_GAUCHE;
  vitesse = 120;
}

void tourner_a_droite() {
  direction = DIRECTION_DROITE;
  vitesse = 120;
}

void reculer() {
  direction = DIRECTION_MARCHE_ARRIERE;
  vitesse = 150;
}

void s_arreter() {
  vitesse = 0;
}

void klaxonner() {
  buzzer.tone(500, 1000);
}

void executer_les_actions() {
  int leftSpeed = 0;
  int rightSpeed = 0;

  if (direction == DIRECTION_TOUT_DROIT) {
    leftSpeed = -vitesse;
    rightSpeed = vitesse;

  } else if (direction == DIRECTION_MARCHE_ARRIERE) {
    leftSpeed = vitesse;
    rightSpeed = -vitesse;

  } else if (direction == DIRECTION_GAUCHE) {
    leftSpeed = -vitesse;
    rightSpeed = -vitesse;

  } else if (direction == DIRECTION_DROITE) {
    leftSpeed = vitesse;
    rightSpeed = vitesse;
  }

  capteurGauche.setTarPWM(leftSpeed);
  capteurDroit.setTarPWM(rightSpeed);

  capteurGauche.loop();
  capteurDroit.loop();
}

#endif
