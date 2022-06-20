#include "VallE.h"

void setup() {
  initialisation();
}

void loop() {

  int couleur_de_la_ligne = recuperer_couleur_de_la_ligne();
  int distance = recuperer_distance_obstacle();

  if (couleur_de_la_ligne == GAUCHE_BLANC_DROIT_BLANC) {
    avancer();

  } else if (couleur_de_la_ligne == GAUCHE_NOIR_DROIT_NOIR) {
    reculer();

  } else if (couleur_de_la_ligne == GAUCHE_NOIR_DROIT_BLANC) {
    tourner_a_droite();

  } else if (couleur_de_la_ligne == GAUCHE_BLANC_DROIT_NOIR) {
    tourner_a_gauche();
  }

  if(distance < DISTANCE_OBSTACLE_AVANT_COLLISION) {
    s_arreter();
    klaxonner();
  }

  executer_les_actions();
}
