//
// Created by tmdt2021 on 21/06/2021.
//

#include <stdio.h>
#include <stdlib.h> // calloc,malloc,free
#include "structures.h"

T_NEURONE * instancie_neurone(uint16_t ui16NbDendrites)
{
    T_NEURONE* pNeur ; // = calloc(1, sizeof(T_NEURONE));
    printf("Neurone av : %p\n", pNeur->pdPoids);
    pNeur->pdPoids = calloc(ui16NbDendrites, sizeof(double ));
    printf("Neurone ap : %p\n", pNeur->pdPoids);
    pNeur->ui16NbDendrites = ui16NbDendrites;
    return pNeur;
}

void libere_neurone(T_NEURONE * pNeur)
{
    free(pNeur->pdPoids);
    pNeur->pdPoids = NULL;
    //free(pNeur);
    //pNeur = NULL;
}

T_COUCHE * instancie_couche(uint16_t ui16NbNeurones)
{
    T_COUCHE * pCouche ;
    pCouche = calloc(1, sizeof(T_COUCHE));
    pCouche->ui16NbNeurones = ui16NbNeurones;
    pCouche->pNeur = calloc(pCouche->ui16NbNeurones, sizeof(T_NEURONE));
    return pCouche;
}

void libere_couche(T_COUCHE * pCouche)
{
    free(pCouche->pNeur);
    pCouche->pNeur = NULL;
}

void * instancie_rso(uint8_t ui8NbCouches)
{
    static T_RSO rso;
    rso.ui8NbCouches = ui8NbCouches;
    rso.pCouche = calloc(rso.ui8NbCouches, sizeof(T_COUCHE));
    return &rso;
}

void libere_rso(T_RSO * rso)
{

}

/**
 * libere_cascade
 * @param pRso
 */
void libere_cascade(T_RSO *pRso)
{
    /* Pour chaque couche, libération récursive des neurones */
    for (uint8_t iNbC = 0 ; iNbC < pRso->ui8NbCouches; iNbC++)
    {
        /* Pour chaque neurone */
        for (uint16_t iNbN = 0 ; iNbN < pRso->pCouche[iNbC]->ui16NbNeurones; iNbN)
        {
            libere_neurone(pRso->pCouche[iNbC]->pNeur[iNbN]);
        }
        libere_couche(pRso->pCouche[iNbC]);
    }
    //libere_rso(pRso)
}

/**
 * init_rso_neurones : crée statiquement le réseau de neurones
 * @param ui8NbCouches
 *
 */
T_RSO * init_rso_neurones(uint8_t ui8NbCouches)
{
    T_RSO * pReseau ;
    /* instanciation du réseau */
    pReseau = instancie_rso((ui8NbCouches));

    /* instanciation des couches */
    pReseau->pCouche[0] = instancie_couche(NB_NEURONES_COUCHE_1);
    /* instanciation différenciée de la couche 0 */
    for (uint16_t i = 0 ; i < pReseau->pCouche[0]->ui16NbNeurones; i++)
    {
        pReseau->pCouche[0]->pNeur[i] = instancie_neurone(NB_DENDRITES_INIT);
    }
    pReseau->pCouche[1] = instancie_couche(NB_NEURONES_COUCHE_2);
    /* instanciation différenciée de la couche 1 */
    for (uint16_t i = 0 ; i < pReseau->pCouche[1]->ui16NbNeurones; i++)
    {
        pReseau->pCouche[1]->pNeur[i] = instancie_neurone(NB_NEURONES_COUCHE_1);
    }
    return pReseau;
}

