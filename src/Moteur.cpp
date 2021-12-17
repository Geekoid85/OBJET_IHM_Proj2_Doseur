#include "Moteur.h"

void goDoserVolume(float volume) {
    //TODO Code d'aurélien doser volume
    Serial.print("Dosage d'un volume de: ");
    Serial.print(volume);
    Serial.println(" µL");

    int nombreImpulsion = 0;//déclaration variable nombre impulsion
    int nombreImpulsionDosage = 500; // Pour un volume max de 0.56uL
    long nombreImpulsionRetrait = 2000;//déclaration nombre impulsion retrait

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
    nombreImpulsion = 0;//remise a zé 

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