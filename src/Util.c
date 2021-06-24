#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "structures.h"

#include "functionsIO.h"

#include "Util.h"

void MaxPooling (T_BITMAP * ptrBitmap){
    int x = 0 ; //ligne du tableau de MaxPooling
    int y = 0 ; //colonne du tableau de MaxPooling

    for (int i = 1 ; i < ptrBitmap->ui32HauteurOriginal - 1 ; i+=2, x++, y=0) 
    {
        for (int j=  1 ; j < ptrBitmap->ui32LargeurOriginal - 1 ; j+=2, y++)
        {
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

    int cptValLues = 0; //compteur du nombre de poids lus
    char ligne [MAX_TAILLE_LIGNE] = ""; //une ligne du fichier poids correspond à un poids et la taille max de cette ligne est 15

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
            }//for

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

    //affichage de l'image récupérée dans fichier image et enrengistrée dans le BITMAP
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

    // affichage du Label récupérer dans le fichier LAbel et enrengistré dans le BITMAP
    printf("Label : %d\n", elem->label);

    //affichage de l'image après le MaxPooling enrengistrée dans le BITMAP
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

}//afficherImage