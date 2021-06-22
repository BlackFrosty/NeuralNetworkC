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

/*---------------------------------------------*/
/*     INCLUDE PERSONNELS   - prototypes       */
/*---------------------------------------------*/

#include "Calculs.h"
#include "Structures.h"
#include "FonctionsRso.h"


/*---------------------------------------------------------------------------------------------------------*/
/*  propager                                                                                               */
/* Fonction : lance le calcul d reseau de neurone                                                          */
/* Entree :  pointeur vers le reseau, tableau de double des entree = 60000 bitmaps en 13x13 pxls           */
/* Sortie :                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/

void propager( T_RSO * reseau, double dTabEntree[] ){
    
    long int cpt ;
    double dTabEntreeUnitaire [170] ;
    
    // recuperation des pointeurs vers les couches cachee et sortie
    T_COUCHE * coucheCachee = &(reseau->pCouche[0]) ;
    T_COUCHE * coucheSortie = &(reseau->pCouche[1]) ;
    
    // parcours de l ensemble des bitmaps d entree
    for ( cpt = 0 ; cpt < 60000 ; cpt++ ){
        
        // recuperation 1 par 1 des bitmaps : 1 + 169 pixels
        dTabEntreeUnitaire[0] = 1.0 ;
        
        for ( int j = 1 ; j < 170 ; j++ ){
            dTabEntreeUnitaire[j] = dTabEntree[ 169 * cpt + j] ;
        }
        
        
        // envoi d un bitmap en entree de la couche cachee
        calculerProbaCoucheCahee(coucheCachee , dTabEntreeUnitaire) ;
        
        // calcul de la couche de sortie
        calculerProbaCoucheSortie(coucheCachee, coucheSortie ) ;
        
        // calcul de la somme des exponentielles des valeurs de sortie de la couche de sortie
        double dSommeExp = sommeExpProba( coucheSortie ) ;
        
        // application de softmax sur la couche de sortie
        softmax( coucheSortie, dSommeExp) ;
        
        
        // Afficher
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  calculerProbaCoucheCahee                                                                               */
/* Fonction : lance le calcul de la couche cachee                                                          */
/* Entree :  pointeur vers la couche cachee, tableau de double des entree = 1 bitmaps en 1 + 13x13 pxls    */
/* Sortie :                                                                                                */
/*---------------------------------------------------------------------------------------------------------*/

void calculerProbaCoucheCahee( T_COUCHE *coucheCachee, double dTabEntree[] ){
    
    for ( int cptNeurone = 0 ; cptNeurone < coucheCachee->ui16NbNeurones ; cptNeurone++ ){
        calculerProbaNeurone( &coucheCachee->pNeur[cptNeurone], dTabEntree ) ;
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
    dTabEntree[0] = 0 ;
    for ( int cpt = 0 ; cpt < coucheCachee->ui16NbNeurones ; cpt++ ){
        dTabEntree[cpt] = coucheCachee->pNeur->dValeurSortie ;
    }

    for ( int cptNeurone = 0 ; cptNeurone < coucheSortie->ui16NbNeurones ; cptNeurone++ ){
        calculerProbaNeurone( &coucheSortie->pNeur[cptNeurone], dTabEntree ) ;
    }
    
}


