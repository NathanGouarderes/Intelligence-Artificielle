#include "OuvertureFichiers.h"
#include <stdio.h>
#include <stdlib.h>
#include "Bmp2Matrix.h"

#define NB_LIGNES 1176
#define NB_COLONNES 256

float **ouvrirPoids(char *chemin, int lignes, int colonnes)
{
    int valeurLues = 0;
    printf("Execution de la methode ouvrirPoids()");
    FILE *fichier;
    // char *chemin_poids = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense_1.txt";
    fichier = fopen(chemin, "r");

    float **matrice = (float **)malloc(lignes * sizeof(float *));
    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (float *)malloc(colonnes * sizeof(float));
    }

    printf("\nJe suis ce chemin %s\n", chemin);

    // Lecture de la matrice depuis le fichier
    int nombreLignes = 0;
    int nombreColonnes = 0;
    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            if (fscanf(fichier, "%f", &matrice[i][j]) != 1)
            {
                perror("Erreur dans la lecture du fichier");
                printf("Erreur ligne %d, colonne %d\n pour le fichier %s", i + 1, j + 1, chemin);
                printf("\nVoila l'erreur : %f", matrice[i][j]);

                fseek(fichier, 0, SEEK_SET);
                int c;
                while ((c = fgetc(fichier)) != EOF)
                {
                    putchar(c);
                }
                valeurLues++;

                fclose(fichier);
                return NULL;
            }
            nombreColonnes = j;
        }
        nombreLignes = i;
    }
    printf("\nLe fichier %s fait : %d lignes et %d colonnes", chemin, nombreLignes, nombreColonnes);

    int nbLignes = 0;
    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            // printf("%f ", matrice[i][j]);
        }
        nbLignes = i;
    }
    printf("\n\nFin de la lecture du fichier : %s et contien %d lignes \n", chemin, nbLignes);

    return matrice;
}

float *ouvertureBiais(char *chemin, int lignes)
{
    printf("Execution de la methode ouvertureBiais()");

    FILE *fichier;
    // char *chemin_biais = "C:/Users/natha/Documents/Junia/IA/layers/layerbiasdense_1.txt";
    fichier = fopen(chemin, "r");

    float *biais = (float *)malloc(lignes * sizeof(float));
    for (int i = 0; i < lignes; i++)
    {
        if (fscanf(fichier, "%f", &biais[i]) != 1)
        {
            perror("Erreur dans la lecture du fichier");
            printf("Erreur ligne %d", i + 1);
            fclose(fichier);
            exit(0);
        }
    }

    // printf("\nLecture de mes biais depuis la methode\n");
    //  for (int i = 0; i < lignes; i++)
    //  {
    //      printf("%f ", biais[i]);
    //  }
    return biais;
}
