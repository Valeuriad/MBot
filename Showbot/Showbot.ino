#include "Showbot.h"

void setup() {
  initialisation();
  eteindre_leds();
}

void loop() {
  if(recuperer_distance_obstacle() < 5) {
    lancer_compte_a_rebours();
    bouger();
  }
  if(recuperer_niveau_sonore() > 450) {
    eteindre_leds();
    jouer_totoro();
  }
  afficher_niveau_sonore();
}
