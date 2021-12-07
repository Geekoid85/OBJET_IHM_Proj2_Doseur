#include "Batterie.h"
int nouveauNiveauBatterie = 74;
int getNiveauBatterie() { // Je défini ma fonction
    if (Serial.available() > 1) { // >1 et pas l'habituel >0 car sinon lors de la prochaine boucle il met 0 dans "niveauBatterie"
        nouveauNiveauBatterie = Serial.parseInt(); // Et pas Serial.read qui renverrait le numéro du caractère ascii
        Serial.print("niveau de batterie: ");
        Serial.print(nouveauNiveauBatterie);
        Serial.println(" %");
    }
    return nouveauNiveauBatterie;
}