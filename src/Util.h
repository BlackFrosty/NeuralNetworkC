
#ifndef NEURALNETWORKC_UTIL_H
#define NEURALNETWORKC_UTIL_H

#define NB_ELEMENTS_BMP 28
#define NB_ELEMENT_MAX_POOLING 13
#define MAX_TAILLE_LIGNE 15

typedef struct T_STAT {
    
    double nbElements ,         //nombre de bitmap traités par le réseau
    double nbVraiPositifs ,     //nombre d'élements dont la prédiction annoncée est égale au label
    double nbFauxPosifis ,      //nombre d'élements dont la prédiction annoncée n'est pas égale au label
    double nbVraiNegatifs ,     //nombre d'élements dont la prédiction annonce correctement que cela ne correspond pas au label 
    double nbFauxNegatifs ,     //nombre d'éléments dont la prédiction annonce à tort que cela ne correspond pas au label
    double precision ,          //rapport nbVraiPositifs / (nbVraiPositifs + nbFauxPosifis)
    double rappel ,             //rapport nbVraiPositifs / (nbVraiPositifs + nbFauxNegatifs)

} T_STAT;


void MaxPooling(T_BITMAP * ptrBitmap);

int LirePoids(char * szNomFicIn ,  T_RSO * pReseau);

void afficherImage(T_BITMAP *, uint8_t);

void majStats(T_STATS *stats, double proba, enumLabel labelRecherche, enumLabel labelEffectif) ;

void afficherStats(T_STATS stats) ;

#endif //NEURALNETWORKC_UTIL_H