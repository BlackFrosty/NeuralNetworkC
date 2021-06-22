#include "functionsIO.h"

//Swap a value from big Endian to little Endian (or vice versa)
uint8_t     swapEndians (uint8_t ui8num) {
    //register suggests the system to use register as a memory instead of RAM
    //shift and filter to swap all 4 bytes
    register uint8_t result = ( ((ui8num >> 24) & 0xff) | ((ui8num << 8) & 0xff0000) | ((ui8num >> 8) & 0xff00) | ((ui8num << 24) & 0xff000000) );

    return result;
}

//
uint8_t     checkMagicNumber (FILE * fpImageFD, uint8_t ui8MagicNumber ) {
    //
    uint8_t ui8res = 0;
    if (fread(&ui8res, 4, 1, fpImageFD) != 1) {
        perror("Erreur de lecture d'entier dans le fichier d'entree.");
        exit(EXIT_FAILURE);
    }
    ui8res = swapEndians (ui8res);
    
    //
    if (ui8res == ui8MagicNumber) {return 1;}
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

T_BITMAP    readImageFile(char * pcFileLocation, uint8_t bMaxPooling) {
    //Read Image file
    FILE * fpImageFD = openFile(pcFileLocation);
    
    //Lecture et contrôle de la "clé" magique
	if (checkMagicNumber(fpImageFD, MAGIC_NUMBER_IMG)) {
        perror("Erreur : la clé magique ne correspond pas au type image.");
        exit(EXIT_FAILURE);
    }
    
    //Lecture et sauvegarde du nombre de bitmaps
    uint8_t ui8NbBitmaps = 0;
    if (fread(&ui8NbBitmaps, 4, 1, fpImageFD) != 1) {
        perror("Erreur : le nombre de bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui8NbBitmaps = swapEndians(ui8NbBitmaps);

    //Lecture et sauvegarde de la largeur des images
	uint8_t ui8LargeurBitmap = 0;
    if (fread(&ui8LargeurBitmap, 4, 1, fpImageFD) != 1) {
        perror("Erreur : la largeur des bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui8LargeurBitmap = swapEndians(ui8LargeurBitmap);
    
    //Lecture et sauvegarde de la heuteur des images
	uint8_t ui8HauteurBitmap = 0;
    if (fread(&ui8HauteurBitmap, 4, 1, fpImageFD) != 1) {
        perror("Erreur : la longueur des bitmaps n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui8HauteurBitmap = swapEndians(ui8HauteurBitmap);
    
    //initialiser la structure à rendre (type T_BITMAP) et les variables de hauteur/largeur
    static T_BITMAP pstrBitmap = instancie_bitmap(ui8NbBitmaps, ui8LargeurBitmap, ui8HauteurBitmap, bMaxPooling);

    for (uint8_t ui8ImagePosition = 0; ui8ImagePosition < ui8NbBitmaps; ui8ImagePosition++) {
        //remplissage du tableau pTabPixel avec les pixels lus
        double ** pImage = (double **) malloc (ui8LargeurBitmap * ui8HauteurBitmap * sizeof(double));
        for (uint8_t ui8Row = 0; ui8Row < ui8HauteurBitmap; ui8Row++) {
            for (uint8_t ui8Column = 0; ui8Column < ui8LargeurBitmap; ui8Column++) {
                //Lecture d'une entrée de 1 octets 
                if (fread(&pImage[ui8Row][ui8Column], 1, 1, fpImageFD) != 1) {
                    perror("Erreur : La lecture d'un pixel (octet) dans le fichier d'entree a échoué.");
                    exit(EXIT_FAILURE);
                }
            }
        }
        
        pImage = MaxPooling(pImage, ui8LargeurBitmap);
        pstrBitmap->pTabPixel[ui8ImagePosition] = pImage;
    }

    //fermeture du fichier d'entrées
	fclose(fpImageFD);

    return pstrBitmap ;
}

void    readLabelFile(char * pcFileLocation, T_BITMAP * pstrBitmap) {
    //Read Image file
    FILE * fpImageFD = openFile(pcFileLocation);
    
    //Lecture et contrôle de la "clé" magique
	if (checkMagicNumber(fpImageFD, MAGIC_NUMBER_LBL)) {
        perror("Erreur : la clé magique ne correspond pas au type label.");
        exit(EXIT_FAILURE);
    }
    
    //Lecture et sauvegarde du nombre de labels
    uint8_t ui8NbLabels = 0;
    if (fread(&ui8NbLabels, 4, 1, fpImageFD) != 1) {
        perror("Erreur : le nombre de labels n'est pas lisible.");
        exit(EXIT_FAILURE);
    }
    ui8NbLabels = swapEndians(ui8NbLabels);
}