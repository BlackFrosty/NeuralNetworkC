#ifndef PMC_CLASSIF_INCLUDED
#define PMC_CLASSIF_H_INCLUDED


#define MAX_NB_COUCHES  10 //nombre maximum de couches

//Définition du type PMC (perceptron multi-couches)
typedef struct {
	long nbCouches; //nombres de couches de neurones
	T_COUCHE couches[MAX_NB_COUCHES];
}T_PMC;

//fonction d'initialisation d'un PMC
void initPMC(T_PMC *pmc, long nbCouches, long *nbNeurCouche);

void initPoids(T_PMC *pmc);


//fonction de calcul des probabilités du PMC
void propagerAvant(T_PMC* pmc, T_BITMAP* elem
	, T_LABEL *labelDetecte, T_STATS* stats);

double errSortie(T_PMC* pmc, T_LABEL labelAttendu);

void retropropager(T_PMC *pmc);

void corrigerPoids(T_PMC *pmc, double tauxAppr);

void afficherPMC(T_PMC *pmc);

void afficherDetection(T_BITMAP element, T_LABEL label);

void entrainerPMC(T_PMC* pmc, char* ficAppr, char* ficApprLbl
	, double variationMaxToleree, double nbMaxEpochs, double tauxAppr);

void testerPMC(T_PMC* pmc, char* ficTest); //à venir

#endif // PMC_CLASSIF_INCLUDED
