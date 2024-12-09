#ifndef SENSOR_H
#define SENSOR_H

// Définition des pins
extern const int trig_pin;
extern const int echo_pin;
extern const int button_pin;  // Nouveau : bouton pour activer/désactiver

// Déclaration des variables
extern long duration;
extern int distance;
extern bool mesureActive;  // Nouveau : état pour activer/désactiver le capteur

// Déclaration des fonctions
void initUltrason();
int lireDistance();
void gererBouton();  // Nouveau : gestion du bouton avec debounce

#endif
