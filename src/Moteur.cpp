#include "Moteur.h"

void goDoserVolume(float volume) {
    //TODO Code d'aurélien doser volume
    Serial.print("Dosage d'un volume de: ");
    Serial.print(volume);
    Serial.println(" µL");
}

void goDoserDebit(float debit, int BROCHE_BOUTON_DOSER) {
    //TODO Code d'aurélien doser débit
    // Tant que le bouton n'a pas été relaché
    Serial.print("Dosage continue avec un debit de: ");
    Serial.print(debit);
    Serial.println(" µL/s");
    while (digitalRead(BROCHE_BOUTON_DOSER) == LOW) {
    }
}