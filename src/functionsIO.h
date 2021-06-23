#ifndef FUNCTIONSIO_H
#define FUNCTIONSIO_H

    #include <stdio.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include "structures.h"
    #include "Util.h"

    //magic key identification for Image & Label files
    #define MAGIC_NUMBER_IMG        (uint32_t)2051
    #define MAGIC_NUMBER_LBL        (uint32_t)2049

    //fonction ouvrant un fichier image et renvoyant un tableau de tableau avec la valeur de chaque pixel
    T_BITMAP    readImageFile(char * pcFileLocation, uint8_t bMaxPooling);
    void        readLabelFile(char * pcFileLocation, T_BITMAP * pstrBitmap);
    FILE *      openFile (char * pcFileLocation);
    uint8_t     swapEndians (uint8_t ui8num);
    uint8_t     checkMagicNumber (FILE * iImageFD, uint8_t ui8MagicNumber );

#endif



