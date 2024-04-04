#include <Arduino.h>

double n = 0.; //Nombre de cycles
double theta0 = 0.; 
double theta1 = 0.;
double thetaN0 = 0.0;  //theta0 N+1
double thetaN1 = 0.0; //theta1 N+1
double m  = 24.;      //Nombre de valeurs

//A modifier pour l'entrainement

double eps = 100000.;    //Objectif d'erreur
double alpha = 0.0005;    //Taux d'apprentissage

//Valeurs d'entrainements
double xi[] = {5.,5.,5.,5.,10.,10.,10.,10.,30.,30.,30.,30.,45.,45., 45.,45.,70.,70.,70.,70.,90.,90,90.,90};
double yi[] = {8.000,8.300,8.000,8.100,9.900,9.900,10.000,10.700,16.500,16.800,16.020, 16.150, 21.290, 21.620, 21.000, 20.700, 28.900, 28.200, 27.950, 27.810, 34.160,34.520,34.250,35.160};
// double yi[] = {8000.,8300.,8000.,8100.,9900.,9900.,10000.,10.700,16.500,16.800,16.020, 16.150, 21.290, 21.620, 21.000, 20.700, 28.900, 28.200, 27.950, 27.810, 34.160,34.520,34.250,35.160};
//Yi en k RPM


//Todo Fonction d'hypothese linéaire
double hypRLin(double x) {
  return theta0 + theta1*x;
}

//Todo Fonction de prédiction duty cycle => vitesse
double predictVitesse(double x) {
  return hypRLin(x);
}

//Todo Fonction de prédiction vitesse => duty cycle
double predictDuty(double y){
  return (y-theta0)/theta1;
}





void learnerMLR() {
  double erreur = 0.0;
  double resHyp = 0.0;
  double tmpSomme0 = 0.0;
  double tmpSomme1 = 0.0;
  do {
    //Todo: Descente de gradient 
    //Regression lineaire
    erreur = 0.0;
    resHyp = alpha/m;
    tmpSomme0 = 0.0;
    tmpSomme1 = 0.0;
    for (int i = 0; i < 24; i++)
    {
      tmpSomme0 +=  ( hypRLin(xi[i]) - (yi[i]*1000.0) );
      tmpSomme1 +=  (hypRLin(xi[i]) - (yi[i]*1000.0))*xi[i];
    }

    thetaN0 = theta0 - resHyp*tmpSomme0;
    thetaN1 = theta1 - resHyp*tmpSomme1;

    n++;
    theta0 = thetaN0;
    theta1 = thetaN1;
    for (int i = 0; i < 24; i++)
    {
      erreur +=  ( hypRLin(xi[i]) - (yi[i]*1000.0) )*( hypRLin(xi[i]) - (yi[i]*1000.0) );
    }

    Serial.print("Erreur: ");
    Serial.println(erreur,6);
  } while (eps<erreur);
  Serial.print("Theta0: ");
  Serial.println(theta0,6);
  Serial.print("Theta1: ");
  Serial.println(theta1,6);
  Serial.print("Nombre de cycles: ");
  Serial.println(n);
}


void setup() {
  Serial.begin(9600);
  //Todo Entrainement + prediction
 learnerMLR();

}
//Rien dans la loop
void loop() {}
