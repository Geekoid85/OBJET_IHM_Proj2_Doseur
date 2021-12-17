#include "Moteur.h"
int nombreImpulsion = 0; //déclaration variable nombre impulsion
float distanceRetrait = 0.25; // distance de retrait en mm

void goDoserVolume(float volume) {
    //TODO Code d'aurélien doser volume
    Serial.print("Dosage d'un volume de: ");
    Serial.print(volume);
    Serial.println(" µL");
    nombreImpulsion = 0;//remise a zéro
    int nombreImpulsionDosage = (volume * 58.8 * 986 * 14) / (201 * 2 * 3.14 * 8); // Pour un volume max de 0.56uL
    int nombreImpulsionRetrait = (distanceRetrait * 58.8 * 986 * 14) / (2 * 3.14 * 8);//déclaration nombre impulsion retrait
    attachInterrupt(digitalPinToInterrupt(BROCHE_CODEUR_A), impulsionRoueCodeuse, RISING); //Détection impulsion sur roue codeuse donc ajouté 1
    while (nombreImpulsion < nombreImpulsionDosage) {//Tant que nombre d'impulsion insuffisant continuer
        Serial.println(nombreImpulsion);
        digitalWrite(BROCHE_DIR, LOW);//Moteur tourne sens horaire
        analogWrite(BROCHE_PWM, 60);//moteur tourne vitesse de 60
    }
    analogWrite(BROCHE_PWM, 0);//moteur stop
    Serial.println(nombreImpulsion);
    nombreImpulsion = 0;//remise a zéro
    Serial.println(nombreImpulsion);
    delay(2500);
    while (nombreImpulsion < nombreImpulsionRetrait) {//Tant que nombre d'impulsion insuffisant continuer
        Serial.println(nombreImpulsion);
        digitalWrite(BROCHE_DIR, HIGH);//Moteur tourne sens trigo
        analogWrite(BROCHE_PWM, 255);//moteur tourne vitesse max
    }
    analogWrite(BROCHE_PWM, 0);//moteur stop
    Serial.println(nombreImpulsion);
    nombreImpulsion = 0;//remise a zéro

}

void goDoserDebit(float debit, int BROCHE_BOUTON_DOSER) {
    //TODO Code d'aurélien doser débit
    // Tant que le bouton n'a pas été relaché
    Serial.print("Dosage continue avec un debit de: ");
    Serial.print(debit);
    Serial.println(" µL/s");
    digitalWrite(BROCHE_DIR, LOW);//Moteur tourne sens horaire
    analogWrite(BROCHE_PWM, 200);
    while (digitalRead(BROCHE_BOUTON_DOSER) == LOW) {
    }
    analogWrite(BROCHE_PWM, 0);
}

void impulsionRoueCodeuse() {
    nombreImpulsion++; // ajouter 1 au nombre d'impulsion
}