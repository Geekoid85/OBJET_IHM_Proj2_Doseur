#include <Arduino.h>
#include "Ecran.h"
#include "Batterie.h"
Ecran* monEcran; // Broche de l'écranEcran ecran(13, 12); // Broche de l'écran

#define BROCHE_BOUTON_DOSER  4
#define BROCHE_BOUTON_PLUS 5
#define BROCHE_BOUTON_MOINS 6
#define BROCHE_BUZZER 3
#define BROCHE_LED 11

#define ANTI_REBOND 250
#define DUREE_BIP 50
#define FREQUENCE_BIP_DOSER 1760 // Fréquence en Hertz
#define FREQUENCE_BIP_GENERAL 880

void setup() {
  Serial.begin(9600);
  pinMode(BROCHE_BOUTON_DOSER, INPUT_PULLUP); // Déclarer les broches des boutons comme entrée et utilise la résistance de rappel positif.
  pinMode(BROCHE_BOUTON_PLUS, INPUT_PULLUP);
  pinMode(BROCHE_BOUTON_MOINS, INPUT_PULLUP);
  pinMode(BROCHE_BUZZER, OUTPUT);
  pinMode(BROCHE_LED, OUTPUT);

  digitalWrite(BROCHE_LED, HIGH);
  monEcran = new Ecran(); // J'initialise ce pointeur dans le void setup
}
void loop() {
  if (digitalRead(BROCHE_BOUTON_DOSER) == LOW // Si le bouton Dose est pressé
    && digitalRead(BROCHE_BOUTON_PLUS) == HIGH
    && digitalRead(BROCHE_BOUTON_MOINS) == HIGH) {
    if (monEcran->getModeContinue() == 0) { // Si le doseur est en mode Impulsion
      tone(BROCHE_BUZZER, FREQUENCE_BIP_DOSER);
      delay(DUREE_BIP);
      noTone(BROCHE_BUZZER);
      monEcran->doserVolume();
    } else { // Si le doseur est en mode Continue
      tone(BROCHE_BUZZER, FREQUENCE_BIP_DOSER);
      delay(DUREE_BIP);
      noTone(BROCHE_BUZZER);
      monEcran->doserDebit();
    }
    delay(ANTI_REBOND);

  } else if (digitalRead(BROCHE_BOUTON_DOSER) == HIGH // Si le bouton Plus et le bouton Moins sont pressé simultanément
    && digitalRead(BROCHE_BOUTON_PLUS) == LOW
    && digitalRead(BROCHE_BOUTON_MOINS) == LOW) {
    tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
    monEcran->changerMode();
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND);

  } else if (digitalRead(BROCHE_BOUTON_DOSER) == HIGH // Si le bouton Plus est pressé
    && digitalRead(BROCHE_BOUTON_PLUS) == LOW
    && digitalRead(BROCHE_BOUTON_MOINS) == HIGH) {
    tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
    monEcran->incrementation();
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND);

  } else if (digitalRead(BROCHE_BOUTON_DOSER) == HIGH // Si le bouton Moins est presssé
    && digitalRead(BROCHE_BOUTON_PLUS) == HIGH
    && digitalRead(BROCHE_BOUTON_MOINS) == LOW) {
    tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
    monEcran->decrementation();
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND);

  } else { // Si d'autres combinaisons sont pressés par mégard //TODO BUGGGGG NON !!!
    /*tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
    monEcran->erreur(monEcran->BOUTON);
    noTone(BROCHE_BUZZER);
    delay(ANTI_REBOND); */
  }
  monEcran->actualiserBatterie(getNiveauBatterie());
}