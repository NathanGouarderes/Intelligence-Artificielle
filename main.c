/*******************************************************Le fich
Nom ......... : main.c
Role ........ : Programme principal executant la lecture
                d'une image bitmap
Auteur ...... : Frédéric CHATRIE
Version ..... : V1.1 du 1/2/2021
Licence ..... : /

Compilation :
make veryclean
make
Pour exécuter, tapez : ./all
********************************************************/

#include "Bmp2Matrix.h"
#include "OuvertureFichiers.h"
#include "Calculs.h"

#define NB_NEURONES_ENTREE 784
#define NB_NEURONES_C1 1176   // Première couche
#define NB_NEURONES_C2 256    // Deuxième couche
#define NB_NEURONES_SORTIE 10 // Troisième couche (sortie)

int main(int argc, char *argv[])
{

    BMP bitmap;
    FILE *pFichier = NULL;

    pFichier = fopen("5_0.bmp", "rb"); // Ouverture du fichier contenant l'image
    if (pFichier == NULL)
    {
        printf("%s\n", "0_0.bmp");
        printf("Erreur dans la lecture du fichier\n");
    }
    LireBitmap(pFichier, &bitmap);
    fclose(pFichier); // Fermeture du fichier contenant l'image

    ConvertRGB2Gray(&bitmap);
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 28; j++)
        {
            printf("%d ", bitmap.mPixelsGray[i][j]); // Ici je regarde la forme qu'à mon chiffre
        }
        printf("\n");
    }
    printf("%d\n", bitmap.mPixelsGray[10][10]);

    for (int i = 0; i < 5; i++)
    {
        printf("\n");
    }

    printf("C'est le flatten \n\n");

    // float *mon_vecteur = (float *)malloc(784 * sizeof(float));
    float *mon_vecteur = flatten(bitmap.mPixelsGray); // Ici j'appaltie mon image sur une seule dimmension
    printf("Donnees avant normalisation :\n");
    for (int i = 0; i < 784; i++)
    {
        printf("\n %f", mon_vecteur[i]); // Ici je vérifiais mon vecteur
    }

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("\n");
    // }
    // printf("C'est le vecteur\n");

    // for (int i = 0; i < 28 * 28; i++)
    // {
    //     printf("%f ", mon_vecteur[i]); // ici j'affichais mon image appaltie
    // }
    // printf("le vecteur est fini\n");

    normalize(mon_vecteur, NB_NEURONES_ENTREE); // Ici je normalise comme on le faisait en python en divisant mon vecteur par 255.0

    for (int i = 0; i < NB_NEURONES_ENTREE; i++)
    {
        printf("Mon vecteur normalise : %f\n", mon_vecteur[i]); // vérification de la normalisation des données (ici on est bon)
    }

    for (int i = 0; i < 5; i++)
    {
        printf("\n");
    }

    char *chemin_poids = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense.txt";
    char *chemin_biais = "C:/Users/natha/Documents/Junia/IA/layers/layerbiasdense.txt";
    char *chemin_poids1 = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense_1.txt";
    char *chemin_biais1 = "C:/Users/natha/Documents/Junia/IA/layers/layerbiasdense_1.txt";
    char *chemin_poids2 = "C:/Users/natha/Documents/Junia/IA/layers/layer_weightdense_2.txt";
    char *chemin_biais2 = "C:/Users/natha/Documents/Junia/IA/layers/layerbiasdense_2.txt";

    float **matricePoids = ouvrirPoids(chemin_poids, 784, 1176); // C'est dans le nom de la méthode. Je me suis calqué sur ce que j'avais fait en python
    float *matriceBiais = ouvertureBiais(chemin_biais, 1176);
    printf("\nMatrice de poids\n");
    // for (int i = 0; i < 784; i++)
    // {
    //     for (int j = 0; j < 1176; j++)
    //     {
    //         printf("%f ", matricePoids[i][j]);
    //     }
    // }
    // printf("\nMatrice de biais\n");
    // for (int i = 0; i < 1176; i++)
    // {
    //     printf("%f\n", matriceBiais[i]);
    // }

    // float **matricePoids1 = ouvrirPoids(chemin_poids1, NB_NEURONES_C1, NB_NEURONES_C2); //
    // float *matriceBiais1 = ouvertureBiais(chemin_biais1, NB_NEURONES_C2);

    // float **matricePoids2 = ouvrirPoids(chemin_poids2, NB_NEURONES_C2, NB_NEURONES_SORTIE); //
    // float *matriceBiais2 = ouvertureBiais(chemin_biais2, NB_NEURONES_SORTIE);

    float *sortieCoucheDense1 = calculerDense(mon_vecteur, matricePoids, matriceBiais, NB_NEURONES_ENTREE);
    // float *sortieCoucheDense2 = calculerDense(sortieCoucheDense1, matricePoids1, matriceBiais1, NB_NEURONES_C2);
    // float *sortieCoucheDense3 = calculerDense(sortieCoucheDense2, matricePoids2, matriceBiais2, NB_NEURONES_SORTIE);y
    printf("\nSortie couhe dense 1\n");
    for (int i = 0; i < NB_NEURONES_C1; i++)
    {
        printf("%f ", sortieCoucheDense1[i]);
    }

    printf("\nNB_NEURONES_ENTREE x NB_NEURONES_C1 = %d", NB_NEURONES_ENTREE * NB_NEURONES_C1);

    // for (int i = 0; i < 256; i++)
    // {
    //     //printf("\nLa valeur de sortieCoucheDense1 : %f\nLa valeur de sortieSoftMax : %f\n", sortieCoucheDense1[i], sortieSoftMax[i]);
    // }

    int prediction = 0;
    float max_prediction = sortieCoucheDense1[0];

    for (int i = 0; i < NB_NEURONES_SORTIE; i++)
    {
        // printf("\nprediction pour %d est : %f\n", i, sortieCoucheDense1[i]);

        if (sortieCoucheDense1[i] > max_prediction)
        {
            prediction = i;
            max_prediction = sortieCoucheDense1[i];
            // printf("Prédiction : %f \nmax_prediction : %f\n", prediction, max_prediction);
        }
        // printf("\nsortieCoucheDense[i] : %f \nPrediction : %d \nmax_prediction : %f\n", sortieCoucheDense1[i], prediction, max_prediction);
    }
    printf("\nLa prediction finale est : %d\n", prediction);
    DesallouerBMP(&bitmap);

    return 0;
}
