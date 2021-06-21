#include <stdio.h>
#include <stdlib.h>

#include "Bitmap.h"
#include "Neurone.h"
#include "Couche.h"
#include "Statistiques.h"
#include "PMC.h"



int main(void) {

    //déclaration d'un réseaux de neurones PMC type "Classification"
    T_PMC pmc = { 0 };

    //tableau indiquant le nombre de neurones pour chaque couche
    long nbNeurCouche[]
        //= { NB_LIGNES_BMP * NB_COLONNES_BMP + 1, 30, 10 };
        = { 3, 3, 3 };

    //nombre de couches, calculé automatiquement à partir du tableau nbNeurCouche
    long nbCouches = sizeof(nbNeurCouche) / sizeof(long );

    //variables qui conditionneront les itérations d'apprentissages (epoch)
    double variationMaxToleree = 0.1
            , tauxAppr = 0.01;

    //nombre maximum d'itérations (epoch) d'apprentissage
    long nbMaxEpochs = 1;

    //nom des fichiers d'apprentissage et de test
    char ficApprImg[] = "res/mnist/char/train-images.idx3-ubyte";
    char ficApprLbl[] = "res/mnist/char/train-labels.idx1-ubyte";

    
    
    //initialisation du PMC (poids et valeurs nuls)
    initPMC(&pmc, nbCouches, nbNeurCouche);
    
    //entrainer le PMC à partir d'un fichier d'apprentissage
    entrainerPMC(&pmc, ficApprImg, ficApprLbl
        , variationMaxToleree, nbMaxEpochs, tauxAppr);

    //tester le PMC à partir d'un fichier de test
    //testerPMC(&pmc, ficTest);//fonction à définir
    
    //getchar() pour mettre le terminal en attente
    char c = getchar();

    return EXIT_SUCCESS;

}//main()