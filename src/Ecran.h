#ifndef ECRAN_H
#define ECRAN_H
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

class Ecran {
#define RESOLUTION_DOSAGE 50 // Résolutions du dosage 0.05µL
#define COEF_K 1 // Coefficient de correction du dosage
private:
    int niveauBatterie;
    int dosage; // 0.25µL = 250nL
    int resolutionDosage;
    bool modeContinue;
    String unit;
    U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C* u8g2; // Créer un pointeur dans l'espace mémoire
    void actualiser();

public:
    Ecran(int SDA, int SCL);
    void incrementation(); // 0.05uL = 50nL
    void decrementation();
    void changerMode();
    void actualiserBatterie(int niveauBatterie);
    void erreur();
    void doserVolume();
    void doserDebit();
    bool getModeContinue();
};

#endif