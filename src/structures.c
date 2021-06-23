//
// Created by tmdt2021 on 21/06/2021.
//

#include <stdio.h>
#include <stdlib.h> // calloc,malloc,free
#include "structures.h"

void instancie_neurone(T_NEURONE * pNeur, uint16_t ui16NbDendrites)
{
    pNeur->ui16NbDendrites = ui16NbDendrites;
    //printf("Neurone av : %p\n", pNeur->pdPoids);
    pNeur->pdPoids = calloc(ui16NbDendrites, sizeof(double ));
    //printf("Neurone ap : %p\n", pNeur->pdPoids);
}

void libere_neurone(T_NEURONE * pNeur)
{
    free(pNeur->pdPoids);
    pNeur->pdPoids = NULL;
    //free(pNeur);
    //pNeur = NULL;
}

void instancie_couche(T_COUCHE * pCouche, uint16_t ui16NbNeurones)
{
    pCouche->ui16NbNeurones = ui16NbNeurones;
    pCouche->pNeur = calloc(pCouche->ui16NbNeurones, sizeof(T_NEURONE));
}

void libere_couche(T_COUCHE * pCouche)
{
    free(pCouche->pNeur);
    pCouche->pNeur = NULL;
}

T_RSO * instancie_rso(uint8_t ui8NbCouches)
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
        for (uint16_t iNbN = 0 ; iNbN < pRso->pCouche[iNbC].ui16NbNeurones; iNbN)
        {
            libere_neurone(&(pRso->pCouche[iNbC].pNeur[iNbN]));
        }
        libere_couche(&(pRso->pCouche[iNbC]));
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
    instancie_couche(&(pReseau->pCouche[0]), NB_NEURONES_COUCHE_1);
    /* instanciation différenciée de la couche 0 */
    for (uint16_t i = 0 ; i < pReseau->pCouche[0].ui16NbNeurones; i++)
    {
        instancie_neurone(&(pReseau->pCouche[0].pNeur[i]), NB_DENDRITES_INIT);
    }
    instancie_couche(&(pReseau->pCouche[1]), NB_NEURONES_COUCHE_2);
    /* instanciation différenciée de la couche 1 */
    for (uint16_t i = 0 ; i < pReseau->pCouche[1].ui16NbNeurones; i++)
    {
        instancie_neurone(&(pReseau->pCouche[1].pNeur[i]), NB_NEURONES_COUCHE_1);
    }
    return pReseau;
}

/**
 * instancie_bitmap : alloue l'espace pour le tbitmap
 *
 * */
T_BITMAP * instancie_bitmap(
        uint32_t ui32HauteurOrig,
        uint32_t ui32LargeurOrig,
        uint32_t ui32HauteurMaxP,
        uint32_t ui32LargeurMaxP,
        enumLabel enLabel)
{
    T_BITMAP * pBmp;
    pBmp = calloc(1, sizeof(T_BITMAP));
    if (pBmp == NULL)
    {
        perror("Echec de l'instanciation d'un T_BITMAP");
    }
    else
    {
        pBmp->ui32HauteurOriginal = ui32HauteurOrig;
        pBmp->ui32LargeurOriginal = ui32LargeurOrig;
        pBmp->ui32HauteurMaxP = ui32HauteurMaxP;
        pBmp->ui32LargeurMaxP = ui32LargeurMaxP;
        pBmp->pTabPixelOriginal = calloc(pBmp->ui32HauteurOriginal, sizeof (double*));
        for (int i = 0 ; i < pBmp->ui32HauteurOriginal; i++)
        {
            pBmp->pTabPixelOriginal[i] = calloc(pBmp->ui32LargeurOriginal, sizeof(double));
        }
        pBmp->pTabPixelMaxP = calloc(pBmp->ui32HauteurMaxP, sizeof (double*));
        for (int i = 0 ; i < pBmp->ui32HauteurMaxP; i++)
        {
            pBmp->pTabPixelMaxP[i] = calloc(pBmp->ui32LargeurMaxP, sizeof(double));
        }
        pBmp->label = enLabel;
    }

    return pBmp;
}
