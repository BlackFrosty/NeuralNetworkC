#include <stdio.h> //printf()

#include "Bitmap.h"
#include "Statistiques.h"

void majStats(T_STATS *stats, double proba
	, T_LABEL labelRecherche, T_LABEL labelEffectif ) {

	//incrémentation du nombre d'éléments analysés
	stats->nbElements++;

	//incrémentation du champs concerné
	if (proba >= 0.5) {

		if (labelEffectif == labelRecherche) {
			//Prediction valide : vrai positif
			stats->nbVraiPositifs++;
		}
		else {//labelEffectif != labelRecherche
		 //Prediction invalide : faux positif [ERREUR]
			stats->nbFauxPositifs++;
		}//if

	}
	else { //proba < 0.5

		if (labelEffectif != labelRecherche) {
			// Prediction valide : vrai negatif
			stats->nbVraiNegatifs++;
		}
		else { //labelEffectif == labelRecherche
		 //Prediction invalide : faux negatif [ERREUR]");
			stats->nbFauxNegatifs++;
		} //if

	}//if

	//mise à jour du champ "precision"
	if (stats->nbVraiPositifs + stats->nbFauxPositifs) {//pour eviter la division par zero
		stats->precision
			= stats->nbVraiPositifs / (stats->nbVraiPositifs + stats->nbFauxPositifs);
	}//if

	//mise à jour du champ "rappel"
	if (stats->nbVraiPositifs + stats->nbFauxNegatifs) {//pour eviter la division par zero
		stats->rappel
			= stats->nbVraiPositifs / (stats->nbVraiPositifs + stats->nbFauxNegatifs);
	}//if

}//majStats


void majStatsPMC_Classif(T_STATS *stats, double proba) {

}//majStatsPMC_Classif


void afficherStats(T_STATS stats) {

	printf("\nPrecision  = %.0lf%%, Rappel = %.0lf%%, nb Vrais positifs = %.0lf, nb Faux positifs = %.0lf, nb Vrais negatifs = %.0lf, nb Faux negatifs = %.0lf\n"
		, stats.precision * 100
		, stats.rappel * 100
		, stats.nbVraiPositifs
		, stats.nbFauxPositifs
		, stats.nbVraiNegatifs
		, stats.nbFauxNegatifs);

}//afficherStats()