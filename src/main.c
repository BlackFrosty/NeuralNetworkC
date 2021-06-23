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
    // Lire le fichier d'images
    readImageFile(FIC_IMAGES, &ui32NbBitmap, paBitmap);
    for (int i = 0; i < ui32NbBitmap; i++)
    {
        printf("Hauteur bitmap: %lf\n", paBitmap[i].ui32HauteurOriginal);
    }
    // Lire les labels
    // Lire le fichier de poids
    //LirePoids(FIC_POIDS, pReseau);
    // propager
    //propager(pReseau,paBitmap, ui32NbBitmap);


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



    libere_cascade(pReseau);
}
