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

/*---------------------------------------------*/
/*     INCLUDE PERSONNELS   - prototypes       */
/*---------------------------------------------*/

#include "structures.h"

#define MAX_NB_DENDRITES 785


void calculerProbaNeurone(T_NEURONE *, double [] )  ;
double moyennePonderee(T_NEURONE *, double []) ;
double sigmoide ( double ) ;
double derivSigmoide( double ) ;
double sommeExpProba( T_COUCHE * ) ;
void softmax( T_COUCHE *, double ) ;

#endif /* calculs_h */
