#ifndef NEURONE_H_INCLUDED
#define NEURONE_H_INCLUDED

#define MAX_NB_DENDRITES 785 //nombre maximum de dendrites

//d�finition du type structur� T_NEURONE
typedef struct T_NEURONE {
    
    long nbDendrites;
    
    double poids[MAX_NB_DENDRITES];
    //double* poids;
    
    //valeur du neurone, calcul�e par la fonction d'activation
    double valeurSortie;

    //Champ utilis� pour la retropopagation
    //Cf fonction "retropopager" et "errSortie" de PMC.c
    double gradient;

    //pointeur sur la fonction d'activation
    double (*fctActivation) (double);

    //pointeur sur la d�riv�e de la fonction d'activation
    double (*derivFctActivation) (double);

}T_NEURONE;//T_NEURONE


//fonction d'initialisation d'un neurone
void initNeurone(T_NEURONE* neurone
    , long nbDendrites
    , double valeurSortie
    , double gradient
    , double (*fctActivation) (double)
    , double (*derivFctActivation) (double));

//fonction de calcul de la probabilit�  pour un neurone
double calculerProbaNeurone
    (T_NEURONE *neurone, double tabEntrees[MAX_NB_DENDRITES]);

//fonction d'agr�gation de type "moyenne ponderee" (ou produit scalaire)
double moyennePonderee(T_NEURONE *neurone, double tabEntrees[MAX_NB_DENDRITES]);

//fonction d'activation de type Sigmoide
double sigmoide(double val);

//fonction deriv�e (au sens math�matique de sigmoide()
double derivSigmoide(double val);

//fonction d'affichage d'un neurone
void afficherNeurone(T_NEURONE neurone);

#endif // NEURONE_H_INCLUDED
