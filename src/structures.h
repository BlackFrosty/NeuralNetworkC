//
// Created by user on 21/06/2021.
//


#ifndef NEURALNETWORKC_STRUCTURES_H
#define NEURALNETWORKC_STRUCTURES_H
#include <stdint.h>

#define NB_COUCHES  2
#define NB_DENDRITES_INIT   170
#define NB_NEURONES_COUCHE_1 66
#define NB_NEURONES_COUCHE_2 10



/**
 * T_NEURONE : contient
 *   - un pointeur vers un tableau de poids synaptiques
 *   - le nombre de dendrites
 *   - la valeur de sortie du neurone
 *   - la valeur de gradient
 */

typedef struct T_NEURONE {
    /* tableau de poids */
    double ** pdPoids;
    uint16_t ui16NbDendrites;
    double dValeurSortie;
    double dGradient;
    double (*fActication)(double);
    double (*fDerivActivation)(double);
} T_NEURONE;

/**
 * T_COUCHE
 */
typedef struct T_COUCHE {
    /* tableau de neurones */
    T_NEURONE ** pNeur;
    uint16_t ui16NbNeurones;
} T_COUCHE;

/**
 * T_RSO
 */

typedef struct T_RSO
{
    /* tableau de couches */
    T_COUCHE ** pCouche;
    uint8_t ui8NbCouches;
} T_RSO;

typedef enum
{
    ZERO, UN, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, INCONNU=255
} enumLabel;

typedef struct
{
    enumLabel label;
    double ** pTabPixel;
    uint8_t ui8Largeur;
    uint8_t ui8Longueur;
} T_BITMAP;

T_NEURONE * instancie_neurone(uint16_t );
void libere_neurone(T_NEURONE * );
T_COUCHE * instancie_couche(uint16_t );
void libere_couche(T_COUCHE * );
void * instancie_rso(uint8_t ui8NbCouches);
void libere_rso(T_RSO * rso);
void libere_cascade(T_RSO *pRso);
T_RSO * init_rso_neurones(uint8_t ui8NbCouches);


#endif //NEURALNETWORKC_STRUCTURES_H
