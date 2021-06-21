#include <stdio.h> //printf()
#include <string.h> //strcpy
#include <stdlib.h> //exit(EXIT_FAILURE)

#include "Util.h" //convertBItoLI()
#include "Bitmap.h"

/*
* fonction qui lit un fichier d'entrées et place 
* les images lues dans un tableau d'entrées
* 
	***** Fichiers des bitmaps (0x00000803) *****
	-> Lire "clé magique" de 4 octets (0x00000803).
	-> Lire "nombre bitmaps" : entier de 4 octets.
		valant 60000 pour l'apprentissage et 10000 pour le test.
	-> Lire "largeur bitmap" : entier de 4 octets, égal à 28.
	-> Lire "hauteur bitmap" : entier de 4 octets, égal à 28.
	-> Lire n lignes (60000 pour les fichiers d'apprentissage, 10000 pour les tests)
		chaque ligne contenant un bitmap de 28*28 = 784 octets non signés

	***** Fichiers des labels (0x00000801) *****
	-> Lire "clé magique" de 4 octets (0x00000801).
	-> Lire "nombre bitmaps" : entier de 4 octets.
		valant 60000 pour l'apprentissage et 10000 pour le test.
	-> Lire n lignes (60000 pour les fichiers d'apprentissage, 10000 pour les tests)
		chaque ligne contenant un label de 4 octets non signés
	*/
long lireEntrees(char *ficEntrees, T_BITMAP *tabEntrees) {

	//ouverture contrôlée du fichier, en lecture binaire
	FILE* ficIn 
		= fopen(ficEntrees, "rb");

	if (ficIn == NULL) {
		fprintf(stderr, "Impossible d'ouvrir le fichier d'entrees '%s'.\n", ficEntrees);
		exit(EXIT_FAILURE);
	}//if

	//Lecture et contrôle de la "clé magique"
	unsigned int cleMagique 
		= lireEntier(TAILLE_BLOC, 1, ficIn);

	if ( (cleMagique != CLE_MAGIQUE_IMG) 
		&& (cleMagique != CLE_MAGIQUE_TST) ) {
		fprintf(stderr,
			"Cle magique lue invalide : '%u'.\n", cleMagique);
		exit(EXIT_FAILURE);
	}//if


	//Lecture et contrôle du nombre de lignes à lire 
	unsigned int nbEntrees 
		= lireEntier(TAILLE_BLOC, 1, ficIn);

	if ( (nbEntrees != NB_ENTREES_APPR) 
		&& (nbEntrees != NB_ENTREES_TEST) ) {
		fprintf(stderr,
			"Nombre de lignes à lire invalide : '%u'.\n"
			, nbEntrees);
		exit(EXIT_FAILURE);
	}//if

	//Si l'on est dans un fichier d'images, lire et contrôler 
	//le nombre de lignes et colonnes de chaque image.
	if (cleMagique == CLE_MAGIQUE_IMG) {
		
		//nombre de lignes par image
		unsigned int nbLignes 
			= lireEntier(TAILLE_BLOC, 1, ficIn);

		if (nbLignes != NB_LIGNES_BMP) {
			fprintf(stderr,
				"Nombre de lignes par image invalide : '%u'.\n"
				, nbLignes);
			exit(EXIT_FAILURE);
		}//if

		//nombre de colonnes par image
		unsigned int nbColonnes 
			= lireEntier(TAILLE_BLOC, 1, ficIn);

		if (nbLignes != NB_LIGNES_BMP) {
			fprintf(stderr,
				"Nombre de colonnes par image invalide : '%u'.\n"
				, nbColonnes);
			exit(EXIT_FAILURE);
		}//if

		//remplissage du tableau d'entrées avec les pixels lus
		for (unsigned int numEntree = 0; numEntree < nbEntrees; numEntree++) {
			for (unsigned int ligne = 0; ligne < NB_LIGNES_BMP; ligne++) {
				for (unsigned int colonne = 0; colonne < NB_COLONNES_BMP; colonne++) {

					//Lecture d'une entrée de 1 octets 
					if (fread(&(tabEntrees[numEntree]).pixels[ligne][colonne]
						, 1, 1, ficIn) != 1) {
						perror("Erreur de lecture de pixel (octet) dans le fichier d'entree.");
						exit(EXIT_FAILURE);
					}//if

				}//for
			}//for
		}//for

	} else {//on n'est donc pas dans un fichier d'images, donc dans un fichier de labels

		//remplissage du tableau d'entrées avec les labels lus
		for (unsigned int numEntree = 0; numEntree < nbEntrees; numEntree++) {
			
			//Lecture d'une entrée de 1 octets 
			if (fread(&(tabEntrees[numEntree]).label
				, 1, 1, ficIn) != 1) {
				perror("Erreur de lecture de label (octet) dans le fichier d'entree.");
				exit(EXIT_FAILURE);
			}//if

		}//for

	}//if
	


	//fermeture du fichier d'entrées
	fclose(ficIn);

	return nbEntrees;
	
}//lireEntrees()

 
void afficherEntree(T_BITMAP *elem, char afficherProba, T_LABEL label) {

	//chaine de caractères correspondante au champ de classification
	char strLabel[40] = "";
	strcpy(strLabel, getStrLabel(elem->label));

	//affichage de l'entrée
	printf(
		" Reel: [%s] "
		, strLabel
	);//printf()

	if (afficherProba) {
		printf(" Proba: [%2.2lf%%]", 100 * elem->proba);

		if (elem->proba >= 0.5) {
			if (elem->label == label) {
				printf(" => [VALIDE] : vrai positif");
			}
			else {
				printf(" => [ERREUR] : faux positif");
			}//if
		}
		else { //proba < 0.5
			if (elem->label != label) {
				printf(" => [VALIDE] : vrai negatif");
			}
			else { //elem.label == label
				printf(" => [ERREUR] : faux negatif");
			} //if
		}//if
	}//if

	//on finit par un saut de ligne
	printf("\n");

}//afficherEntree()

//fonction d'affichage d'une image d'un bitmap
void afficherImage(T_BITMAP elem) {
	
	printf("\n");

	for (int i = 0; i < NB_LIGNES_BMP; i++) {

		for (int j = 0; j < NB_COLONNES_BMP; j++) {

			if (elem.pixels[i][j] > 0) {
				printf("*");
			} else {
				printf(" ");
			}//if

		}//for

		printf("\n");

	}//for

}//afficherImage


//fonction d'affichage d'un tableau d'entrees
void afficherTabEntrees(T_BITMAP *tabEntrees, long nbEntrees
	, T_LABEL label, char afficherProba) {

	printf("\n");

	//parcours du tableau d'entrées
	for (long i = 0;
		//(i < MAX_NB_LIGNES_FICIN) && (tabEntrees[i].largPetale > 0); i++) {
		(i < nbEntrees) /* && (tabEntrees[i].largPetale > 0) */ ; i++) {//REVOIR CONDITION ICI
		afficherEntree(&(tabEntrees)[i], afficherProba, label);

	}//for

}//affichertabEntrees()

//fonction qui renvoie la constante de type T_LABEL
//en fonction de l'entier entrée en paramètre.
T_LABEL getLabel(long numLabel) {

	switch (numLabel) {
		case 0 :	return ZERO;	break;
		case 1:		return UN;		break;
		case 2:		return DEUX;	break;
		case 3:		return TROIS;	break;
		case 4:		return QUATRE;	break;
		case 5:		return CINQ;	break;
		case 6:		return SIX;		break;
		case 7:		return SEPT;	break;
		case 8:		return HUIT;	break;
		case 9:		return NEUF;	break;
		default:	return INCONNU;	break;
	}//switch

}//getLabel()


//Fonction utilitaire, qui permet d'obtenir une correspondance
//entre un numéro de label et une chaine de caractère.
//Peut servir pour réaliser de l'affichage.
const char* getStrLabel(T_LABEL label) {
	
	char strLabel[40] = "";

	switch (label) {
		case ZERO	: strcpy(strLabel, "0 (Zero)  "); break;
		case UN		: strcpy(strLabel, "1 (Un)    "); break;
		case DEUX	: strcpy(strLabel, "2 (Deux)  "); break;
		case TROIS	: strcpy(strLabel, "3 (Trois) "); break;
		case QUATRE	: strcpy(strLabel, "4 (Quatre)"); break;
		case CINQ	: strcpy(strLabel, "5 (Cinq)  "); break;
		case SIX	: strcpy(strLabel, "6 (Six)   "); break;
		case SEPT	: strcpy(strLabel, "7 (Sept)  "); break;
		case HUIT	: strcpy(strLabel, "8 (Huit)  "); break;
		case NEUF	: strcpy(strLabel, "9 (Neuf)  "); break;
		default: strcpy(strLabel, "Label inconnu"); break;
	}//switch

	return strLabel;

}//getStrLabel