#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include "somDef.h" 

int max(int a, int b); 
int min(int a, int b); 
float genRand(int scale); 
void printArray(double* arr, int len); 
int checkInArray(int a, int* arr, int len); 
int getLength(int num); 
Data* readFile(FILE* fp, int* catOrig, int dims, int numCatOrig); 
Data* genRandData(int dims); 
void getRanges(Data* data); 
double getDistance(double* currRec, double* currUnit, int dims); 
int* getBMU(int index, double** examples, Som* som); 
double getSigma(double sigma, double distDecay, int currIter); 
double getAlpha(double alpha, double learnDecay, int currIter); 
double getNDF(Som* som, int a, int b, int i, int j, double sigma); 
void initialiseGrid(Data* data, Som* som); 
void initialiseGridRand(Data* data, Som* som); 
void update(int index, Data* data, Som* som, int step, double alpha, double sigma, int a, int b); 
Som* trainSom(Data* data, int epochs, double alpha, double sigma, int height, int width, double learnDecay, double distDecay, int dims, int num, int gridInitialise, int step); 
void getClusters(Som* som, Data* data); 
void printClusters(Som* som); 
void printCountries(Som* som); 