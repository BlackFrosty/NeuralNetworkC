#ifndef COUCHE_NEUR_H_INCLUDED
#define COUCHE_NEUR_H_INCLUDED

#define MAX_NB_NEUR_COUCHE 10 //nombre maximum de neurone par couche

//définition du type de couche de neurone
typedef struct {
    long nbNeurones;
    T_NEURONE neurones[MAX_NB_NEUR_COUCHE];
}T_COUCHE;

//fonction d'initilisation d'une couche de neurones
void initCouche(T_COUCHE* coucheNeur, long nbNeurones
    , long nbDendrides);

//fonction d'initilisation d'une couche d'entrée d'un PMC
void initCoucheEntree(T_COUCHE* couche, T_BITMAP *elem);

double probaMax(T_COUCHE *couche
    , long *numNeurSortie);

void afficherCouche(T_COUCHE *couche);

#endif //COUCHE_NEUR_H_INCLUDED