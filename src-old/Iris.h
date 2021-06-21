#ifndef IRIS_H_INCLUDED
#define IRIS_H_INCLUDED


#define MAX_TAILLE_LIGNE    35 //taille maximum d'une ligne de donn�es dans un fichier
#define MAX_NB_LIGNES       130 //nombre maximum de lignes � lire dans le fichier
#define NB_CHAMPS           4 //nombre de champs de la structure de donn�es (Iris)    

//d�finition des constantes de types de famille d'Iris
typedef enum  {
        SETOSA = 0
    ,   VERSICOLOR = 1
    ,   VIRGINICA = 2 
} T_FAMILLE_IRIS;

//d�finition du type structur� T_IRIS
typedef struct {
    double lgPetale;
    double largPetale;
    T_FAMILLE_IRIS famille;
    double proba;
}T_IRIS;//T_IRIS



//fonction qui renvoie un tableau d'Iris (structure) � partir d'un fichier de configuration d'Iris
long lireTabIris(char* nomFicAppr, T_IRIS* tabIris, double nbIris);

void afficherUnIris (T_IRIS iris, long afficherProba, T_FAMILLE_IRIS famille);

//fonction d'affichage d'un tableau d'Iris
void afficherTabIris(T_IRIS* tabIris, long nbIris
    , T_FAMILLE_IRIS famille, long afficherProba);

T_FAMILLE_IRIS getFamilleIris(long numNeurSortie);

const char* getStrFamilleIris(T_FAMILLE_IRIS famille);


#endif // IRIS_H_INCLUDED