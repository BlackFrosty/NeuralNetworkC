//
//  calculs.c
//
//  Created by Maskott on 21/06/2021.
//

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

#include "calculs.h"
#include "structures.h"




/*--------------------------------------------------------------------------------------*/
/*  calculerProbaNeuroneCache                                                           */
/* Fonction : calcul de la probabilité pour un neurone de la couche cachee              */
/* Entree :  un pointeur vers un neuronne, le tableau des valeurs d entree du neurone   */
/* Sortie :  la probabilite calculee par le neuronne                                    */
/*--------------------------------------------------------------------------------------*/

void calculerProbaNeuroneCachee(T_NEURONE *neurone, double * tabEntrees, uint16_t ui16Size) {
    
    //mise à jour de la valeur de sortie du neurone
    neurone->dValeurSortie = sigmoide(moyennePonderee(neurone, tabEntrees, ui16Size));

}

/*--------------------------------------------------------------------------------------*/
/*  calculerProbaNeuroneSortie                                                          */
/* Fonction : calcul de la probabilité pour un neurone de la couche de sortie           */
/* Entree :  un pointeur vers un neuronne, le tableau des valeurs d entree du neurone   */
/* Sortie :  la probabilite calculee par le neuronne                                    */
/*--------------------------------------------------------------------------------------*/

void calculerProbaNeuroneSortie(T_NEURONE *neurone, double * tabEntrees, uint16_t ui16Size) {
    
    //mise à jour de la valeur de sortie du neurone
    neurone->dValeurSortie = moyennePonderee(neurone, tabEntrees, ui16Size);

}
/*--------------------------------------------------------------------------------------*/
/*  moyennePonderee                                                                     */
/* Fonction : fonctgion d agregation de type moyenne ponderee                           */
/* Entree :  un pointeur vers un neuronne, le tableau des valeurs d entree du neurone   */
/* Sortie :  la moyenne ponderee de ces entrees                                         */
/* avant le calcul de la sigmoide par le neurone                                        */
/*--------------------------------------------------------------------------------------*/

double moyennePonderee(T_NEURONE *neurone, double * tabEntrees, uint16_t ui16Size) {
    
    double moyennePonderee = 0;

    //pour chaque dendrite
    for (uint16_t numDendrite = 0 ; numDendrite < ui16Size ; numDendrite++) {

        moyennePonderee +=  tabEntrees[numDendrite] * neurone->pdPoids[numDendrite];
    }

    return moyennePonderee;
}

/*-----------------------------------------------------------------*/
/*  sigmoide                                                       */
/* Fonction : calcule la sigmoide de x                             */
/* Entree :  un reel x                                             */
/* Sortie :  Le resultat sigmoide(x)                               */
/*-----------------------------------------------------------------*/

double sigmoide ( double x ){
   return ( 1.0 / ( 1.0 + exp( -x ) ) ) ;
}

/*-----------------------------------------------------------------*/
/*  derivSigmoide                                                  */
/* Fonction : calcule la valeur de la derivee de la sigmoide en x  */
/* Entree :  un reel la valeur de sigmoide en x                    */
/* Sortie :  Le resultat sigmoide'(x)                              */
/* Attention : sigmoide'(x) = sigmoide(x)*(1 - sigmoide(x) )       */
/* il faut calculer avant sigmoide(x)                              */
/*-----------------------------------------------------------------*/

double derivSigmoide( double dSigmox ){
    return dSigmox * ( 1 - dSigmox ) ;
}

/*--------------------------------------------------------------------------------------------------------------*/
/*  sommeExpProba                                                                                               */
/* Fonction : calcule la somme des exponentielle des valeurs de la couche de sortie qui sera passee a softmax() */
/* Entree :  un pointeur vers la couche de sortie et sa taille                                                  */
/* Sortie :  un double qui sera utilise par softmax                                                             */
/*--------------------------------------------------------------------------------------------------------------*/

double sommeExpProba( T_COUCHE * coucheSortie ){
    double dSommeExp = 0 ;
    for ( uint8_t i = 0 ; i < coucheSortie->ui16NbNeurones ; i++ ){
        dSommeExp += exp( (coucheSortie->pNeur[i]).dValeurSortie ) ;
    }
    return dSommeExp ;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  softmax                                                                                                */
/* Fonction : remplace la valeur de sortie d un neurone de la couche sortie par exp(val)/somme(exp(val_i)) */
/* Entree :  pointeur vers la couche de sortie, la valeur sommeExpProba et le neuronne d'application       */
/* Sortie :  un double = nouvelle valeur de sortie du neurone                                              */
/*---------------------------------------------------------------------------------------------------------*/

void softmax( T_COUCHE * coucheSortie, double dSommeExp ){
    for ( uint8_t i = 0 ; i < coucheSortie->ui16NbNeurones ; i ++ ){
        (coucheSortie->pNeur[i]).dValeurSortie = exp( (coucheSortie->pNeur[i]).dValeurSortie ) / dSommeExp ;
    }
}

