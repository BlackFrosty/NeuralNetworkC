#include <math.h>

double** MaxPooling (double adTabPixel[][], int iNbElementTabPixel){
    static double adTabMaxPooling [NB_ELEMENT_MAX_POOLINIG][NB_ELEMENT_MAX_POOLINIG];
    int x = 0 ;
    int y = 0;
    
    for (int i = 1 ; i < iNbElementTabPixel - 1 ; i+2){
        for (int j=  1 ; j < iNbElementTabPixel - 1 ; j+2){
            adTabMaxPooling[x][y] = fmax(adTabPixel[i][j], adTabPixel[i+1][j]) ;
            if (adTabMaxPooling[x][y] < fmax(adTabPixel[i][j+1],adTabPixel[i+1][j+1] ) {
                adTabMaxPooling[x][y] = fmax(adTabPixel[i][j+1],adTabPixel[i+1][j+1] ;
            }
            if (y <13) {
                y += 1 ;
            }else {
                y = 0
            }
        }
    x += 1 ;
    }

    return adTabMaxPooling ;
}// fin MAxPooling
