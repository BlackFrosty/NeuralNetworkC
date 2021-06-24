//
// Created by tmdt2021 on 21/06/2021.
//

#include "structures.h"
#include "functionsIO.h"
#include "fonctionsRso.h"
#include "Util.h"
#include "calculs.h"

void entrainer(T_RSO* pReseau , T_BITMAP * paBitmap)
{
    uint32_t ui32NbBitmap;
    T_STAT stat = {0};
    double dErreurMoyenne = 0., dErreur;
    int iOccurences = 1;

    printf("paBitmap = %p\n", paBitmap);
    printf("pReseau = %p\n", pReseau);

    // Lire le fichier d'images
    paBitmap = readImageFile(FIC_IMAGES, &ui32NbBitmap, paBitmap);

    // Lire les labels
    readLabelFile(FIC_LABEL, &ui32NbBitmap, paBitmap);

    // Lire le fichier de poids
    LirePoids(FIC_POIDS, pReseau);
    //initPoids(pReseau);

    /*for (int i = 0 ; i < 10 ; i++)
    {
        for (int j = 0 ; j < 66 ; j++)
        {
            printf("Poids(%d)(%d) : %lf\n", i, j, pReseau->pCouche[1].pNeur[i].pdPoids[j]);
        }
        printf("\n");
    }*/
    // propager
    //printf("Avant Propager\n");
    for (int i = 0 ; i < iOccurences ; i++)
    {
        dErreur = propager(pReseau, paBitmap, ui32NbBitmap, &stat);
        dErreurMoyenne += dErreur;
        printf("Erreur à l'occurence %d : %lf\n", i+1, dErreur);
    }
    printf("Erreur moyenne totale après %d occurences : %lf\n", iOccurences, dErreurMoyenne/iOccurences);

}

int main(int argc, char ** argv)
{
    //
    T_RSO * pReseau;
    T_BITMAP * paBitmap;

    // Instanciation du réseau
    pReseau = init_rso_neurones(NB_COUCHES);
    // Apprentissage
    entrainer(pReseau, paBitmap);
    printf("Avec retropropagation\n");

    //libere_cascade(pReseau);
}
