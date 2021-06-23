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
    ui32res = swapEndians (ui32res);
    
    //Check with provided Magic Number
    if (ui32res == ui32MagicNumber) {return 1;}
    return 0;
}

//Open file and check 
FILE*       openFile (char * pcFileLocation) {
    //open file (b option is added to indicate binary mode for non-UNIX system)
    FILE * f = fopen(pcFileLocation, "rb");

    if (f == NULL) {
	    fprintf(stderr, "Impossible d'ouvrir le fichier d'entrees '%s'.\n", pcFileLocation);
		exit(EXIT_FAILURE);
	}
}

//
void    readImageFile(char * pcFileLocation, uint32_t * pui32NbBitmaps, T_BITMAP * pstrBitmaps) {
    //Open Image file
    FILE * fpImageFD = openFile(pcFileLocation);
    
    //Lecture et contrôle de la "clé" magique
	if (checkMagicNumber(fpImageFD, MAGIC_NUMBER_IMG)) {
        perror("Erreur : la clé magique ne correspond pas au type image.");
        exit(EXIT_FAILURE);
    }
    
    //Lecture et sauvegarde du nombre de bitmaps  
    if (fread(pui32NbBitmaps, 4, 1, fpImageFD) != 1) {
        perror("Erreur : le nombre de bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    * pui32NbBitmaps = swapEndians(* pui32NbBitmaps);

    //Lecture et sauvegarde de la largeur des images
	uint32_t ui32LargeurBitmap = 0;
    if (fread(&ui32LargeurBitmap, 4, 1, fpImageFD) != 1) {
        perror("Erreur : la largeur des bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui32LargeurBitmap = swapEndians(ui32LargeurBitmap);
    
    //Lecture et sauvegarde de la heuteur des images
	uint8_t ui32HauteurBitmap = 0;
    if (fread(&ui32HauteurBitmap, 4, 1, fpImageFD) != 1) {
        perror("Erreur : la longueur des bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui32HauteurBitmap = swapEndians(ui32HauteurBitmap);

    //initialiser la structure à rendre (type T_BITMAP) et les variables de hauteur/largeur
    // T_BITMAP    strBitmaps[* pui32NbBitmaps];
    // for (uint32_t ui32BitmapPosition = 0; ui32BitmapPosition < (* pui32NbBitmaps); ui32BitmapPosition++) {
    //     strBitmaps[ui32BitmapPosition] = * instancie_bitmap(ui32HauteurBitmap, ui32LargeurBitmap, (uint32_t) 13, (uint32_t) 13, 255);
    // }

    //Parcourir l'image
    for (uint32_t ui32ImagePosition = 0; ui32ImagePosition < (* pui32NbBitmaps); ui32ImagePosition++) {
        //initialize pImageBuffer
        double ** pImageBuffer = (double **) malloc (ui32HauteurBitmap * sizeof(double*));
        // TODO : Instancier la matrice en 2 temps
        // TODO : Transformer en fonction
        
        for (uint32_t ui32Row = 0; ui32Row < ui32HauteurBitmap; ui32Row++)
        {
            pImageBuffer[ui32Row] = (double *) malloc (ui32LargeurBitmap  * sizeof(double));
        }
        //double ** pImageBuffer = (double **) malloc ((* pui8LargeurBitmap) * (* pui8HauteurBitmap) * sizeof(double));
        
        //remplissage du tableau pImageBuffer avec chaque pixels lu       
        for (uint32_t ui32Row = 0; ui32Row < ui32HauteurBitmap; ui32Row++) {
                //Lecture d'une entrée de 1 octets
                if (fread(pImageBuffer[ui32Row], 28, 1, fpImageFD) != 1) {
                    perror("Erreur : La lecture des pixels dans le fichier d'entree a échoué.");
                    exit(EXIT_FAILURE);
                }
        }
        pstrBitmaps[ui32ImagePosition].pTabPixelOriginal = pImageBuffer;
        free(pImageBuffer);
    }

    //fermeture du fichier d'entrées
	fclose(fpImageFD);
}

void    readLabelFile(char * pcFileLocation, uint32_t * pui32NbBitmaps, T_BITMAP * pstrBitmaps) {
    //Read Image file
    FILE * fpLabelFD = openFile(pcFileLocation);
    
    //Lecture et contrôle de la "clé" magique
	if (checkMagicNumber(fpLabelFD, MAGIC_NUMBER_LBL)) {
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