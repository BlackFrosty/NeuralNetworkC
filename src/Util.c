
double PixelMax(double *ptrTab, int iDep, int jDep){
    double dMaxPixel ; 

    for (int i = 1 ; i < 3 ; i++ ){
        for (int j = 1 ; j < 3 ; j++){
            if (ptrTab[iDep+i][jDep+j] > dMaxPixel){
                dMaxPixel = ptrTab[iDep+i][jDep+j] ;
            }//fin if
        }// fin for
    }// fin for 

    return dMaxPixel ;
}// fin PixelMax

double MaxPooling (double adTabPixel[][], int iNbElementTabPixel){
    double adTabMaxPooling [NB_ELEMENT_MAX_POOLINIG][NB_ELEMENT_MAX_POOLINIG];
    
    for (int i = 0 ; i <NB_ELEMENT_MAX_POOLINIG ; i++ ){ 
        for (int j = 0 ; j <NB_ELEMENT_MAX_POOLINIG ; j++){
            adTabMaxPooling[i][j] = PixelMax(adTabPixel, i , j);
        }
    }
    return adTabMaxPooling ;
}// fin MAxPooling

