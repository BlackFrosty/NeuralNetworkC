#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED


//nombre maximum de lignes à lire dans le fichier d'apprentissage
#define NB_ENTREES_APPR     60000

//nombre maximum de lignes à lire dans le fichier de test
#define NB_ENTREES_TEST     10000

#define NB_CHAMPS           4 //nombre de champs de la structure de données (voir si toujours utile)

//nombre de lignes et de colonnes d'un fichier bitmap
#define NB_LIGNES_BMP       28
#define NB_COLONNES_BMP     28

//taille en octet d'un bloc � lire dans les fichiers d'entrée
#define TAILLE_BLOC         4

#define CLE_MAGIQUE_IMG    2051
#define CLE_MAGIQUE_TST     2049


//définition des constantes de classification d'éléments
typedef enum {
    ZERO = 0, UN = 1, DEUX = 2, TROIS = 3, QUATRE = 4
    , CINQ = 5, SIX = 6, SEPT = 7, HUIT = 8, NEUF = 9
    , INCONNU = -1
} T_LABEL;//T_LABEL_CHIFFRES;

//commenter le précédent et décommenter le suivant
//pour traiter des vétements au lieu des chiffres
/*
typedef enum {
    TSHIRT_TOP = 0, TROUSER = 1, PULLOVER = 2, DRESS = 3, COAT = 4
    , SANDAL = 5, SHIRT = 6, SNEAKER = 7, BAG = 8, ANKLE_BOOT = 9
    , INCONNU = -1
} T_LABEL;
*/


//définition du type structuré T_BITMAP
typedef struct {

    //char car besoin d'un seul octet par bit
    unsigned char pixels[NB_LIGNES_BMP][NB_COLONNES_BMP];
    T_LABEL label;
    double proba;

}T_BITMAP;//T_BITMAP



//fonction qui lit un ensemble d'éléments à partir d'un fichier d'entrées
//et les stocke dans un tableau. Renvoi le nombre d'éléments lus.
long lireEntrees(char* ficEntrees, T_BITMAP* tabEntrees);

//fonction d'affichage d'un élément contenu dans un tableau
//Après propagation avant par le PMC, la probabilité de chaque
//reconnaissance est mis à jour dans ce tableau.
//Cette probabilité est affichable avec le booleen afficherProba)
void afficherEntree(T_BITMAP *elem, char afficherProba, T_LABEL label);

//fonction d'affichage d'un tableau d'entrées
void afficherTabEntrees(T_BITMAP *tabEntrees, long nbEntrees
    , T_LABEL label, char afficherProba);

//renvoie le label associé un numéro de neurone de sortie
T_LABEL getLabel(long numNeurSortie);

//retourne une chaine caractère associée à un label
const char* getStrLabel(T_LABEL label);

//affichage d'une image pixel par pixel
void afficherImage(T_BITMAP elem);

#endif // BITMAP_H_INCLUDED