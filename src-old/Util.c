#include <stdio.h> //stdin
#include <stdlib.h> //rand
#include <time.h> //srand

#include "Util.h"

double nombreRdm(double min, double max) {
	//initialisation du générateur aléatoire avec time()
	srand(time(NULL));

	//renvoi d'une valeur aléatoire comprise entre min et max
	return (double)rand() / RAND_MAX * (max - min) + min;

}//poidsRdm


/* Fonction qui inverse les octets 1234
 vers 4321 d'un entier sur 32 bits. Utile car MNIST utilise des entiers au format
 Big Indian, où les 4 premiers octets sont dans l'ordre inverse des entiers 
 interprétables par un processeur type Intel */
unsigned int toLowIndian(unsigned int num) {

    //register pour accélérer le traitement en mémoire
    register unsigned int res = 
        //decallage du 4e octet en 1er position
        ((num >> 24) & 0xff) |
        //decallage du 2e octet en 3e position
        ((num << 8) & 0xff0000) |
        //decallage du 3e octet en 2e position
        ((num >> 8) & 0xff00) |
        //decallage du 1er octet en 4e position
        ((num << 24) & 0xff000000);

    return res;

}//toLowIndian()


unsigned int lireEntier(long tailleBloc, long nbBlocs, FILE* ficIn) {

    unsigned int res = 0;

    //Lecture d'une entrée  (format MNIST : Big Indian)
    if (fread(&res, tailleBloc, nbBlocs, ficIn) != nbBlocs) {
        perror("Erreur de lecture d'entier dans le fichier d'entree.");
        exit(EXIT_FAILURE);
    }//if

    //passage au format Low Indian (pour processeurs type Intel)
    res = toLowIndian(res);

    return res;

}//lireEntier()