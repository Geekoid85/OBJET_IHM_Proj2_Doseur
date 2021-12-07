#include <Arduino.h>
#include "Ecran.h"
#include "Batterie.h"
Ecran* monEcran; // Broche de l'écranEcran ecran(13, 12); // Broche de l'écran

#define BROCHE_BOUTON_DOSER  4
#define BROCHE_BOUTON_PLUS 5
#define BROCHE_BOUTON_MOINS 6
#define BROCHE_BUZZER 3
#define BROCHE_LED 11

#define ANTI_REBOND 10
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
  }

  if (digitalRead(BROCHE_BOUTON_PLUS) == LOW) { // Si le bouton PLUS est pressé
    bool doublePression = 0;
    delay(ANTI_REBOND); // Attendre 10ms pour s'assurer que ce n'est pas un rebond
    if (digitalRead(BROCHE_BOUTON_PLUS) == LOW) { // Si ce n'était pas un rebond et que le bouton PLUS est donc toujours pressé
      while (digitalRead(BROCHE_BOUTON_PLUS) == LOW) { // Tant que le bouton PLUS est pressé
        if (digitalRead(BROCHE_BOUTON_MOINS) == LOW) { // Si jamais le bouton MOINS est pressé
          delay(ANTI_REBOND); // Attendre 10ms pour s'assurer que ce n'est pas un rebond
          if (digitalRead(BROCHE_BOUTON_MOINS) == LOW) { // Si ce n'était pas un rebond et que le bouton MOINS est donc toujours pressé
            while (digitalRead(BROCHE_BOUTON_MOINS) == LOW) {} // Attendre tant que le bouton MOINS est pressé
            tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
            monEcran->changerMode();
            noTone(BROCHE_BUZZER);
            doublePression = 1; // Une double pression a donc été détecté
          }
        }
      }
      if (doublePression == 0) { // Si aucune double pression n'a été détecté
        tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
        monEcran->incrementation();
        noTone(BROCHE_BUZZER);
      } // Sinon, ignorer le relachement du bouton PLUS
    }
  }

  if (digitalRead(BROCHE_BOUTON_MOINS) == LOW) { // Si le bouton MOINS est pressé
    bool doublePression = 0;
    delay(ANTI_REBOND); // Attendre 10ms pour s'assurer que ce n'est pas un rebond
    if (digitalRead(BROCHE_BOUTON_MOINS) == LOW) { // Si ce n'était pas un rebond et que le bouton MOINS est donc toujours pressé
      while (digitalRead(BROCHE_BOUTON_MOINS) == LOW) { // Tant que le bouton MOINS est pressé
        if (digitalRead(BROCHE_BOUTON_PLUS) == LOW) { // Si jamais le bouton PLUS est pressé
          delay(ANTI_REBOND); // Attendre 10ms pour s'assurer que ce n'est pas un rebond
          if (digitalRead(BROCHE_BOUTON_PLUS) == LOW) { // Si ce n'était pas un rebond et que le bouton PLUS est donc toujours pressé
            while (digitalRead(BROCHE_BOUTON_PLUS) == LOW) {} // Attendre tant que le bouton PLUS est pressé
            tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
            monEcran->changerMode();
            noTone(BROCHE_BUZZER);
            doublePression = 1; // Une double pression a donc été détecté
          }
        }
      }
      if (doublePression == 0) { // Si aucune double pression n'a été détecté
        tone(BROCHE_BUZZER, FREQUENCE_BIP_GENERAL);
        monEcran->decrementation();
        noTone(BROCHE_BUZZER);
      } // Sinon, ignorer le relachement du bouton MOINS
    }
  }
  monEcran->actualiserBatterie(getNiveauBatterie());
}