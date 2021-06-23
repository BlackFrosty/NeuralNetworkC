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
    /*for (int i = 0; i < ui32NbBitmap; i++)
    {
        printf("HxL bitmap: %d %d\n", paBitmap[i].ui32HauteurOriginal, paBitmap[i].ui32LargeurOriginal);
    }*/
    // Lire les labels

    readLabelFile(FIC_LABEL, &ui32NbBitmap, paBitmap);
    // Lire le fichier de poids

    /*printf("Avant LirePoids\n");*/

    LirePoids(FIC_POIDS, pReseau);


    /*for (int i = 1; i < 66; i++)
    {
        printf("Poids: %lf\n", pReseau->pCouche[0].pNeur[i].pdPoids[1]);
    }*/
    // propager
    printf("Avant Propager\n");
    propager(pReseau,paBitmap, ui32NbBitmap);

    /*for (int i = 0 ; i < 10 ; i++)
    {
        //printf("%lf\n", paBitmap[i].pTabPixelOriginal[14][14]);
        afficherImage(&paBitmap[i]);
        //printf("paBitmap = %p\n", &paBitmap[i]);

    }*/

}

int main(int argc, char ** argv)
{
    //static double adTabPixel[NB_ELEMENTS_BMP][NB_ELEMENTS_BMP] ;
    T_RSO * pReseau;
    T_BITMAP * paBitmap;
    //adTabPixel = readImageFile("../data/numbers/train-images-idx3-ubyte");
    //MaxPooling (adTabPixel, NB_ELEMENTS_BMP);

    pReseau = init_rso_neurones(NB_COUCHES);


    entrainer(pReseau, paBitmap);



    //libere_cascade(pReseau);
}
