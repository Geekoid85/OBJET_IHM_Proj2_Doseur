#include <Arduino.h>
#include "Ecran.h"
#include <U8g2lib.h>
#include <Wire.h>


Ecran::Ecran(int SDA, int SCL) {
    // Intialiser mon écran (font, color...)
    this->u8g2 = new U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C(/* rotation=*/ U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
    u8g2->begin();
    u8g2->setI2CAddress(0x78); // Adresse réelle de l'écran 0x3C fois deux égal 0x78
    u8g2->enableUTF8Print(); // Autoriser l'utilisation de caractères spéciaux
    u8g2->setFont(u8g2_font_timB24_tf);
    u8g2->setDrawColor(1);
    //inialisation des pointeurs
    this->niveauBatterie = 50; // dans le futur = getPourcentage
    this->dosage = 250;
    this->modeContinue = 0;
}

void Ecran::actualiser() {
    // Affichage du dosage
    if (this->modeContinue == 0) {
        this->unit = "µL";
    } else {
        this->unit = "µL/s";
    }
    u8g2->firstPage(); do { // Les éventuels variables présentes dans cette boucle ne doivent pas changer pendant l'execution de la boucle
        u8g2->setCursor(30, 28); // L'origine d'une lettre c'est en bas à gauche
        u8g2->print(this->dosage * 1000 + unit);
        // Affichage du niveau de batterie
        u8g2->drawFrame(0, 5, 18, 27); // Contour Origine X=32-26 Y, Dimension XY
        u8g2->drawBox(6, 2, 6, 3); // Bosse
        if (this->niveauBatterie >= 0 && this->niveauBatterie <= 25) {
            u8g2->drawBox(2, 25, 14, 5); // [0;25]%
        }
        if (this->niveauBatterie < 25 && this->niveauBatterie >= 50) {
            u8g2->drawBox(2, 19, 14, 5); // ]25;50]%
        }
        if (this->niveauBatterie < 50 && this->niveauBatterie >= 75) {
            u8g2->drawBox(2, 13, 14, 5); // ]50;75]%
        }
        if (this->niveauBatterie < 75 && this->niveauBatterie >= 100) {
            u8g2->drawBox(2, 7, 14, 5); // ]75;100]%
        }
    } while (u8g2->nextPage()); // Afficher page par page le contenu jusqu'à sortir de la boucle
}

void Ecran::incrementation() {
    dosage += 50; // revient à dosage = dosage + 50
    this->actualiser();
}
void Ecran::decrementation() {
    dosage -= 50;
    this->actualiser();
}

void Ecran::changerMode() {
    modeContinue = !modeContinue;
}

void Ecran::actualiserBatterie(int niveauBatterie) {
    if (niveauBatterie != this->niveauBatterie) { // Si le niveau de batterie à changer
        this->niveauBatterie = niveauBatterie;
        this->actualiser();
    }
}