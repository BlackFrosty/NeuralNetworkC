//
//  calculs.h
//
//  Created by Maskott on 21/06/2021.
//

#ifndef calculs_h
#define calculs_h

/*---------------------------------------------*/
/*             INCLUDE LANGAGE C               */
/*---------------------------------------------*/


#include <stdio.h>
#include <stdint.h>

/*---------------------------------------------*/
/*     INCLUDE PERSONNELS   - prototypes       */
/*---------------------------------------------*/

#include "structures.h"

#define MAX_NB_DENDRITES 170


void calculerProbaNeuroneCachee(T_NEURONE *, double *, uint16_t )  ;
void calculerProbaNeuroneSortie(T_NEURONE *, double *, uint16_t )  ;
double moyennePonderee(T_NEURONE *, double *, uint16_t) ;
double sigmoide ( double ) ;
double derivSigmoide( double ) ;
double sommeExpProba( T_COUCHE * ) ;
void softmax( T_COUCHE *, double ) ;

#endif /* calculs_h */
