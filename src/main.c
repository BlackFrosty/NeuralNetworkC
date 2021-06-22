//
// Created by tmdt2021 on 21/06/2021.
//

#include "structures.h"

int main(int argc, char ** argv)
{
  static double adTabPixel[NB_ELEMENTS_BMP][NB_ELEMENTS_BMP] ;
  adTabPixel = (readImageFile() ; NB_ELEMENTS_BMP); 
  MaxPooling (adTabPixel);
  
}
