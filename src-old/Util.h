#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

//renvoi d'une valeur al�atoire entre 2 bornes
//avec min pouvant �tre une valeur n�gative.
double nombreRdm(double min, double max);

//fonction de conversion d'un entier Big Indian � un Low Indian
unsigned int toLowIndian(unsigned int val);

//lecture d'un entier dans un fichier binaire puis
//conversion de celui-ci du format Big Indian au Low Indian
unsigned int lireEntier(long tailleBloc, long nbBlocs, FILE* ficIn);

#endif //UTIL_H_INCLUDED