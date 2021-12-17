#ifndef ECRAN_H
#define ECRAN_H
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

class Ecran {
#define RESOLUTION_DOSAGE 50 // Résolutions du dosage 0.05µL
#define COEF_K 1 // Coefficient de correction du dosage
#define DEBIT_MAX 750 // Débit maximum en mode continue 0.75µL/s soit F=80N pour une pâte neuve
#define LOGO_GOUTTE_TAILLE_X 128
#define LOGO_GOUTTE_TAILLE_Y 32

private:
    U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C* u8g2;
    int niveauBatterie;
    int dosage; // 0.25µL = 250nL
    int resolutionDosage;
    bool modeContinue;
    String unit;
    void actualiser();

public:
    enum TypeErreur {
        MIN,
        MAX,
        SUR_INTENSITE
    };
    Ecran();
    void incrementation(); // 0.05uL = 50nL
    void decrementation();
    void changerMode();
    void actualiserBatterie(int niveauBatterie);
    void erreur(TypeErreur typeErreur);
    void doserVolume();
    void doserDebit(int BROCHE_BOUTON_DOSER);
    bool getModeContinue();
};

#endif