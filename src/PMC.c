#include <stdio.h> //printf()
#include <stdlib.h>
#include <string.h> //memcpy()
#include <math.h> //pow()

#include "Util.h"
#include "Bitmap.h"
#include "Neurone.h"
#include "Couche.h"
#include "Statistiques.h"//majStats()
#include "PMC.h"


/* fonction d'initialisation d'un PMC */
void initPMC(T_PMC *pmc, long nbCouches, long *nbNeurCouche) {

	//initialisation du nombre de couches
	pmc->nbCouches = nbCouches;

	//pour chaque couche
	for (long numCouche = 0 ; numCouche < pmc->nbCouches; numCouche++) {
		
		//le nombre de dendrites vaut le nombre de neurones de la couche précédente (PMC formel)
		long nbDendrites =
			(numCouche == 0) ? 0 : nbNeurCouche[numCouche - 1];

		//initialisation de la couche courante du PMC
		initCouche(&(pmc->couches[numCouche])
			, nbNeurCouche[numCouche], nbDendrites);

	}//for

	//initialisation des poids
	initPoids(pmc);	//initCoucheEntree(couche, *elem);

}//initPMC()

//fonction d'initialisation des poids
void initPoids(T_PMC *pmc) {
	
	long nbCouches = pmc->nbCouches
		, nbNeur = 0
		, nbNeurCouchePrec = 0;
	
	//initialisation du tableau de poids avec des valeurs aléatoires
	for (long numCouche = 1; numCouche < nbCouches; numCouche++) {//pour chaque couche

		nbNeur = pmc->couches[numCouche].nbNeurones;
		
		nbNeurCouchePrec = numCouche == 0 ? 0 
			: pmc->couches[numCouche -1].nbNeurones;
		
		//pour chaque neurone
		for (long numNeur = 0; numNeur < nbNeur ; numNeur++) {

			//pour chq dendrite (nb dendrites = nb neurones de couche -1 car PMC formel)																			 
			for (long numDendrite = 0; numDendrite < nbNeurCouchePrec ; numDendrite++) {
				
				//generation et affectation au neurone d'un poids aléatoire (ou nul si couche zéro)
				pmc->couches[numCouche].neurones[numNeur].poids[numDendrite]
					= (numCouche == 0) //si l'on est sur la couche d'entrée
						|| ( (numCouche < nbCouches - 1) && (numNeur == 0) )//ou sur un neurone de biais
							? 0 //affecter la valeur zéro
							: nombreRdm(-1.0, 1.0);//sinon affecter un nombre aléatoire entre -1 et 1
				
			}//for
		}//for
	}//for
}//initPoids

//fonction qui va calculer la probabilité en sortie en fonction
//des élements en entrée
void propagerAvant(T_PMC *pmc, T_BITMAP *elem
	, T_LABEL *labelDetecte, T_STATS *stats) {

	T_COUCHE* couche = &(pmc->couches[0]);//couche 0
	T_NEURONE* neur = NULL;

	long nbNeurCouche = couche->nbNeurones,//nombres de neurones de la couche 0
		nbNeurCouchePrec = 0;

	double proba = 0.0;

	//initialisation de la couche d'entrée
	initCoucheEntree(couche, elem);

	//pour chaque couche après la couche d'entree
	for (long numCouche = 1; numCouche < pmc->nbCouches; numCouche++) {

		//pointeur vers la couche courante (pour simplifier l'écriture)
		couche = &(pmc->couches[numCouche]);

		//récupération du nombre de neurones de la couche courante
		nbNeurCouche = couche->nbNeurones;

		//récupération du nombre de neurones de la couche précédente
		nbNeurCouchePrec = pmc->couches[numCouche - 1].nbNeurones;

		//pour chaque neurone de la couche courante
		for (long numNeur = 0; numNeur < nbNeurCouche ; numNeur++) {

			//pointeur vers le neurone courant (pour simplifier l'écriture)
			neur = &(couche->neurones[numNeur]);

			//si l'on se trouve sur un neurone de biais
			//(pour rappel : pas de neurone de biais sur la couche de sortie)
			if (((numNeur == 0) && (numCouche < pmc->nbCouches - 1))) {
				//affecter la valeur 1
				neur->valeurSortie = 1;
			}
			else {
				//récupération de la valeur des neurones précédents
				double tabValPrec[MAX_NB_DENDRITES] = { 0 }; 
				for (long i = 0; i < nbNeurCouchePrec ; i++) {
					tabValPrec[i] = pmc->couches[numCouche - 1].neurones[i].valeurSortie;
				}//for

				//calcul de la probabilité pour le neurone courant
				//neur->valeur = calculerProbaNeurone(*neur, tabValPrec);
				calculerProbaNeurone(neur, tabValPrec);
			}//if
		}//for
	}//for

	//variable qui contiendra le numero de neurone de sortie contenant
	//la plus grande probabilité (sert surtout pour la classification
	long numNeurSortie = 0;

	//affectation de la dernière maximale de la couche de sortie à l'élément
	elem->proba = probaMax(couche, &numNeurSortie);

	//affectation de la famille correspondante au numero de neurone de sortie avec proba maximale
	*labelDetecte = getLabel(numNeurSortie);

	//mise à jour des statistiques globales
	majStats(stats, elem->proba
		, *labelDetecte
		, elem->label);

	//affichage rajouté pour le contrôle du résultat de la rétropropagation
	//afficherStats(*stats);

}//propagerAvant()

//fonction qui calcule et renvoie l'erreur de sortie quadratique 
//de l'ensemble des neurones de sortie
//elle met également à jour l'erreur (gradient) dans chaque neurone de sortie
double errSortie(T_PMC* pmc, T_LABEL labelAttendu) {

	double errQuadra = 0;

	//pointeur vers la couche de sortie
	T_COUCHE* coucheSortie = &pmc->couches[pmc->nbCouches - 1];
	T_NEURONE* neur = NULL;

	//parcours de la couche de sortie et calcul des erreurs de sortie
	for (long numNeur = 0; numNeur < coucheSortie->nbNeurones; numNeur++) {

		//pointeur vers le neurone courant
		neur = &coucheSortie->neurones[numNeur];
	
		//valeur attendue suivant le rang du neurone de sortie
		double valeurAttendue = 
			(numNeur == labelAttendu) ? 1 : 0;

		//calcul de l'erreur quadratique
		errQuadra += pow((neur->valeurSortie - valeurAttendue), 2);
		
		//calcul de l'erreur (gradient) du neurone de sortie courant
		neur->gradient
			= 2 * (valeurAttendue - neur->valeurSortie)
				* neur->derivFctActivation(neur->valeurSortie);

			/*dans certaines références, neur->gradient = (valeurAttendue - neur->valeurSortie)
			 Dans d'autres, neur->gradient =(valeurAttendue - neur->valeurSortie) 
				* neur->derivFctActivation(neur->valeurAgregation) */

	}//for

	//renvoi de l'erreur quadratique de sortie 
	//(somme des erreurs quadratiques de chaque neurone de sortie)
	return 0.5 * errQuadra; //dans la plupart des références, on divise d'abord l'erreur quadra par 2


}//errSortie()

void retropropager(T_PMC *pmc) {
//calculs des erreurs du PMC autre que ceux de la couche de sortie
	long nbDendrites = 0;
	T_NEURONE *neur = NULL;

	//parcours du PMC à l'envers et mise à jour des erreurs
	for (long numCouche = pmc->nbCouches - 2 ; numCouche > 0; numCouche--) {
		
		//pour chaque neurone de la couche courante
		for (long numNeur = 0; numNeur < pmc->couches[numCouche].nbNeurones; numNeur++) {
			
			//pointeur vers le neurone courant
			neur = &pmc->couches[numCouche].neurones[numNeur];

			//initialisation du gradient
			neur->gradient = 0;
			
			//nombres de neurones de la couche d'après (et donc de connexions, puisque PMC formel)
			nbDendrites = pmc->couches[numCouche + 1].nbNeurones;

			//calcul du gradient du neurone courant
			for (long i = 0; i < nbDendrites; i++) {
				neur->gradient
					+= pmc->couches[numCouche + 1].neurones[i].poids[numNeur]
						* pmc->couches[numCouche + 1].neurones[i].gradient;
			}//for

			//au final, on multiplie l'erreur du neurone par la dérivée de sa fonction d'activation
			neur->gradient *= derivSigmoide(neur->valeurSortie);

		}//for
	}//for

}//retropropager()

void corrigerPoids(T_PMC *pmc, double tauxAppr) {


	double poids = 0;
	long nbDendrites = 0;

	T_COUCHE* couche = &pmc->couches[0];
	T_NEURONE* neur = NULL;

	//pour chaque couche après la couche d'entree
	for (long numCouche = 1; numCouche < pmc->nbCouches; numCouche++) {

		//pointeur vers la couche courante (pour simplifier l'écriture)
		couche = &(pmc->couches[numCouche]);

		//pour chaque neurone de la couche courante
		for (long numNeur = 0; numNeur < couche->nbNeurones; numNeur++) {

			//pointeur vers le neurone courant (pour simplifier l'écriture)
			neur = &(couche->neurones[numNeur]);

			//si l'on ne se trouve sur un neurone de biais
			//(remarque : pas de neurone de biais en couche de sortie)
			if ((numNeur != 0) || (numCouche == (pmc->nbCouches - 1))) {
				//corriger le poids
				//pour chacun des dendrites de ce neurone
				for (long i = 0; i < neur->nbDendrites; i++) {
					neur->poids[i]
						+= tauxAppr * pmc->couches[numCouche - 1].neurones[i].valeurSortie
							* neur->gradient;
				}//for
			}//if
		}//for
	}//for

}//corrigerPoids()

//fonction d'affichage du perceptron multicouche
void afficherPMC(T_PMC *pmc) {
	printf("\n------------- Affichage du perceptron multi-couches -------------\n");

	//parcours des couches du PMC
	for (long i = 0; i < pmc->nbCouches; i++) {
		printf("\nCouche # %i : \t", i);
		afficherCouche(&(pmc->couches)[i]);
	}//for

	printf("\n\n");

}//afficherPMC()

void afficherDetection(T_BITMAP elem, T_LABEL label) {

	char strLabel[40] = "";
	strcpy(strLabel, getStrLabel(label));
	printf( " Detectee: [ %s ] ", strLabel );

}//afficherDetection()

void entrainerPMC(T_PMC *pmc, char *ficApprImg, char *ficApprLbl
	, double variationMaxToleree, double nbMaxEpochs, double tauxAppr) {

	//variables utilisées pour la condition de sortie sur la valeur de l'erreur globale
	double errTotale = 0
		, errMoyenne = 1.0;

	//tableau d'entrées qui sera rempli à partir du fichier d'apprentissage
	T_BITMAP *tabEntrees = malloc(sizeof(T_BITMAP)* NB_ENTREES_APPR);

	if (tabEntrees == NULL) {
		perror("Probleme memoire, impossible d'initialiser le tableau d'entrees.");
		exit(EXIT_FAILURE);
	}//

	//remplissage du tableau d'apprentissage
	long nbEntrees
		= lireEntrees(ficApprImg, tabEntrees);

	long nbLabels
		= lireEntrees(ficApprLbl, tabEntrees);

	//rajouté pour test uniquement
	//afficherImage(tabEntrees[21]);//mettre la valeur qu'on veut entre 0 et max nb entrée

	//déclaration du tableau de statistiques (nb "Vrais positifs" etc..)
	T_STATS stats = { 0 };

	//déclaration et initialisation du champ de la famille qui va être identifiée
	T_LABEL labelDetecte = INCONNU
		, labelAttendu = INCONNU;


	//affichage du PMC
	//afficherPMC(pmc);

	//tant que l'on n'a pas dépassé le nombre maximal d'itérations d'apprentissage
	//et que la variation globale est inférieure à celle tolérée
	for (long epoch = 0
		; (epoch < nbMaxEpochs) && (errMoyenne > variationMaxToleree)
		; epoch++) {

		//printf("\nEpoch # %i : \n", epoch);

		//pourcours du tableau contenant toutes les entrées lues
		for (long numEntree = 0; numEntree < nbEntrees; numEntree++) {

			labelAttendu = tabEntrees[numEntree].label;

			//afficherPMC(pmc);

			//calcul des probabilités du PMC (propagation vers l'avant)
			//printf("\n*************** PROPAGATION VERS L'AVANT ***************");
			propagerAvant(pmc/*, nbNeurCouche*/, &(tabEntrees[numEntree])
				, &labelDetecte, &stats);

			//afficherPMC(pmc);

			//affichage de la prédiction
			//afficherDetection(tabEntrees[numEntree], labelDetecte);

			//affichage de l'élement courant
			//afficherEntree(tabEntrees[numEntree], 1, labelDetecte);

			//mise à jour de l'erreur quadratique globale
			errTotale += errSortie(pmc, labelAttendu);
			errMoyenne = errTotale / (((double)(numEntree)+1) * (double)(epoch));

			//printf(" Err quadra globale = %.4lf\n\n", errMoyenne);


			if (errMoyenne > variationMaxToleree) {//doute sur ce if avec la condition du for

				//retropropagation
				//printf("\n*************** RETROPROPAGATION ***************");
				retropropager(pmc);

				//nouvel affichage du PMC (propagation arriere effectuée)
				//afficherPMC(pmc);

				//correction des poids
				//printf("\n*************** CORRECTION DES POIDS ***************");
				corrigerPoids(pmc, tauxAppr);
				//nouvel affichage du PMC (correction des poids effectuée)
				//afficherPMC(pmc);

			}//if
		}//for
		printf("\nEpoch #%d : Err quadra globale = %.4lf\n", epoch + 1, errMoyenne);
		afficherStats(stats);

	}//for

	//libération de la mémoire du tableau d'entrées
	free(tabEntrees);
	tabEntrees = NULL;


}//entrainerPMC();

void testerPMC(T_PMC* pmc, char* ficTest) {}//à venir