#include <Arduino.h>
#include <cmath>

float n = 0.;  //Nombre de cycles
float theta0 = 0.;
float theta1 = 0.;
float thetaN0 = 0.0; //theta0 N+1
float thetaN1 = 0.0; //theta1 N+1
float m  = 10.;      //Nombre de valeurs


float eps = 0.0005;    //Objectif d'erreur
float alpha = 0.00001; //Taux d'apprentissage


//Valeurs d'entrainements
float xi[] = {-255, 70, -128,-60, -50, 80, 30, 128, 200, -80};
float yi[] = {0,1,0,0,0,1,1,1,1,0};



void learnerMLR();


double z(float x) {
  return theta0 + theta1*x;
}

// fonction hypothese logistique binaire (Sigmoide)
float hypRLogBin(float x) {
  return 1/(1 + exp(-z(x)));
}

//fonction de prediction
float predict(float x) {
  return hypRLogBin(x);
}


void setup() {
  Serial.begin(115200);
  learnerMLR();
}

void loop() {
}

void learnerMLR() {
  double erreur = 0.0;
  double resHyp = 0.0;
  double tmpSomme0 = 0.0;
  double tmpSomme1 = 0.0;
  do {
    //Todo: Descente de gradient 
    //Regression logistique
    erreur = 0.0;
    resHyp = alpha/m;
    tmpSomme0 = 0.0;
    tmpSomme1 = 0.0;
    for (int i = 0; i < 24; i++)
    {
      tmpSomme0 +=  ( hypRLogBin(xi[i]) - yi[i] );
      tmpSomme1 +=  (hypRLogBin(xi[i]) - yi[i])*xi[i];
    }

    thetaN0 = theta0 - resHyp*tmpSomme0;
    thetaN1 = theta1 - resHyp*tmpSomme1;

    n++;
    theta0 = thetaN0;
    theta1 = thetaN1;
    for (int i = 0; i < 24; i++)
    {
      erreur +=  ( hypRLogBin(xi[i]) - (yi[i]) )*( hypRLogBin(xi[i]) - (yi[i]) );
    }
    erreur = erreur/48.;

    Serial.print("Erreur: ");
    Serial.println(erreur,6);
  } while (eps < erreur);
  Serial.print("Theta0: ");
  Serial.println(theta0,6);
  Serial.print("Theta1: ");
  Serial.println(theta1,6);
  Serial.print("Nombre de cycles: ");
  Serial.println(n);
}




