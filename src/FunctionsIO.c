#include <stdio.h>

void    readImageFile(char * pcFileLocation, double * padPixels) {
    //open file
    FILE * f = fopen(pcFileLocation, "r");

    //open file
    FILE * f = openFileOfType(pcFileLocation, MAGIC_NUMBER_IMG)
}

void    readLabelFile(char * pcFileLocation, T_BITMAP * pbmpBitmap) {
    //open file
    FILE * f = fopen(pcFileLocation, "r");

    //open file
    FILE * f = openFileOfType(pcFileLocation, MAGIC_LABEL_IMG)
}