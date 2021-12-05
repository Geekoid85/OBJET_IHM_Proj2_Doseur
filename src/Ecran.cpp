#include <Arduino.h>
#include "Ecran.h"
#include "Moteur.h"

Ecran::Ecran() {
    this->u8g2 = new U8G2_SSD1306_128X32_UNIVISION_1_HW_I2C(/* rotation=*/ U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
    // Intialiser mon écran (font, color...)
    u8g2->begin();
    u8g2->setI2CAddress(0x78); // Adresse réelle de l'écran 0x3C fois deux égal 0x78
    u8g2->enableUTF8Print(); // Autoriser l'utilisation de caractères spéciaux
    u8g2->setFont(u8g2_font_timB18_tf);
    u8g2->setDrawColor(1);
    //inialisation des pointeurs
    this->niveauBatterie = 50; // dans le futur = getPourcentage
    this->dosage = 250;
    this->resolutionDosage = 50; // résolution du dosage 0.05µL
    this->modeContinue = 0;
    Serial.println("ok");
}

void Ecran::actualiser() {
    // Affichage du dosage
    if (this->modeContinue == 0) {
        this->unit = "µL";
    } else {
        this->unit = "µL/s";
    }
    u8g2->firstPage();
    do { // Les éventuels variables présentes dans cette boucle ne doivent pas changer pendant l'execution de la boucle
        u8g2->setCursor(30, 28); // L'origine d'une lettre c'est en bas à gauche
        u8g2->print(((float)this->dosage / 1000) * COEF_K + unit);
        // Affichage du niveau de batterie
        u8g2->drawFrame(0, 5, 18, 27); // Contour Origine X=32-26 Y, Dimension XY
        u8g2->drawBox(6, 2, 6, 3); // Bosse
        if (this->niveauBatterie >= 0) {
            u8g2->drawBox(2, 25, 14, 5); // [0;25]%
        }
        if (this->niveauBatterie >= 25) {
            u8g2->drawBox(2, 19, 14, 5); // ]25;50]%
        }
        if (this->niveauBatterie >= 50) {
            u8g2->drawBox(2, 13, 14, 5); // ]50;75]%
        }
        if (this->niveauBatterie >= 75) {
            u8g2->drawBox(2, 7, 14, 5); // ]75;100]%
        }
    } while (u8g2->nextPage()); // Afficher page par page le contenu jusqu'à sortir de la boucle
}

void Ecran::incrementation() {
    if (this->modeContinue == 1 // Si le doseur est en mode continue et que l'utilisateur essai de dépasser le débit maximum
        && dosage > DEBIT_MAX) {
        this->erreur(MAX);
    } else {
        dosage += RESOLUTION_DOSAGE; // revient à dosage = dosage + RESOLUTION_DOSAGE
    }
    this->actualiser();
}
void Ecran::decrementation() {
    if (dosage > RESOLUTION_DOSAGE) {
        dosage -= RESOLUTION_DOSAGE;
        this->actualiser();
    } else {
        this->erreur(MIN);
    }
}

void Ecran::changerMode() {
    if (this->modeContinue == 0 // Si le doseur était en mode Impulsion et que le volume était supérieur au débit maximum
        && dosage > DEBIT_MAX) {
        dosage = DEBIT_MAX; // Définir un débit par défault comme étant le débit maximum
        this->erreur(MAX);
    }
    modeContinue = !modeContinue;
}

void Ecran::actualiserBatterie(int niveauBatterie) {
    if (niveauBatterie != this->niveauBatterie) { // Si le niveau de batterie à changer
        this->niveauBatterie = niveauBatterie;
        this->actualiser();
    }
}

void Ecran::erreur(TypeErreur typeErreur) {
    u8g2->firstPage(); do {
        switch (typeErreur) {
        case MIN:
            // TODO Afficher "MIN" en gras et en grand
            break;
        case MAX:
            // TODO Afficher "MAX" en gras et en grand
            break;
        case BOUTON:
            // TODO Afficher une croix
            break;
        case BATTERIE_FAIBLE:
            break;
            // TODO Afficher une batterie vide avec une croix par dessus
        case SUR_INTENSITE:
            // TODO Indiquer que le piston est probablement en buté ou que la pâte est trop vieille
            break;
        }
    } while (u8g2->nextPage());
    delay(750); // Afficher l'icone d'erreur et donc buzzer pendant 0.75 seconde avant de réafficher l'interface
    this->actualiser();
}

void Ecran::doserVolume() {

    u8g2->firstPage(); do {
        //TODO Dessiner un icone dosage par impulsion (une goutte ?)
        u8g2->setCursor(30, 28);
        u8g2->print("vol");
    } while (u8g2->nextPage());
    goDoserVolume(); // Fonction doserVolume dans Moteur.cpp
    delay(500);
    this->actualiser();
}

void Ecran::doserDebit() {
    u8g2->firstPage(); do {
        //TODO Dessiner un icone dosage continue (un +∞ ?)
        u8g2->setCursor(30, 28);
        u8g2->print("deb");
    } while (u8g2->nextPage());
    goDoserDebit();
    delay(500);
    this->actualiser();
}

bool Ecran::getModeContinue() {
    return this->modeContinue;
}