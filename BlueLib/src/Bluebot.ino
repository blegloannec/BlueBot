
#include "Moteurs.h"
#include "Commande.h"

void setup() {
  //Serial.begin(9600); // Debug USB
  Serial1.begin(9600);
  MOT_init();
  MOT_setR(0);
}

void loop() {
  CMD_recvOrdre();
}
