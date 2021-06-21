//
// Created by tmdt2021 on 21/06/2021.
//

#include <stdlib.h> // calloc,malloc,free
#include "structures.h"

void * instancie_neurone(uint16_t ui16NbDendrites)
{
    T_NEURONE* pNeur = calloc(1, sizeof(T_NEURONE));
    pNeur->pdPoids = calloc(ui16NbDendrites, sizeof(double ));


}

void libere_neurone(T_NEURONE * pNeur)
{
    free(pNeur->pdPoids);
    free(pNeur);
}


