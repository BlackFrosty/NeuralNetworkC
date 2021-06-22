#ifndef FUNCTIONSIO_H
#define FUNCTIONSIO_H

    //taille en octet de la clé magique dans le fichier d'entrée
    #define MAGIC_NUMBER_SIZE       4

    //magic key identification for Image & Label files
    #define MAGIC_NUMBER_IMG        2051
    #define MAGIC_NUMBER_LBL        2049
    
    //nombre de lignes et de colonnes d'une image du fichier bitmap
    #define NB_ELEMENTS_BMP           28
    
    //nombre maximum de lignes à lire dans le fichier d'apprentissage
    #define NB_ENTREES_APPR         60000

    //nombre maximum de lignes à lire dans le fichier de test
    #define NB_ENTREES_TEST     10000

    //taille en octet d'un bloc à lire dans les fichiers d'entrée
    #define TAILLE_BLOC         4

    #define CLE_MAGIQUE_IMG    2051
    #define CLE_MAGIQUE_TST     2049

    //fonction ouvrant un fichier image et renvoyant un tableau de tableau avec la valeur de chaque pixel
    double**    readImageFile(char * pcFileLocation) ;

#endif



