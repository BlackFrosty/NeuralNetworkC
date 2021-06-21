#include <stdio.h> //printf()
#include <string.h> //strcpy
#include <stdlib.h> //exit(EXIT_FAILURE)

#include "Iris.h"

//fonction qui lit un fichier d'apprentissage et renvoie un tableau d'iris
long lireTabIris(char* nomFicAppr, T_IRIS* tabIris, double nbIris) {

	long cptIris = 0;

	double champIgnore = 0.0;

	//lecture du fichier d'apprentissage
	FILE* ficAppr = fopen(nomFicAppr, "rt");

	if (ficAppr == NULL) {
		perror("Impossible d'ouvrir le fichier d'apprentissage.\n");
		exit(EXIT_FAILURE);
	}//if

	char ligneLue[MAX_TAILLE_LIGNE + 1];
	//Pour chaque ligne du fichier d'apprentissage, en récupérer les valeurs
	for (long i = 0
		; (fgets(ligneLue, MAX_TAILLE_LIGNE, ficAppr) != NULL)
		&& (i < nbIris)
		; i++, cptIris++) {

		//variable qui va permettre de stocker et traiter la famille d'Iris lue
		char familleLue[20] = "";

		//on vérifie qu'il y a bien 5 éléments par ligne
		if ( sscanf(ligneLue, "%lf,%lf,%lf,%lf,%s"
			, &champIgnore, &champIgnore
			, &(tabIris[i]).lgPetale, &(tabIris[i]).largPetale
			, familleLue) == 5) {

			//on affecte à l'Iris la constante de la famille d'Iris lue
			if (strstr(familleLue, "setosa") != NULL) {
				tabIris[i].famille = SETOSA;
			} else  if (strstr(familleLue, "versicolor") != NULL) {
				tabIris[i].famille = VERSICOLOR;
			} else  if (strstr(familleLue, "virginica") != NULL) {
				tabIris[i].famille = VIRGINICA;
			}//if

		}
		else { // on n'a pas 3 éléments par ligne (ligne invalide)
			perror("Erreur dans le fichier d'apprentissage, format invalide : 5 valeurs attendues par ligne");
			exit(EXIT_FAILURE);
		}  //if

	}//while

	//fermeture du fichier d'apprentissage
	fclose(ficAppr);

	return cptIris;

}//lireTabIris()


void afficherUnIris(T_IRIS iris, long afficherProba, T_FAMILLE_IRIS famille) {

	//chaine de caractères correspondante au champ familleIris
	char strFamille[40] = "";
	strcpy(strFamille, getStrFamilleIris(iris.famille));

	//affichage de l'Iris
	printf(
		" Reel: [%s]  Long: [%1.1lf]  Larg: [%1.1lf]"
		, strFamille
		, iris.lgPetale
		, iris.largPetale
	);//printf()

	if (afficherProba) {
		printf(" Proba: [%2.2lf%%]", 100 * iris.proba);

		if ( iris.proba >= 0.5 ) {
			if (iris.famille == famille) {
				printf(" => [VALIDE] : vrai positif");
			} else {
				printf(" => [ERREUR] : faux positif");
			}//if
		} else { //proba < 0.5
			if ( iris.famille != famille) {
				printf(" => [VALIDE] : vrai negatif");
			} else { //iris.famille == famille
				printf(" => [ERREUR] : faux negatif");
			} //if
		}//if
	}//if

	//on finit par un saut de ligne
	printf("\n");

}//AfficherUnIris()

//fonction d'affichage d'un tableau d'Iris
void afficherTabIris(T_IRIS* tabIris, long nbIris
	, T_FAMILLE_IRIS famille, long afficherProba) {

	printf("\n");

	//parcours du tableau d'Iris
	for (long i = 0;
		//(i < MAX_NB_LIGNES) && (tabIris[i].largPetale > 0); i++) {
		(i < nbIris) && (tabIris[i].largPetale > 0); i++) {
		afficherUnIris(tabIris[i], afficherProba, famille);
		
	}//

}//afficherTabIris()

//fonction qui renvoie la constante de type T_FAMILLE_IRIS
//en fonction de l'entier entrée en paramètre
T_FAMILLE_IRIS getFamilleIris(long numNeurSortie) {
	switch (numNeurSortie) {
		case 0 :
			return SETOSA;
			break;
		case 1 :
			return VERSICOLOR;
			break;
		case 2 :
			return VIRGINICA;
			break;
		default:
			return -1;
			break;
	}//switch
}//getFamilleIris()

const char* getStrFamilleIris(T_FAMILLE_IRIS famille) {
	char strFamille[40] = "";

	switch (famille) {
	case SETOSA :
		strcpy(strFamille, "  Setosa  ");
		break;

	case VERSICOLOR :
		strcpy(strFamille, "Versicolor");
		break;

	case VIRGINICA :
		strcpy(strFamille, "Virginica ");
		break;

	default:
		strcpy(strFamille, "Famille non repertoriee");
		break;
	}//switch

	return strFamille;

}//getStrFamilleIris
