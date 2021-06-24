//
//  FonctionsRso.h
//
//  Created by Maskott on 22/06/2021.
//

#ifndef FonctionsRso_h
#define FonctionsRso_h

#include <stdio.h>
#include "structures.h"
#include "Util.h"


double propager( T_RSO * , T_BITMAP * , uint32_t , T_STAT *) ;
void calculerProbaCoucheCachee(  double * , T_COUCHE * ) ;
void calculerProbaCoucheSortie( T_COUCHE *, T_COUCHE * ) ;
uint8_t labelPredit(T_COUCHE *couche) ;
void    initPoids ( T_RSO * );


#endif /* FonctionsRso_h */
