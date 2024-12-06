#ifndef ULTRASON_H
#define ULTRASON_H

// Définition des pins
extern const int trigPin;
extern const int echoPin;
extern const int buttonPin;  // Nouveau : bouton pour activer/désactiver

// Déclaration des variables
extern long duration;
extern int distance;
extern bool mesureActive;  // Nouveau : état pour activer/désactiver le capteur

// Déclaration des fonctions
void initUltrason();
int lireDistance();
void gererBouton();  // Nouveau : gestion du bouton avec debounce

#endif
