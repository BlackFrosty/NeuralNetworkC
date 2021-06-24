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

    for (int i = 1 ; i < ptrBitmap->ui32HauteurOriginal - 1 ; i+=2, x++, y=0) {
        for (int j=  1 ; j < ptrBitmap->ui32LargeurOriginal - 1 ; j+=2, y++){

            ptrBitmap->pTabPixelMaxP[x][y] = fmax(ptrBitmap->pTabPixelOriginal[i][j], ptrBitmap->pTabPixelOriginal[i+1][j]) ;
            
            if (ptrBitmap->pTabPixelMaxP[x][y] < fmax(ptrBitmap->pTabPixelOriginal[i][j+1],ptrBitmap->pTabPixelOriginal[i+1][j+1])) 
            {
                ptrBitmap->pTabPixelMaxP[x][y] = fmax(ptrBitmap->pTabPixelOriginal[i][j+1],ptrBitmap->pTabPixelOriginal[i+1][j+1] );
            }//if
            /*printf("%lf, (%lf %lf %lf %lf)\n", ptrBitmap->pTabPixelMaxP[x][y],
                   ptrBitmap->pTabPixelOriginal[i][j], ptrBitmap->pTabPixelOriginal[i][j+1],
                   ptrBitmap->pTabPixelOriginal[i+1][j], ptrBitmap->pTabPixelOriginal[i+1][j+1]);*/
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
        T_COUCHE * couche = &(pReseau->pCouche[numCouche]);

         //pour chaque neurone de la couche courante
         // Si numCouche = 0, on commence l'itération à 1 (sans utiliser le neurone de biais), 0 si couche de sortie
        for (  int numNeurone = (pReseau->ui8NbCouches -1 == numCouche) ? 0 : 1 ;
                (numNeurone < couche[numCouche].ui16NbNeurones);
                numNeurone++ )
        {
            //pour chaque neurone de la couche

            //pointeur vers le neurone courant
            T_NEURONE * neurone = &couche->pNeur[numNeurone];

            //pour chaque case de poids du neurone courant
            for( int numPoids = 0;
                numPoids < neurone->ui16NbDendrites && fgets(ligne, MAX_TAILLE_LIGNE, fpFicIn) != NULL ;
                numPoids++, cptValLues++)
            {
                //tentative de lecture d'un poids et d'affection du poids lu dans le tableau de poids du neurone courant
                 if (sscanf(ligne, "%lf", &neurone->pdPoids[numPoids]) != 1)
                 {
                    fprintf(stderr, "Impossible de lire le poids à la ligne %d.\n", cptValLues);
		            exit(EXIT_FAILURE);
                 }
                 /*else
                 {
                     printf("ligne %s, %lf\n", ligne, neurone->pdPoids[numPoids]);
                 }*/ //if
                //printf("cptValLues = %d\n", cptValLues);
            }//for
            //printf("cptValLues For = %d\n", cptValLues);
        }//for
    }//for
    printf("cptValLues Final = %d\n", cptValLues);

    //fermeture du fichier d'entrées
	fclose(fpFicIn);

    return cptValLues;

}//lirePoids()

//fonction d'affichage d'une image d'un bitmap
/**
 * afficherImage : Affiche sommairement le contenu de tableaux de pixels, ainsi que le label associé, si défini
 * @param elem : Pointeur sur T_BITMAP
 */
void afficherImage(T_BITMAP * elem) {

    printf("\n");

    for (int i = 0; i < elem->ui32HauteurOriginal; i++) {
        for (int j = 0; j < elem->ui32LargeurOriginal; j++) {
            if (elem->pTabPixelOriginal[i][j] > (double)0) {
                printf("*");
            } else {
                printf(" ");
            }//if
        }//for
        printf("\n");
    }//for
    printf("\n");

    /*for (int i = 0; i < elem->ui32HauteurMaxP; i++) {
        for (int j = 0; j < elem->ui32LargeurMaxP; j++) {
            if (elem->pTabPixelMaxP[i][j] > (double)0) {
                printf("*");
            } else {
                printf(".");
            }//if
        }//for
        printf("\n");
    }//for
    printf("\n");*/

    printf("Label : %d\n", elem->label);
}//afficherImage