#ifndef FUNCTIONSIO_H
#define FUNCTIONSIO_H

    //taille en octet de la clé magique dans le fichier d'entrée
    #define MAGIC_NUMBER_SIZE       4

    //magic key identification for Image & Label files
    #define MAGIC_NUMBER_IMG        2051
    #define MAGIC_NUMBER_LBL        2049
    
    //nombre de lignes et de colonnes d'une image du fichier bitmap
    #define NB_LIGNES_BMP           28
    #define NB_COLONNES_BMP         28
    
    //nombre maximum de lignes à lire dans le fichier d'apprentissage
    #define NB_ENTREES_APPR         60000

#endif