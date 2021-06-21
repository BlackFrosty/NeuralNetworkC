#ifndef NEURONE_H_INCLUDED
#define NEURONE_H_INCLUDED

#define MAX_NB_DENDRITES 785 //nombre maximum de dendrites

//définition du type structuré T_NEURONE
typedef struct T_NEURONE {
    
    long nbDendrites;
    
    double poids[MAX_NB_DENDRITES];
    //double* poids;
    
    //valeur du neurone, calculée par la fonction d'activation
    double valeurSortie;

    //Champ utilisé pour la retropopagation
    //Cf fonction "retropopager" et "errSortie" de PMC.c
    double gradient;

    //pointeur sur la fonction d'activation
    double (*fctActivation) (double);

    //pointeur sur la dérivée de la fonction d'activation
    double (*derivFctActivation) (double);

}T_NEURONE;//T_NEURONE


//fonction d'initialisation d'un neurone
void initNeurone(T_NEURONE* neurone
    , long nbDendrites
    , double valeurSortie
    , double gradient
    , double (*fctActivation) (double)
    , double (*derivFctActivation) (double));

//fonction de calcul de la probabilité  pour un neurone
double calculerProbaNeurone
    (T_NEURONE *neurone, double tabEntrees[MAX_NB_DENDRITES]);

//fonction d'agrégation de type "moyenne ponderee" (ou produit scalaire)
double moyennePonderee(T_NEURONE *neurone, double tabEntrees[MAX_NB_DENDRITES]);

//fonction d'activation de type Sigmoide
double sigmoide(double val);

//fonction derivée (au sens mathématique de sigmoide()
double derivSigmoide(double val);

//fonction d'affichage d'un neurone
void afficherNeurone(T_NEURONE neurone);

#endif // NEURONE_H_INCLUDED
