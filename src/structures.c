//
// Created by tmdt2021 on 21/06/2021.
//

/**
 * structures.c
 * Contient les fonctions nécessaires à l'instanciation des structures utilisés par le réseau de neurones
 *
 */

#include <stdio.h>  // printf
#include <stdlib.h> // calloc,malloc,free
#include <unistd.h>
#include "structures.h"

/**
 * instancie_neurone
 * Crée le tableau de poids propre au neurone
 * @param pNeur : Pointeur sur un neurone
 * @param ui16NbDendrites : Nombre de dendrites d'entrées (et donc de poids correspondant à instancier)
 */
void instancie_neurone(T_NEURONE * pNeur, uint16_t ui16NbDendrites)
{
    pNeur->ui16NbDendrites = ui16NbDendrites;
    pNeur->pdPoids = calloc(ui16NbDendrites, sizeof(double ));
    if (pNeur->pdPoids == NULL)
    {
        perror("Echec de l'instantation des poids d'un neurone");
    }
}

/**
 * libere_neurone : Libère le tableau de poids réservé par instancie_neurone
 * @param pNeur : Neurone à libérer de poids
 */
void libere_neurone(T_NEURONE * pNeur)
{
    free(pNeur->pdPoids);
    pNeur->pdPoids = NULL;
}

void instancie_couche(T_COUCHE * pCouche, uint16_t ui16NbNeurones)
{
    pCouche->ui16NbNeurones = ui16NbNeurones;
    pCouche->pNeur = calloc(pCouche->ui16NbNeurones, sizeof(T_NEURONE));
    if (pCouche->pNeur == NULL)
    {
        perror("Echec d'instanciation des neurones d'une couche");
        exit(EXIT_FAILURE);
    }
    /*else
    {
        printf("Instanciation des neurones d'une couche\n");
    }*/
}
void libere_couche(T_COUCHE * pCouche)
{
    free(pCouche->pNeur);
    pCouche->pNeur = NULL;
}

/**
 * instancie_rso : Crée la variable du réseau de neurones, et réserve la mémoire pour le tableau de couches
 * @param ui8NbCouches : Nombre de couches à instancier
 * @return pointeur sur le réseau de neurones (T_RSO *)
 */
T_RSO * instancie_rso(uint8_t ui8NbCouches)
{
    static T_RSO rso;
    rso.ui8NbCouches = ui8NbCouches;
    rso.pCouche = calloc(rso.ui8NbCouches, sizeof(T_COUCHE));
    if (rso.pCouche == NULL)
    {
        perror("Echec d'instanciation des couches");
        exit(EXIT_FAILURE);
    }
    return &rso;
}

void libere_rso(T_RSO * rso)
{

}

/**
 * libere_cascade : Libération récursive des emplacements mémoire liés au réseau de neurones
 * @param pRso : Pointeur sur le réseau de neurones
 */
void libere_cascade(T_RSO *pRso)
{
    /* Pour chaque couche, libération récursive des neurones et de leurs poids synaptiques */
    for (uint8_t iNbC = 0 ; iNbC < pRso->ui8NbCouches; iNbC++)
    {
        /* Pour chaque neurone de la couche */
        for (uint16_t iNbN = 0 ; iNbN < pRso->pCouche[iNbC].ui16NbNeurones; iNbN++)
        {
            libere_neurone(&(pRso->pCouche[iNbC].pNeur[iNbN]));
        }
        libere_couche(&(pRso->pCouche[iNbC]));
    }
    //libere_rso(pRso)
}

/**
 * init_rso_neurones : crée statiquement le réseau de neurones
 * @param ui8NbCouches : nombre de couches à instancier
 *
 */
T_RSO * init_rso_neurones(uint8_t ui8NbCouches)
{
    T_RSO * pReseau ;
    /* instanciation du réseau */
    pReseau = instancie_rso((ui8NbCouches));

    /* instanciation des couches */
    instancie_couche(&(pReseau->pCouche[0]), NB_NEURONES_COUCHE_CACHEE);
    /* instanciation différenciée de la couche 0 */
    for (uint16_t i = 0 ; i < pReseau->pCouche[0].ui16NbNeurones; i++)
    {
        instancie_neurone(&(pReseau->pCouche[0].pNeur[i]), NB_DENDRITES_INIT);
    }
    instancie_couche(&(pReseau->pCouche[1]), NB_NEURONES_COUCHE_SORTIE);
    /* instanciation différenciée de la couche 1 */
    for (uint16_t i = 0 ; i < pReseau->pCouche[1].ui16NbNeurones; i++)
    {
        instancie_neurone(&(pReseau->pCouche[1].pNeur[i]), NB_NEURONES_COUCHE_CACHEE);
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
    // Instanciation de la structure et réservation de la mémoire associée
    pBmp = calloc(1, sizeof(T_BITMAP));
    if (pBmp == NULL)
    {
        perror("Echec de l'instanciation d'un T_BITMAP");
        exit(EXIT_FAILURE);
    }
    else
    {
        /* initialisation des membres de la structure */
        pBmp->ui32HauteurOriginal = ui32HauteurOrig;
        pBmp->ui32LargeurOriginal = ui32LargeurOrig;
        pBmp->ui32HauteurMaxP = ui32HauteurMaxP;
        pBmp->ui32LargeurMaxP = ui32LargeurMaxP;
        /* Réservation de la mémoire pour le tableau de taille initiale, en 2 phases */
        pBmp->pTabPixelOriginal = calloc(pBmp->ui32HauteurOriginal, sizeof (double*));
        if (pBmp->pTabPixelOriginal == NULL)
        {
            perror("Echec de l'instanciation d'un double ** de T_BITMAP");
            exit(EXIT_FAILURE);
        }
        for (int i = 0 ; i < pBmp->ui32HauteurOriginal; i++)
        {
            pBmp->pTabPixelOriginal[i] = calloc(pBmp->ui32LargeurOriginal, sizeof(double));
            if (pBmp->pTabPixelOriginal[i] == NULL)
            {
                perror("Echec de l'instanciation d'un double ** de T_BITMAP");
                exit(EXIT_FAILURE);
            }
        }
        /* Réservation de la mémoire pour le tableau maxpoolé, en 2 phases */
        pBmp->pTabPixelMaxP = calloc(pBmp->ui32HauteurMaxP, sizeof (double*));
        if (pBmp->pTabPixelMaxP == NULL)
        {
            perror("Echec de l'instanciation d'un double ** de T_BITMAP");
            exit(EXIT_FAILURE);
        }
        for (int i = 0 ; i < pBmp->ui32HauteurMaxP; i++)
        {
            pBmp->pTabPixelMaxP[i] = calloc(pBmp->ui32LargeurMaxP, sizeof(double));
            if (pBmp->pTabPixelMaxP[i] == NULL)
            {
                perror("Echec de l'instanciation d'un double ** de T_BITMAP");
                exit(EXIT_FAILURE);
            }
        }
        pBmp->label = enLabel;
    }

    return pBmp;
}

/**
 * Instancie un tableau de bitmap dont le nombre et le pointeur sur ce tableau sont fournis en paramètres
 * @param pBmp : pointeur vers le tableau
 * @param ui32Count : Nombre d'éléments du tableau à instancier
 */
T_BITMAP * instancie_tab_bitmap(T_BITMAP * pBmp, uint32_t ui32Count)
{
    //printf("nb Bitmaps %d\n", ui32Count);
    pBmp = calloc(ui32Count, sizeof(T_BITMAP));
    if (pBmp == NULL)
    {
        perror("Echec de l'instanciation du tableau de T_BITMAP\n");
        exit(EXIT_FAILURE);
    }
    /*else
    {
        printf("Instanciation d'un tableau de %d T_BITMAP\n", ui32Count);
    }*/
    return pBmp;
}
