//
// Created by user on 21/06/2021.
//


#ifndef NEURALNETWORKC_STRUCTURES_H
#define NEURALNETWORKC_STRUCTURES_H
#include <stdint.h>

/**
 * T_NEURONE : contient
 *   - un pointeur vers un tableau de poids synaptiques
 *   - le nombre de dendrites
 *   - la valeur de sortie du neurone
 *   - la valeur de gradient
 */

typedef struct {
    double * pdPoids;
    uint16_t ui16NbDendrites;
    double dValeurSortie;
    double dGradient;
} T_NEURONE;

/**
 * T_COUCHE
 */
typedef struct {
    T_NEURONE * pNeur;
    uint16_t ui16NbNeurones;
} T_COUCHE;

/**
 * T_RSO
 */

typedef struct
{
    T_COUCHE * pCouche;
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



#endif //NEURALNETWORKC_STRUCTURES_H
