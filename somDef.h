#include <stdio.h> 

typedef struct Som { 
    double*** grid; 
    int height; 
    int width; 
    int dims; 
    double alpha0; 
    double sigma0; 
    double learnDecay; 
    double distDecay; 
    int epochs; 
    int step; 
    int** groups; 
    char**** countries; 
} Som; 

typedef struct Data { 
    double** examples; 
    int dims; 
    int num; 
    int* cat; 
    int numCat; 
    double** ranges; 
    char** names; 
    char** features; 
} Data; 