//
// Created by tmdt2021 on 21/06/2021.
//

#include "structures.h"
#include "functionsIO.h"
#include "fonctionsRso.h"
#include "Util.h"

void entrainer(T_RSO* pReseau , T_BITMAP * paBitmap)
{
    uint32_t ui32NbBitmap;
    printf("paBitmap = %p\n", paBitmap);
    printf("pReseau = %p\n", pReseau);

    // Lire le fichier d'images
    paBitmap = readImageFile(FIC_IMAGES, &ui32NbBitmap, paBitmap);

    // Lire les labels
    readLabelFile(FIC_LABEL, &ui32NbBitmap, paBitmap);

    // Lire le fichier de poids
    LirePoids(FIC_POIDS, pReseau);

    // propager
    printf("Avant Propager\n");
    propager(pReseau,paBitmap, ui32NbBitmap);

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


    //libere_cascade(pReseau);
}
