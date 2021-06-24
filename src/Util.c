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
 * @param ui8Mode : Somme de modes d'affichage : 4 (Affiche Original), 2 (Affiche MaxPool), 1 (Affiche Label) = 7 max
 */
void afficherImage(T_BITMAP * elem, uint8_t ui8Mode) {

    _Bool bAfficheOriginal = 0, bAfficheMaxP = 0, bAfficheLabel = 0;

    switch (ui8Mode)
    {
        case 7:
            bAfficheOriginal = 1;
            bAfficheMaxP = 1;
            bAfficheLabel = 1;
            break;
        case 6:
            bAfficheOriginal = 1;
            bAfficheMaxP = 1;
            break;
        case 5:
            bAfficheOriginal = 1;
            bAfficheLabel = 1;
            break;
        case 4:
            bAfficheOriginal = 1;
            break;
        case 3:
            bAfficheMaxP = 1;
            bAfficheLabel = 1;
            break;
        case 2:
            bAfficheMaxP = 1;
            break;
        case 1:
            bAfficheLabel = 1;
            break;
        default:
            perror("AfficheImage : Erreur de mode");
    }

    if (bAfficheOriginal)
    {
        printf("\n");

        //affichage de l'image récupérée dans fichier image et enrengistrée dans le BITMAP
        for (int i = 0; i < elem->ui32HauteurOriginal; i++) {
            for (int j = 0; j < elem->ui32LargeurOriginal; j++) {
                if (elem->pTabPixelOriginal[i][j] > (double) 0) {
                    printf("*");
                } else {
                    printf(" ");
                }//if
            }//for
            printf("\n");
        }//for
        printf("\n");
    }

    if (bAfficheMaxP)
    {
        //affichage de l'image après le MaxPooling enrengistrée dans le BITMAP
        for (int i = 0; i < elem->ui32HauteurMaxP; i++) {
            for (int j = 0; j < elem->ui32LargeurMaxP; j++) {
                if (elem->pTabPixelMaxP[i][j] > (double)0) {
                    printf("*");
                } else {
                    printf(" ");
                }//if
            }//for
            printf("\n");
        }//for
        printf("\n");
    }
    if (bAfficheLabel)
    {
        // affichage du Label récupérer dans le fichier LAbel et enrengistré dans le BITMAP
        printf("Label : %d\n", elem->label);
    }
}//afficherImage

void majStats(T_STATS *stats, double proba , enumLabel labelRecherche, enumLabel labelEffectif ) {

    //incrémentation du nombre d'éléments analysés
    stats->nbElements++;

    //incrémentation du champs concerné
    if (proba >= 0.5) {

        if (labelEffectif == labelRecherche) {
            //Prediction valide : vrai positif
            stats->nbVraiPositifs++;
        }
        else {//labelEffectif != labelRecherche
         //Prediction invalide : faux positif [ERREUR]
            stats->nbFauxPositifs++;
        }//if

    }
    else { //proba < 0.5

        if (labelEffectif != labelRecherche) {
            // Prediction valide : vrai negatif
            stats->nbVraiNegatifs++;
        }
        else { //labelEffectif == labelRecherche
         //Prediction invalide : faux negatif [ERREUR]");
            stats->nbFauxNegatifs++;
        } //if

    }//if

    //mise à jour du champ "precision"
    if (stats->nbVraiPositifs + stats->nbFauxPositifs) {//pour eviter la division par zero
        stats->precision
            = stats->nbVraiPositifs / (stats->nbVraiPositifs + stats->nbFauxPositifs);
    }//if

    //mise à jour du champ "rappel"
    if (stats->nbVraiPositifs + stats->nbFauxNegatifs) {//pour eviter la division par zero
        stats->rappel
            = stats->nbVraiPositifs / (stats->nbVraiPositifs + stats->nbFauxNegatifs);
    }//if

}//majStats

void afficherStats(T_STATS stats) {

    printf("\nPrecision  = %.0lf%%, Rappel = %.0lf%%, nb Vrais positifs = %.0lf, nb Faux positifs = %.0lf, nb Vrais negatifs = %.0lf, nb Faux negatifs = %.0lf\n"
        , stats.precision * 100
        , stats.rappel * 100
        , stats.nbVraiPositifs
        , stats.nbFauxPositifs
        , stats.nbVraiNegatifs
        , stats.nbFauxNegatifs);

}//afficherStats()