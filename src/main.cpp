#include <Arduino.h>
#include "Ecran.h"
#include "Batterie.h"
Ecran ecran(13, 12); // Broche de l'écran

#define BROCHE_DOSE  4
#define BROCHE_PLUS 5
#define BROCHE_MOINS 6
#define BROCHE_BUZZER 3
#define BROCHE_LED 11
#define ANTI_REBOND 250

void setup() {
  pinMode(BROCHE_DOSE, INPUT_PULLUP); // Déclarer les broches des boutons comme entrée et utilise la résistance de rappel positif.
  pinMode(BROCHE_PLUS, INPUT_PULLUP);
  pinMode(BROCHE_MOINS, INPUT_PULLUP);
  pinMode(BROCHE_BUZZER, OUTPUT);
  pinMode(BROCHE_LED, OUTPUT);

  digitalWrite(BROCHE_LED, HIGH);
}

void loop() {
  if (digitalRead(BROCHE_DOSE) == LOW // Si le bouton Dose est pressé
    && digitalRead(BROCHE_PLUS) == HIGH
    && digitalRead(BROCHE_MOINS == HIGH)) {
    tone(BROCHE_BUZZER, 1760);
    // Fonction pour déposer une dose avec une boucle while qui empêche d'appuyer sur le bouton tant que la distribution n'est pas fini
    //TODO Intéruption sur le front montant
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND);

  } else if (digitalRead(BROCHE_DOSE) == HIGH // Si le bouton Plus est pressé
    && digitalRead(BROCHE_PLUS) == LOW
    && digitalRead(BROCHE_MOINS) == HIGH) {
    tone(BROCHE_BUZZER, 1760);
    ecran.incrementation();
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND);

  } else if (digitalRead(BROCHE_DOSE) == HIGH // Si le bouton Moins est presssé
    && digitalRead(BROCHE_PLUS) == HIGH
    && digitalRead(BROCHE_MOINS) == LOW) {
    tone(BROCHE_BUZZER, 1760);
    ecran.decrementation();
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND);

  } else if (digitalRead(BROCHE_DOSE) == HIGH // Si le bouton Plus et le bouton Moins sont pressé simultanément
    && digitalRead(BROCHE_PLUS) == LOW
    && digitalRead(BROCHE_MOINS) == LOW) {
    tone(BROCHE_BUZZER, 1760);
    ecran.changerMode();
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND);
  } else { // Si d'autres combinaisons sont pressés par mégard
    ecran.erreur();
  }
  ecran.actualiserBatterie(getNiveauBatterie());
}