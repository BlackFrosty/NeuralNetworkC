#ifndef STATISTIQUES_H_INCLUDED
#define STATISTIQUES_H_INCLUDED

//definition du type structuré T_STAT
typedef struct {
	double nbElements
		, nbVraiPositifs
		, nbFauxPositifs
		, nbVraiNegatifs
		, nbFauxNegatifs
		, precision
		, rappel;

}T_STATS;

void majStats(T_STATS *stats, double proba
	, T_LABEL labelRecherche, T_LABEL labelEffectif);

void majStatsPMC_Classif(T_STATS *stats, double proba);

void afficherStats(T_STATS stats);

#endif //STATISTIQUES_H_INCLUDED