#include "Calculs.h"

float *flatten(unsigned char **ma_matrice)
{
    printf("Execution de la methode flatten()");

    // ma matrice fait 28 par 28, c'est le nombre de pixels de l'image
    // elle fait 2 dimmensions donc ce sera un float**
    // Il faut applatir la matrice sur une seule dimmension (un vecteur)

    // nombre de colonnes de la matrice
    int width = 28;
    // nombre de lignes de la matrice
    int height = 28;

    // allocation de la memoire pour le vecteur
    float *mon_vecteur = (float *)malloc(height * width * sizeof(float)); // Là mon vecteur attend de recevoir des chiffres
    int index = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // printf("%d ", ma_matrice[i][j]);
            mon_vecteur[index] = (float)ma_matrice[i][j]; // Là je mets chaque point de chaque colonne et de chaque ligne de ma matrice dans mon vecteur pour applatir ma matrice
            // printf("\n Mon vecteur vaut : %f", mon_vecteur);
            index++;
        }
        printf("\n");
    }
    return mon_vecteur;
}

void normalize(float *arr, int size)
{
    printf("Execution de la methode normalize()");
    for (int i = 0; i < size; i++)
    {
        arr[i] /= 255.0;
    }
}

float relu(float x)
{
    // printf("Execution de la methode relu()\n Voila la valeur de x en entree : %f\n", x);

    if (x > 0)
    {
        return x;
    }
    else
    {
        return 0;
    }
}

float *softmax(float *arr, int size)
{
    printf("Execution de la methode softmax()");

    float sum = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += exp(arr[i]);
    }

    float *result = malloc(size * sizeof(float));
    for (int i = 0; i < size; i++)
    {
        result[i] = exp(arr[i]) / sum;
    }
    return result;
}

float *calculerDense(float *entree, float **poids, float *biais, int nbNeurones)
{
    printf("Execution de la methode calculerDense()");

    float *sortie = (float *)malloc(nbNeurones * sizeof(float));
    if (!sortie)
    {
        perror("Allocation mémoire échouée pour sortie");
        exit(EXIT_FAILURE);
    }

    // Initialisation de la sortie à zéro
    for (int i = 0; i < nbNeurones; i++)
    {
        sortie[i] = 0.0;
    }

    for (int i = 0; i < nbNeurones; i++)
    {
        sortie[i] = biais[i];
        for (int j = 0; j < 784; j++)
        {
            sortie[i] = poids[i][j] * entree[j];
            printf("sortie[%d] = %f + %f * %f = %f\n", i, sortie[i], poids[i][j], entree[j], sortie[i]);
        }
        sortie[i] = relu(sortie[i]);
        //  printf("\n%f", sortie[i]);
        //  printf("\ni : %d\n ", i);
    }

    return sortie;
}

float **allouerMatricePoids(int lignes, int colonnes)
{
    float **matrice = (float **)malloc(lignes * sizeof(float *));
    for (int i = 0; i < lignes; i++)
    {
        matrice[i] = (float *)malloc(colonnes * sizeof(float));
    }
    return matrice;
}

float *allouerBiais(int lignes)
{
    return (float *)malloc(lignes * sizeof(float));
}

void libererMatricePoids(float **matrice, int lignes)
{
    for (int i = 0; i < lignes; i++)
    {
        free(matrice[i]);
    }
    free(matrice);
}

void libererBiais(float *vecteur)
{
    free(vecteur);
}

double generateGaussianNoise(double mu, double sigma)
{
    static const double epsilon = 1e-10;
    static const double two_pi = 2.0 * 3.14159265358979323846;
    static double z0, z1;
    static int generate;
    generate = !generate;

    if (!generate)
        return z1 * sigma + mu;

    double u1, u2;
    do
    {
        u1 = rand() * (1.0 / RAND_MAX);
        u2 = rand() * (1.0 / RAND_MAX);
    } while (u1 <= epsilon);

    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}

// Initialisation GlorotNormal pour les poids
void initializeWeightsGlorotNormal(float **weights, int inputSize, int outputSize)
{
    double variance = 2.0 / (inputSize + outputSize);
    double sigma = sqrt(variance);
    for (int i = 0; i < inputSize; i++)
    {
        for (int j = 0; j < outputSize; j++)
        {
            weights[i][j] = (float)generateGaussianNoise(0, sigma);
        }
    }
}
