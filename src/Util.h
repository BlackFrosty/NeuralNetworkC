
#ifndef NEURALNETWORKC_UTIL_H
#define NEURALNETWORKC_UTIL_H

#define NB_ELEMENTS_BMP 28
#define NB_ELEMENT_MAX_POOLING 13
#define MAX_TAILLE_LIGNE 15

void MaxPooling (double adTabPixel[NB_ELEMENTS_BMP][NB_ELEMENTS_BMP], double adTabResultat[NB_ELEMENT_MAX_POOLING][NB_ELEMENT_MAX_POOLING]);

int LirePoids(char * szNomFicIn ,  T_RSO * pReseau);

#endif //NEURALNETWORKC_UTIL_H