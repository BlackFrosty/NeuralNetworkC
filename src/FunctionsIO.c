#include <stdio.h>

double**    readImageFile(char * pcFileLocation) { 
    static double adTabPixel[NB_LIGNES_BMP][NB_COLONNES_BMP];
    
    //open file
    FILE * f = fopen(pcFileLocation, "r");

    if (f == NULL) {
		fprintf(stderr, "Impossible d'ouvrir le fichier d'entrees '%s'.\n", pcFileLocation);
		exit(EXIT_FAILURE);
	}//if
    
    //Lecture et contrôle de la "clé magique"
	unsigned int cleMagique = lireEntier(TAILLE_BLOC, 1, f);

	if (cleMagique != CLE_MAGIQUE_IMG) {
		fprintf(stderr,	"la CLE MAGIQUE est differente d'une image : '%u'.\n", cleMagique);
		exit(EXIT_FAILURE);
	}//if
    
    //Lecture et contrôle du nombre de lignes 
	unsigned int nbEntrees = lireEntier(TAILLE_BLOC, 1, f);

	if ( (nbEntrees != NB_ENTREES_APPR) && (nbEntrees != NB_ENTREES_TEST) ) {
		fprintf(stderr, "lecture invalide du nombre de lignes : '%u'.\n", nbEntrees);
		exit(EXIT_FAILURE);
	}//if
    
    //nombre de lignes par image
	unsigned int nbLignes = lireEntier(TAILLE_BLOC, 1, f);

    if (nbLignes != NB_LIGNES_BMP) {
        fprintf(stderr, "Nombre de lignes par image invalide : '%u'.\n" , nbLignes);
        exit(EXIT_FAILURE);
    }//if

    //nombre de colonnes par image
    unsigned int nbColonnes = lireEntier(TAILLE_BLOC, 1, f);

    if (nbLignes != NB_LIGNES_BMP) {
        fprintf(stderr,	"Nombre de colonnes par image invalide : '%u'.\n", nbColonnes);
        exit(EXIT_FAILURE);
    }//if
    
    //remplissage du tableau avec les pixels lus
    for (unsigned int ligne = 0; ligne < NB_LIGNES_BMP; ligne++) {
        for (unsigned int colonne = 0; colonne < NB_COLONNES_BMP; colonne++) {

            //Lecture d'une entrée de 1 octets 
            if (fread(adTabPixel[[ligne][colonne], 1, 1, f) != 1) {
                perror("Erreur de lecture de pixel (octet) dans le fichier d'entree.");
                exit(EXIT_FAILURE);
            }//if

        }//for
    }//for
    
    //fermeture du fichier d'entrées
	fclose(ficIn);

    return adTabPixel ;
}// fin readImageFile

void    readLabelFile(char * pcFileLocation, T_BITMAP * pbmpBitmap) {
    //open file
    FILE * f = fopen(pcFileLocation, "r");

    //open file
    FILE * f = openFileOfType(pcFileLocation, MAGIC_LABEL_IMG)
}
