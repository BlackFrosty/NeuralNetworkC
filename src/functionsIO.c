#include "functionsIO.h"

//Swap a value from big Endian to little Endian (or vice versa)
uint32_t     swapEndians (uint32_t ui32num) {
    //register suggests the system to use register as a memory instead of RAM
    //shift and filter to swap all 4 bytes
    register uint32_t result = ( ((ui32num >> 24) & 0xff) | ((ui32num << 8) & 0xff0000) | ((ui32num >> 8) & 0xff00) | ((ui32num << 24) & 0xff000000) );
    return result;
}

//Check MagicNumber with given number
uint32_t     checkMagicNumber (FILE * fpImageFD, uint32_t ui32MagicNumber ) {
    //
    uint32_t ui32res = 0;
    if (fread(&ui32res, 4, 1, fpImageFD) != 1) {
        perror("Erreur de lecture d'entier dans le fichier d'entree.");
        exit(EXIT_FAILURE);
    }
    //printf("Magic av : %x %ld\n", ui32res, ui32res);
    ui32res = swapEndians (ui32res);
    //rintf("Magic ap : %x %ld\n", ui32res, ui32res);
    //Check with provided Magic Number
    if (ui32res == ui32MagicNumber)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//Open file and check 
FILE*       openFile (char * pcFileLocation) {
    //open file (b option is added to indicate binary mode for non-UNIX system)
    FILE * f = fopen(pcFileLocation, "rb");

    if (f == NULL) {
	    fprintf(stderr, "Impossible d'ouvrir le fichier d'entrees '%s'.\n", pcFileLocation);
		exit(EXIT_FAILURE);
	}
    return f;
}

//
T_BITMAP *   readImageFile(char * pcFileLocation, uint32_t * pui32NbBitmaps, T_BITMAP * pstrBitmaps) {
    //Open Image file
    FILE * fpImageFD = openFile(pcFileLocation);
    uint8_t ui8Buffer;
    //printf("paBitmap = %p\n", pstrBitmaps);
    //Lecture et contrôle de la "clé" magique

    //printf("%d %x\n", iBool, iBool);
	if (! checkMagicNumber(fpImageFD, MAGIC_NUMBER_IMG)) {
        perror("Erreur : la clé magique ne correspond pas au type image.");
        exit(EXIT_FAILURE);
    }
    
    //Lecture et sauvegarde du nombre de bitmaps  
    if (fread(pui32NbBitmaps, 4, 1, fpImageFD) != 1) {
        perror("Erreur : le nombre de bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    * pui32NbBitmaps = swapEndians(* pui32NbBitmaps);
    //printf("Nombre de bitmaps : %d, p %p\n", *pui32NbBitmaps, pui32NbBitmaps);

    pstrBitmaps = instancie_tab_bitmap(pstrBitmaps, * pui32NbBitmaps );
    //printf("paBitmap = %p\n", pstrBitmaps);

    //Lecture et sauvegarde de la largeur des images
	uint32_t ui32LargeurBitmap = 0;
    if (fread(&ui32LargeurBitmap, 4, 1, fpImageFD) != 1) {
        perror("Erreur : la largeur des bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui32LargeurBitmap = swapEndians(ui32LargeurBitmap);

    //Lecture et sauvegarde de la heuteur des images
	uint32_t ui32HauteurBitmap = 0;
    if (fread(&ui32HauteurBitmap, 4, 1, fpImageFD) != 1) {
        perror("Erreur : la longueur des bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui32HauteurBitmap = swapEndians(ui32HauteurBitmap);
    //printf("Position: %d\n", ftell(fpImageFD));
    //printf("Dimensions : %d x %d\n", ui32HauteurBitmap, ui32LargeurBitmap);

    //initialiser la structure à rendre (type T_BITMAP) et les variables de hauteur/largeur
    for (uint32_t ui32BitmapPosition = 0; ui32BitmapPosition < (* pui32NbBitmaps); ui32BitmapPosition++) {
        //printf("%d ", ui32BitmapPosition);
        pstrBitmaps[ui32BitmapPosition] = * instancie_bitmap(ui32HauteurBitmap, ui32LargeurBitmap, (uint32_t) 13, (uint32_t) 13, 255);
        //printf("%d %d\n", pstrBitmaps[ui32BitmapPosition].ui32HauteurOriginal, pstrBitmaps[ui32BitmapPosition].ui32LargeurOriginal);
    }
    printf("Tout est instancié\n");

    //Parcourir les images
    for (uint32_t ui32ImagePosition = 0; ui32ImagePosition < (* pui32NbBitmaps); ui32ImagePosition++) {
        
        //Pour chaque image, remplissage du tableau pixel par pixel       
        for (uint32_t ui32Row = 0; ui32Row < ui32HauteurBitmap; ui32Row++) {
            //Lecture d'une entrée de 1 octets
            for (uint32_t ui32Column = 0; ui32Column < ui32LargeurBitmap; ui32Column++) {
                if (fread(&ui8Buffer, 1, 1, fpImageFD) != 1) {
                    perror("Erreur : La lecture des pixels dans le fichier d'entree a échoué.");
                    exit(EXIT_FAILURE);
                }
                else {
                    pstrBitmaps[ui32ImagePosition].pTabPixelOriginal[ui32Row][ui32Column] = (double) ui8Buffer;
                }
            }
        }
        
        //Application de la fonction Maxpooling pour remplir pTabPixelMaxP à partir de l'image lue.
        MaxPooling(&(pstrBitmaps[ui32ImagePosition]));
    }
    printf("Avant le fclose\n");
    //fermeture du fichier d'entrées
	fclose(fpImageFD);

    return pstrBitmaps;
}

void    readLabelFile(char * pcFileLocation, uint32_t * pui32NbBitmaps, T_BITMAP * pstrBitmaps) {
    //Read Image file
    FILE * fpLabelFD = openFile(pcFileLocation);
    
    //Lecture et contrôle de la "clé" magique
	if (!checkMagicNumber(fpLabelFD, MAGIC_NUMBER_LBL)) {
        perror("Erreur : la clé magique ne correspond pas au type label.");
        exit(EXIT_FAILURE);
    }
    
    //Lecture et sauvegarde du nombre de labels
    uint32_t ui32NbLabels = 0;
    if (fread(&ui32NbLabels, 4, 1, fpLabelFD) != 1) {
        perror("Erreur : le nombre de labels n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui32NbLabels = swapEndians(ui32NbLabels);

    //Check if number of labels equals number of images
    if ((* pui32NbBitmaps) != ui32NbLabels) {
        perror("Erreur : le nombre de labels ne correspond pas au nombre d'images.");
        exit(EXIT_FAILURE);
    }

    //Lecture et sauvegarde des labels     
    for (uint32_t ui32Position = 0; ui32Position < ui32NbLabels; ui32Position++) {
        //Lecture d'une entrée de 1 octets 
        if (fread(&(pstrBitmaps[ui32Position].label), 1, 1, fpLabelFD) != 1) {
            perror("Erreur : La lecture d'un label (octet) dans le fichier d'entree a échoué.");
            exit(EXIT_FAILURE);
        }
    }
    
    //fermeture du fichier d'entrées
	fclose(fpLabelFD);

}