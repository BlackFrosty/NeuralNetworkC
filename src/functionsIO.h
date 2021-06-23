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
    T_BITMAP *        readImageFile(char * pcFileLocation, uint32_t * pui32NbBitmaps, T_BITMAP * strBitmaps);
    void        readLabelFile(char * pcFileLocation, uint32_t * pui32NbBitmaps, T_BITMAP * pstrBitmaps);
    FILE *      openFile (char * pcFileLocation);
    uint32_t    swapEndians (uint32_t ui8num);
    uint32_t    checkMagicNumber (FILE * iImageFD, uint32_t ui8MagicNumber );

#endif



