#include <stdio.h>

#include "Bitmap.h"
#include "Neurone.h"
#include "Couche.h"



//fonction d'initilisation d'une couche de neurones
void initCouche (T_COUCHE *coucheNeur, long nbNeurones
	, long nbDendrides) {
	
	//affectation du nombre de neurone de la couche courante
	coucheNeur->nbNeurones = nbNeurones;

	//pour chaque neurone de la couche
	for (long numNeur = 0; numNeur < nbNeurones ; numNeur++) {

		//pointeur vers le neurone courant
		T_NEURONE* neurCourant
			= &(coucheNeur->neurones[numNeur]);

		//initialisation du neurone
		initNeurone(neurCourant, nbDendrides
			, -99 //valeur, à 99 par défaut (choix arbitraire)
			, 0 //erreur, nul avant la rétropropagation
			, &sigmoide, &sigmoide); 

	}//for

}//initCouche()

/*
fonction d'initilisation d'une couche d'entrée d'un PMC
la différence avec une couche classique, c'est qu'elle ne va pas chercher ses valeurs en 
fonction de la couche précédente, mais qu'elle les récupère directement 
depuis un tableau d'entrées
*/
void initCoucheEntree(T_COUCHE *couche, T_BITMAP *elem) {
	
	//initialisation du nombre de neurones
	couche->nbNeurones = NB_LIGNES_BMP * NB_COLONNES_BMP + 1; 
	
	/* initialisation du neurone de biais (neurone 0 de la couche) 
	avec la valeur 1, aucun dendrite et des poids nuls */
	initNeurone(
		&(couche->neurones)[0]
		, 0 //zéro dendrite
		, 1 //"valeur" à 1 (neurone de biais)
		, 0 //gradient
		, &sigmoide //fonction d'activation
		, &derivSigmoide);//dérivée de la fonction d'activation

	//parcours de chaque case du bitmap et création du neurone correspondant
	int indice = 1;
	//for (int numLigne = 0; numLigne < 5 /* NB_LIGNES_BMP */; numLigne++) {
	for (int numLigne = 0; numLigne < NB_LIGNES_BMP ; numLigne++) {

		//for (int numColonne = 0; numColonne < 5/* NB_LIGNES_BMP */; numColonne++) {
		for (int numColonne = 0; numColonne < NB_LIGNES_BMP ; numColonne++) {
			//initialisation du neurone à la valeur du pixel
			
			printf("indice = %d\n", indice);
			initNeurone(
				//numero du neurone dans la couche d'entrée (après neurone de biais)
				&(couche->neurones)[indice] 
				, 0 //nbDendrites
				, elem->pixels[numLigne][numColonne]
				, 0 //gradient
				, &sigmoide
				, &derivSigmoide);
				
			indice++;
		}//for

	}//for

}//initCoucheEntree

double probaMax(T_COUCHE *couche, long *numNeurSortie) {

	double proba = 0;
	long numNeur = 0;

	for (long i = 0 ; i < couche->nbNeurones ; i++) {
		if (couche->neurones[i].valeurSortie > proba) {
			proba = couche->neurones[i].valeurSortie ;
			numNeur = i;
		}//if
	}//for

	//affection du numero de neurone contenant la proba max à la variable "num neurone" pointée
	*numNeurSortie = numNeur;

	return proba;

}//probaMax()

void afficherCouche(T_COUCHE *couche) {

	//parcours des neurones de la couche
	for (long i = 0; i < couche->nbNeurones ; i++) {
		printf("\n\t Neurone # %i : ", i);
		afficherNeurone(couche->neurones[i]);
	}//for

}//afficherCouche()

