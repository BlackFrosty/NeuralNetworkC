//
// Created by tmdt2021 on 21/06/2021.
//

#include "structures.h"
#include "FunctionsIO.h"

int main(int argc, char ** argv)
{
  static double adTabPixel[NB_ELEMENTS_BMP][NB_ELEMENTS_BMP] ;
  adTabPixel = readImageFile("../data/numbers/train-images-idx3-ubyte"); 
  MaxPooling (adTabPixel);
  
}
