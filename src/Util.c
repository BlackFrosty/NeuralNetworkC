#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

#include "functionsIO.h"

#include "Util.h"

// TODO : Utiliser le bitmap = FAIT 
//void MaxPooling (double adTabPixel[NB_ELEMENTS_BMP][NB_ELEMENTS_BMP], double adTabResultat[NB_ELEMENT_MAX_POOLING][NB_ELEMENT_MAX_POOLING]){
void MaxPooling (T_BITMAP * ptrBitmap){
    int x = 0 ;
    int y = 0 ;

    for (int i = 1 ; i < NB_ELEMENTS_BMP - 1 ; i+=2, x++, y=0) {

        for (int j=  1 ; j < NB_ELEMENTS_BMP - 1 ; j+=2, y++){

            ptrBitmap->pTabPixelMaxP[x][y] = fmax(ptrBitmap->pTabPixelOriginal[i][j], ptrBitmap->pTabPixelOriginal[i+1][j]) ;
            
            if (ptrBitmap->pTabPixelMaxP[x][y] < fmax(ptrBitmap->pTabPixelOriginal[i][j+1],ptrBitmap->pTabPixelOriginal[i+1][j+1])) 
            {
                ptrBitmap->pTabPixelMaxP[x][y] = fmax(ptrBitmap->pTabPixelOriginal[i][j+1],ptrBitmap->pTabPixelOriginal[i+1][j+1] );
            }//if

        }//for

    }//for

}// fin MAxPooling

//fonction qui initiliase les poids du RSO à partir d'un fichier de poids
//tous les poids sont stockées à la suite, un par ligne
int LirePoids(char * szNomFicIn ,  T_RSO * pReseau) {

    //ouverture fichier
    //ouverture contrôlée du fichier, en lecture binaire
	FILE * fpFicIn = fopen(szNomFicIn, "rt");

	if (fpFicIn == NULL) {
        fprintf(stderr, "Impossible d'ouvrir le fichier d'entrees '%s'.\n", szNomFicIn);
		exit(EXIT_FAILURE);
	}//if

    int cptValLues = 0;
    char ligne [MAX_TAILLE_LIGNE] = "";

    //lire tableau

    //pour chaque couche du RSO
    for (  int numCouche = 0 ; numCouche < pReseau->ui8NbCouches ; numCouche++ ) {

        //pointeur vers la couche courante
        T_COUCHE * couche = &pReseau->pCouche[numCouche];

         //pour chaque neurone de la couche courante
         // TODO : Neurone de biais ? A vérifier ou faire 2 boucles (1 par couche)
        for (  int numNeurone = (pReseau->ui8NbCouches -1 == numCouche) ? 0 : 1 ; (numNeurone < couche[numCouche].ui16NbNeurones)
            && ( fgets(ligne, MAX_TAILLE_LIGNE, fpFicIn) != NULL );
                 numCouche++ ) {//pour chaque neurone de la couche

            //pointeur vers le neurone courant
            T_NEURONE * neurone = &couche->pNeur[numNeurone];

            //pour chaque case de poids du neurone courant
            for( int numPoids = 0; numPoids < neurone->ui16NbDendrites ; numPoids++, cptValLues++) {

                //tentative de lecture d'un poids et d'affection du poids lu dans le tableau de poids du neurone courant
                 if (sscanf(ligne, "%lf", &neurone->pdPoids[numPoids]) != 1) {

                    fprintf(stderr, "Impossible de lire le poids à la ligne %d.\n", cptValLues);
		            exit(EXIT_FAILURE);

                 }//if
            
            }//for

        }//for
    }//for


    //fermeture du fichier d'entrées
	fclose(fpFicIn);

    return cptValLues;

}//lirePoids()