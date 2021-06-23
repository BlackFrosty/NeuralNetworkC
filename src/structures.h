//
// Created by user on 21/06/2021.
//

/**
 * structures.h
 * Constantes, structures du réseau de neurones et prototypes des fonctions de structures.c
 */

#ifndef NEURALNETWORKC_STRUCTURES_H
#define NEURALNETWORKC_STRUCTURES_H
#include <stdint.h> // uint8_t, uint16_t, uint32_t ...

#define NB_COUCHES  2
#define NB_DENDRITES_INIT   170
#define NB_NEURONES_COUCHE_CACHEE 66
#define NB_NEURONES_COUCHE_SORTIE 10

#define FIC_IMAGES  "../data/numbers/train-images-idx3-ubyte"
#define FIC_LABEL   "../data/numbers/train-labels-idx1-ubyte"
#define FIC_POIDS   "../CoeffOut.txt"

/**
 * T_NEURONE : contient
 *   - un pointeur vers un tableau de poids synaptiques
 *   - le nombre de dendrites
 *   - la valeur de sortie du neurone
 *   - la valeur de gradient
 */
typedef struct T_NEURONE {
    /* tableau de poids */
    double * pdPoids;
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
    T_NEURONE * pNeur;
    uint16_t ui16NbNeurones;
} T_COUCHE;

/**
 * T_RSO
 */
typedef struct T_RSO
{
    /* tableau de couches */
    T_COUCHE * pCouche;
    uint8_t ui8NbCouches;
} T_RSO;

/**
 * Type énuméré de 0 à 9, et 255 (inconnu)
 */
typedef enum enumLabel
{
    ZERO, UN, DEUX, TROIS, QUATRE, CINQ, SIX, SEPT, HUIT, NEUF, INCONNU=255
} enumLabel;

/**
 * Bitmap
 */
typedef struct T_BITMAP
{
    enumLabel label;
    double ** pTabPixelOriginal;
    double ** pTabPixelMaxP;
    uint32_t ui32LargeurOriginal;
    uint32_t ui32HauteurOriginal;
    uint32_t ui32LargeurMaxP;
    uint32_t ui32HauteurMaxP;
} T_BITMAP;

void instancie_neurone(T_NEURONE * , uint16_t );
void libere_neurone(T_NEURONE * );
void instancie_couche(T_COUCHE * , uint16_t );
void libere_couche(T_COUCHE * );
T_RSO * instancie_rso(uint8_t );
void libere_rso(T_RSO * rso);
void libere_cascade(T_RSO *pRso);
T_RSO * init_rso_neurones(uint8_t ui8NbCouches);
T_BITMAP * instancie_bitmap(uint32_t , uint32_t , uint32_t , uint32_t , enumLabel);
T_BITMAP * instancie_tab_bitmap(T_BITMAP * , uint32_t );

#endif //NEURALNETWORKC_STRUCTURES_H
