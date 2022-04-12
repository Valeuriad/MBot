#include "VallE.h"

void setup() {
  initialisation();
}

void loop() {
  
  int couleur_de_la_ligne = recuperer_couleur_de_la_ligne();
  int distance = recuperer_distance_obstacle();

  switch(couleur_de_la_ligne) {
    case GAUCHE_BLANC_DROIT_BLANC:
      avancer();
      break;
    case GAUCHE_NOIR_DROIT_BLANC:
      tourner_a_droite();
      break;
  	case GAUCHE_BLANC_DROIT_NOIR:
      tourner_a_gauche();
      break;
  	case GAUCHE_NOIR_DROIT_NOIR:
      reculer();
      break;
  }

  if(distance < DISTANCE_OBSTACLE_AVANT_COLLISION){
    s_arreter();
    klaxonner();
  }
        
  executer_les_actions();
}
