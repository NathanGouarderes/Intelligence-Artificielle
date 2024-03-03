#ifndef OUVERTURE_FICHIERS_H
#define OUVERTURE_FICHIERS_H
#include <stdio.h>
#include <stdlib.h>
#include "Bmp2Matrix.h"

float **ouvrirPoids(char *chemin, int lignes, int colonnes);
float *ouvertureBiais(char *chemin, int lignes);
void chargerToutesLesImages(const char *folder_path, int nb_digit, int nb_version);

#endif // !OUVERTURE_FICHIERS_H