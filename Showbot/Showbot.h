#ifndef SHOWBOT
#define SHOWBOT

#include <Arduino.h>
#include <MeAuriga.h>
#include <MePort.h>
#include <SoftwareSerial.h>

#define DIRECTION_TOUT_DROIT      1
#define DIRECTION_MARCHE_ARRIERE  2
#define DIRECTION_GAUCHE          3
#define DIRECTION_DROITE          4

#define VITESSE_CONSTANTE         120
#define SEUIL_MICROPHONE          100

MeEncoderOnBoard moteurGauche(SLOT1);
MeEncoderOnBoard moteurDroite(SLOT2);
MeRGBLed leds(0, 12);
MeBuzzer buzzer;
MeUltrasonicSensor capteurUltrasons(10);
MeSoundSensor microphone(14);

int direction;
float vitesse;

void _loop() {
  moteurGauche.loop();
  moteurDroite.loop();
}

void _delay(float seconds) {
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

void initialisation() {
  leds.setpin(44);
  buzzer.setpin(45);
  moteurGauche.reset(SLOT1);
  moteurDroite.reset(SLOT2);
  
  //Set PWM 8KHz
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
}

int recuperer_distance_obstacle() {
  return capteurUltrasons.distanceCm();
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

  moteurGauche.setTarPWM(leftSpeed);
  moteurDroite.setTarPWM(rightSpeed);
}

void avancer() {
  direction = DIRECTION_TOUT_DROIT;
  vitesse = VITESSE_CONSTANTE;
  executer_les_actions();
}

void tourner_a_gauche() {
  direction = DIRECTION_GAUCHE;
  vitesse = VITESSE_CONSTANTE;
  executer_les_actions();
}

void tourner_a_droite() {
  direction = DIRECTION_DROITE;
  vitesse = VITESSE_CONSTANTE;
  executer_les_actions();
}

void reculer() {
  direction = DIRECTION_MARCHE_ARRIERE;
  vitesse = VITESSE_CONSTANTE;
  executer_les_actions();
}

void s_arreter() {
  vitesse = 0;
  executer_les_actions();
}

void bouger() {
  tourner_a_gauche();
  _delay(4);
  tourner_a_droite();
  _delay(4);
  s_arreter();
  _delay(1);
}

void eteindre_leds() {
  leds.setColor(0,0,0,0);
  leds.show();
}

void lancer_compte_a_rebours() {
  int indexLed = 1;
  for(indexLed = 1 ; indexLed < 13 ; indexLed++) {
    leds.setColor(indexLed,255,255,255);
    leds.show();
    _delay(1);
    leds.setColor(indexLed,0,0,0);
  }
  leds.show();
}

void afficher_niveau_sonore() {
  int nombreLedsAAllumer = ((microphone.strength() - 100) * 12 / 500) + 1;
  int indexLed = 1;
  for(indexLed = 1 ; indexLed < nombreLedsAAllumer ; indexLed++) {
    leds.setColor(indexLed,255,255,255);
  }
  for(indexLed = nombreLedsAAllumer ; indexLed < 13 ; indexLed++) {
    leds.setColor(indexLed,0,0,0);
  }
  leds.show();
}

int recuperer_niveau_sonore() {
  return microphone.strength() - 100;
}

void jouer_totoro() {
  buzzer.tone(523, 375);
  buzzer.tone(623, 375);
  buzzer.tone(699, 750);
  buzzer.tone(699, 375);
  buzzer.tone(784, 375);
  buzzer.tone(623, 750);
  buzzer.tone(523, 375);
  buzzer.tone(623, 375);
  buzzer.tone(699, 750);
  buzzer.tone(699, 375);
  buzzer.tone(932, 375);
  buzzer.tone(784, 750);
  buzzer.tone(784, 375);
  buzzer.tone(932, 375);
  buzzer.tone(1046, 375);
  buzzer.tone(1046, 375);
  buzzer.tone(1046, 375);
  buzzer.tone(1246, 375);
  buzzer.tone(1176, 375);
  buzzer.tone(1046, 375);
  buzzer.tone(932, 375);
  buzzer.tone(830, 375);
  buzzer.tone(784, 750);
  buzzer.tone(699, 375);
  buzzer.tone(523, 375);
  buzzer.tone(784, 750);
}

#endif