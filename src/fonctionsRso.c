//
//  FonctionsRso.c
//  calculs
//
//  Created by Maskott on 22/06/2021.
//



// todo
// remplacer les veleurs en dur par des constantes adequates
// nb_bitmpas_entree 60000
// nb_valeurs_entree_couche_chachee 170
// nb_neurones_couche_cache  1 biais + 65


/*---------------------------------------------*/
/*             INCLUDE LANGAGE C               */
/*---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

/*---------------------------------------------*/
/*     INCLUDE PERSONNELS   - prototypes       */
/*---------------------------------------------*/

#include "calculs.h"
#include "structures.h"
#include "fonctionsRso.h"
#include "Util.h"


/*---------------------------------------------------------------------------------------------------------*/
/*  propager                                                                                               */
/* Fonction : lance le calcul d reseau de neurone                                                          */
/* Entree :  pointeur vers le reseau, tableau de double des entree = 60000 bitmaps en 13x13 pxls           */
/* Sortie :                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/

void propager( T_RSO * reseau, T_BITMAP * TabEntreeBitmap, uint32_t ui32NbBitmap ){

    //printf("Pointeurs : %p %p\n", reseau, TabEntreeBitmap);
    // 170 = nb de dendrites des neurones de la couche cachee
    double dTabEntreeUnitaire [170] ;
    uint32_t ui32Correct = 0;
    uint8_t  neuroneWinner = 0;
    
    // recuperation des pointeurs vers les couches cachee et sortie
    T_COUCHE * coucheCachee = &(reseau->pCouche[0]) ;
    T_COUCHE * coucheSortie = &(reseau->pCouche[1]) ;
    //printf("@Couches %p %p\n", coucheCachee, coucheSortie);

    // parcours de l ensemble des bitmaps d entree
    //for ( uint32_t cptBitmap = 0 ; cptBitmap < 10 ; cptBitmap++ ){
    for ( uint32_t cptBitmap = 0 ; cptBitmap < ui32NbBitmap ; cptBitmap++ ){

        //printf("Avant TabEntreeBitmap\n");
        T_BITMAP bitmapCourant = TabEntreeBitmap[cptBitmap] ;
        /*printf("Bitmap : %d %d %d %d\n", bitmapCourant.ui32HauteurOriginal,
                bitmapCourant.ui32LargeurOriginal, bitmapCourant.ui32HauteurMaxP, bitmapCourant.ui32LargeurMaxP);*/

        // recuperation 1 par 1 des bits du bitmapcourant : 1 + 169 pixels
        //afficherImage(bitmapCourant);

        uint8_t k = 0 ;
        dTabEntreeUnitaire[k] = 1.0 ;
        //printf("Avant for\n");
        for ( uint16_t j = 0 ; j < bitmapCourant.ui32HauteurMaxP ; j++ ){
            for ( uint16_t i = 0 ; i < bitmapCourant.ui32LargeurMaxP ; i++ ){
                //printf("h*l %d %d j:%d i:%d\n", bitmapCourant.ui32HauteurMaxP, bitmapCourant.ui32LargeurMaxP, j, i);
                k += 1 ;
                dTabEntreeUnitaire[k] = bitmapCourant.pTabPixelMaxP[j][i] ;
                
            }
        }
        /*for (int i = 0 ; i  < 170 ; i++)
        {
            printf("%lf ", dTabEntreeUnitaire[i]);
        }
        printf("\n");*/

        //printf("Avant calculerProbaCoucheCachee\n");
        // envoi d un bitmap en entree de la couche cachee
        calculerProbaCoucheCachee( dTabEntreeUnitaire, coucheCachee) ;

        //printf("Avant calculerProbaCoucheSortie\n");
        // calcul de la couche de sortie
        calculerProbaCoucheSortie( coucheCachee, coucheSortie ) ;



        //printf("Avant labelPredit\n");
        neuroneWinner = labelPredit(coucheSortie) ;
        //printf("Après labelPredit\n");

        //printf("Label d'entrainement : %d\n\n ", bitmapCourant.label);
        if (neuroneWinner == bitmapCourant.label)
        {
            ui32Correct++;
        }
        else
        {
            afficherImage(&bitmapCourant, 3);
            printf("Le réseau a déterminé %d\n", neuroneWinner);
        }
    }
    printf("Nombre de résultats corrects / tests totaux : %d/%d soit %f%%\n", ui32Correct, ui32NbBitmap, ui32Correct/ (double) ui32NbBitmap * 100);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  calculerProbaCoucheCachee                                                                               */
/* Fonction : lance le calcul de la couche cachee                                                          */
/* Entree :  pointeur vers la couche cachee, tableau de double des entree = 1 bitmaps en 1 + 13x13 pxls    */
/* Sortie :                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
void calculerProbaCoucheCachee( double * dTabEntree, T_COUCHE *coucheCachee ){
    
    // TODO : Cas du neurone de biais
    coucheCachee->pNeur[0].dValeurSortie = 1.0;
    
    // TODO : Cas des neurone normaux
    for ( uint16_t cptNeurone = 1 ; cptNeurone < coucheCachee->ui16NbNeurones ; cptNeurone++ ){
        calculerProbaNeuroneCachee( &coucheCachee->pNeur[cptNeurone], dTabEntree, coucheCachee->pNeur[cptNeurone].ui16NbDendrites) ;
    }

    
}

/*---------------------------------------------------------------------------------------------------------*/
/*  calculerProbaCoucheSortie                                                                              */
/* Fonction : lance le calcul de la couche cachee                                                          */
/* Entree :  pointeur vers la couche cachee, poiteur vers la couche de sotie                               */
/* Sortie :                                                                                                */
/* les valeurs de sortie de neurones de la cch cachee sont recuperees et servent d entree a la cch sortie  */
/*---------------------------------------------------------------------------------------------------------*/

void calculerProbaCoucheSortie( T_COUCHE *coucheCachee, T_COUCHE *coucheSortie ){
    double dTabEntree [66] = {0} ;
    
    // recuperation des valeurs de sortie de la couche cachee en tant qu entree de la couche de sortie
    for ( uint8_t cpt = 0 ; cpt < coucheCachee->ui16NbNeurones ; cpt++ ){
        dTabEntree[cpt] = coucheCachee->pNeur[cpt].dValeurSortie ;
    }

    // aplication de la fonction d activation sur chaque neurone
    for ( uint8_t cptNeurone = 0 ; cptNeurone < coucheSortie->ui16NbNeurones ; cptNeurone++ ){

        calculerProbaNeuroneSortie( &coucheSortie->pNeur[cptNeurone], dTabEntree,  coucheSortie->pNeur[cptNeurone].ui16NbDendrites) ;
    }
    
    // calcul de la somme des exponentielles des valeurs de sortie de la couche de sortie
    double dSommeExp = sommeExpProba( coucheSortie ) ;
    
    // application de softmax sur la couche de sortie
    softmax( coucheSortie, dSommeExp ) ;
    
}

/*---------------------------------------------------------------------------------------------------------*/
/*  labelPredit                                                                                    */
/* Fonction : affiche les poba calculee par les neurones sur une couche                                    */
/* Entree :  pointeur vers la couche                                                                       */
/* Sortie :                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
uint8_t labelPredit(T_COUCHE * couche ){

    uint8_t neuroneMax = 0;
    double valMax = 0.0;
    for ( uint8_t cpt = 0 ; cpt < couche->ui16NbNeurones ; cpt++ ){
        //printf("Probabilite calculee par le neurone %d : %.4f\n", cpt, couche->pNeur[cpt].dValeurSortie ) ;
        if (couche->pNeur[cpt].dValeurSortie > valMax)
        {
            valMax = couche->pNeur[cpt].dValeurSortie;
            neuroneMax = cpt;
        }
    }
    //printf("Probabilite max calculee par le neurone %d : %.4f\n", neuroneMax, valMax ) ;
    //printf("\n");
    return neuroneMax;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  initPoids                                                                                              */
/* Fonction : initialiser les poids avec des nombres aléatoires.                                           */
/* Entree :  pointeur vers la couche                                                                       */
/* Sortie :                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/
void    initPoids ( T_RSO * pReseau ) {
//pour chaque couche du RSO
    for (  int numCouche = 0 ; numCouche < pReseau->ui8NbCouches ; numCouche++ ) {

        //pointeur vers la couche courante
        T_COUCHE * couche = &(pReseau->pCouche[numCouche]);

         //pour chaque neurone de la couche courante
         // Si numCouche = 0, on commence l'itération à 1 (sans utiliser le neurone de biais), 0 si couche de sortie
        for (  int numNeurone = (pReseau->ui8NbCouches -1 == numCouche) ? 0 : 1 ; (numNeurone < couche[numCouche].ui16NbNeurones); numNeurone++ ) {
            
            //pour chaque neurone de la couche

            //pointeur vers le neurone courant
            T_NEURONE * neurone = &couche->pNeur[numNeurone];

            //pour chaque case de poids du neurone courant
            for( int numPoids = 0; numPoids < neurone->ui16NbDendrites; numPoids++) {
                
                //affection d'un nombre random comme poids dans le tableau de poids du neurone courant
                srand ( time (NULL) );
                neurone->pdPoids[numPoids] = (double) rand() / RAND_MAX * 2.0 - 1.0; //range {-1 to 1} => (MAX - MIN) - MIN
            }
        }
    }

}
