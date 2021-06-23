//
// Created by tmdt2021 on 21/06/2021.
//

#include "structures.h"
#include "functionsIO.h"

int main(int argc, char ** argv)
{
      //static double adTabPixel[NB_ELEMENTS_BMP][NB_ELEMENTS_BMP] ;
      T_RSO * pReseau;
      //adTabPixel = readImageFile("../data/numbers/train-images-idx3-ubyte");
      //MaxPooling (adTabPixel, NB_ELEMENTS_BMP);

      pReseau = init_rso_neurones(NB_COUCHES);
    libere_cascade(pReseau);
}
