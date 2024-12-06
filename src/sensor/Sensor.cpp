#include "sensor.h"
#include <Arduino.h>

// Définition des pins
const int trigPin = 9;
const int echoPin = 10;
const int buttonPin = 7;  // Nouveau : bouton connecté à la pin 7

// Définition des variables
long duration;
int distance;
bool mesureActive = true;  // Nouveau : état pour activer/désactiver le capteur
unsigned long lastDebounceTime = 0; // Nouveau : temps pour le debounce
const unsigned long debounceDelay = 50; // Nouveau : délai de debounce

void initUltrason() {
  pinMode(trigPin, OUTPUT);   // trigPin comme sortie
  pinMode(echoPin, INPUT);    // echoPin comme entrée
  pinMode(buttonPin, INPUT_PULLUP); // Nouveau : bouton avec résistance pull-up
}

int lireDistance() {
  if (!mesureActive) {
    return -1;  // Retourne -1 si la mesure est désactivée
  }

  // Clear le trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Met le trigPin à HIGH pendant 10 microsecondes
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lire le temps du signal écho
  duration = pulseIn(echoPin, HIGH);

  // Calculer la distance en centimètres
  distance = duration * 0.034 / 2;

  return distance;
}

void gererBouton() {
  static int lastButtonState = HIGH;  // État précédent du bouton
  int buttonState = digitalRead(buttonPin);  // Lecture de l'état actuel du bouton

  // Vérifie si l'état du bouton a changé
  if (buttonState != lastButtonState) {
    lastDebounceTime = millis();  // Réinitialise le temps de debounce
  }

  // Si le délai de debounce est écoulé
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Si l'état a réellement changé après le délai
    if (buttonState == LOW && lastButtonState == HIGH) {
      // Inverse l'état de mesureActive
      mesureActive = !mesureActive;
    }
  }

  lastButtonState = buttonState;  // Met à jour l'état précédent
}
