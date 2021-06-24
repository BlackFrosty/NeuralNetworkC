
#ifndef NEURALNETWORKC_UTIL_H
#define NEURALNETWORKC_UTIL_H

#define NB_ELEMENTS_BMP 28
#define NB_ELEMENT_MAX_POOLING 13
#define MAX_TAILLE_LIGNE 15


void MaxPooling(T_BITMAP * ptrBitmap);

int LirePoids(char * szNomFicIn ,  T_RSO * pReseau);
void afficherImage(T_BITMAP *, uint8_t);
#endif //NEURALNETWORKC_UTIL_H