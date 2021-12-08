#ifndef MOTEUR_H
#define MOTEUR_H
#include <Arduino.h>

#define BROCHE_DIR 8
#define BROCHE_PWM 9
#define BROCHE_CODEUR_A 2

void goDoserVolume(float volume);
void goDoserDebit(float debit, int BROCHE_BOUTON_DOSER);

#endif