// Compile using: gcc driver.c som.c 


#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 
#include <time.h> 
#include "som.h" 

int main() { 

    int dims = 9; 
    int* catOrig = (int*) malloc(sizeof(int) * 3); 
    catOrig[0] = 0; 
    catOrig[1] = 1; 
    catOrig[2] = 2; 
    int numCatOrig = 3; 
    
    FILE *fp; 
    fp = fopen("happiness2015.csv", "r"); 
    
    if (fp == NULL) 
    { 
        printf ("Error"); 
        return 0; 
    } 

    Data* data = readFile(fp, catOrig, dims, numCatOrig); 
    printf("Training data read! \n\n"); 
    printf("Number of training examples: %d \n\n", data -> num); 
    printf("Features considered: \n"); 
    for (int i = 0; i < data -> dims; i++) { 
        printf("%d. %s \n", i + 1, data -> features[i]); 
    } 
    
    getRanges(data); 
    printf("Training data analysed! \n"); 
    
    int epochs = 10; 
    double alpha0 = 0.01; 
    double sigma0 = 5; 
    int height = 3; 
    int width = 3; 
    double learnDecay = 0.01; 
    double distDecay = 0.01; 
    int gridInitialise = 1; // 1 for random initialisation 
    int step = 3; 
    Som* som = trainSom(data, epochs, alpha0, sigma0, height, width, learnDecay, distDecay, dims, data -> num, gridInitialise, step); 

    printf("Som training complete! \n \n"); 

    getClusters(som, data); 

    printf("Clustering results: \n \n"); 
    
    printClusters(som); 
    printCountries(som); 
    printf("\n \n"); 
}