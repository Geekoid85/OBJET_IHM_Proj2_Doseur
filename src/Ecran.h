#ifndef ECRAN_H
#define ECRAN_H
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

class Ecran {
private:
    int niveauBatterie;
    int dosage; // 0.25uL = 250nL
    bool modeContinue;
    String unit = "µL";
    U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C* u8g2;
    void actualiser();

public:
    Ecran(int SDA, int SCL);
    void incrementation(); // 0.05uL = 50nL
    void decrementation();
    void changerMode();
    void actualiserBatterie(int niveauBatterie);
};

#endif