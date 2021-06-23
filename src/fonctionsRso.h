//
//  FonctionsRso.h
//
//  Created by Maskott on 22/06/2021.
//

#ifndef FonctionsRso_h
#define FonctionsRso_h

#include <stdio.h>
#include "structures.h"


void propager( T_RSO * , T_BITMAP * , uint32_t ) ;
void calculerProbaCoucheCachee(  double * , T_COUCHE * ) ;
void calculerProbaCoucheSortie( T_COUCHE *, T_COUCHE * ) ;
uint8_t afficherProbaCouche( T_COUCHE *  ) ;


#endif /* FonctionsRso_h */
