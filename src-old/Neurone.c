#include <stdio.h>
#include <stdlib.h> //malloc()
#include <math.h> //exp()
#include <string.h> //memcpy()

#include "Bitmap.h"
#include "Neurone.h"

//fonction d'initilisation d'un neurone
void initNeurone (T_NEURONE *neurone, long nbDendrites
        , double valeurSortie, double gradient
        , double (*fctActivation) (double)
        , double (*derivFctActivation) (double) ) {
    
    //Initialisation du champ nbDentrites
    neurone->nbDendrites = nbDendrites;

    //Initialisation du champs poids
    for (int i = 0; i < nbDendrites ; i++) {
        neurone->poids[i] = 0;
    }//for

    //Initialisation du champ valeur
    neurone->valeurSortie = valeurSortie;

    //Initialisation à zéro du champ gradient
    neurone->gradient = 0;

    //Initialisation du champ fctActivation
    neurone->fctActivation = fctActivation;

    //Initialisation du champ derivFctActivation
    neurone->derivFctActivation = derivFctActivation;

}//initNeurone


//fonction de calcul de la probabilité pour un neurone
double calculerProbaNeurone(T_NEURONE *neurone, double tabEntrees [MAX_NB_DENDRITES]) {
    
    //mise à jour de la valeur de sortie du neurone
    neurone->valeurSortie =
        neurone->fctActivation(moyennePonderee(neurone, tabEntrees));

    return neurone->valeurSortie;

}//CalculerProbaNeurone

//fonction d'agrégation de type "moyenne pondérée"
double moyennePonderee(T_NEURONE *neurone, double tabEntrees[MAX_NB_DENDRITES]) {
    
    double moyennePonderee = 0;

    //pour chaque dendrite
    for (long numDendrite = 0 ;
        (numDendrite < MAX_NB_DENDRITES) && (numDendrite < neurone->nbDendrites) ; 
        numDendrite++) {

        moyennePonderee +=  tabEntrees[numDendrite] * neurone->poids[numDendrite];
    
    }//for

    return moyennePonderee;

}//moyennePonderee

//fonction d'activation de type "sigmoide"
double sigmoide(double val) {
    return  (1.0 / (1.0 + exp(-val)));
}//sigmoide()

//dérivée de la fonction d'activation Sigmoide
double derivSigmoide(double val) {
    return  ( sigmoide(val) * (1 - sigmoide(val) )  );
}//sigmoide()

//fonction d'affichage d'un neurone
void afficherNeurone(T_NEURONE neurone) {

    //affichage du nombre des dendrites et des poids associés
    if (neurone.nbDendrites > 0) {
        printf("Nb dendrites=%.d Poids :", neurone.nbDendrites);
        for (long i = 0; i < neurone.nbDendrites; i++) {
            printf(" [%.6lf] ", neurone.poids[i]);
        }//for
    }//if

    //affichage de la valeur
    printf(", Valeur=%.4lf", neurone.valeurSortie);
    
    //affichage du gradient
    printf(", Gradient=%.4lf", neurone.gradient);

}//afficherNeurone()