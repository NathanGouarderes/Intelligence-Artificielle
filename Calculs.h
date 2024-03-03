#ifndef CALCULS_H
#define CALCULS_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float *flatten(unsigned char **ma_matrice);
void normalize(float *arr, int size);
float relu(float x);
float *softmax(float *arr, int size);
float *calculerDense(float *entree, float **poids, float *biais, int nbNeurones);
float **allouerMatricePoids(int lignes, int colonnes);
float *allouerBiais(int lignes);
void libererMatricePoids(float **matrice, int lignes);
void libererBiais(float *vecteur);
double generateGaussianNoise(double mu, double sigma);
void initializeWeightsGlorotNormal(float **weights, int inputSize, int outputSize);

#endif // !CALCULS_H
