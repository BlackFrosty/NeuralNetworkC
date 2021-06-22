
#ifndef NEURALNETWORKC_UTIL_H
#define NEURALNETWORKC_UTIL_H

#define NB_ELEMENT_MAX_POOLINIG 13 

#define MAX_TAILLE_LIGNE 15

void MaxPooling (double adTabPixel[NB_ELEMENTS_BMP][NB_ELEMENTS_BMP], double tabResultat[NB_ELEMENT_MAX_POOLINIG][NB_ELEMENT_MAX_POOLINIG]);

int LirePoids(char * szNomFicIn ,  T_RSO * pReseau);

#endif //NEURALNETWORKC_UTIL_H