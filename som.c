#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <math.h> 
#include <time.h> 
#include "som.h" 

int max(int a, int b) { 

    if (a >= b) { 
        return a; 
    } 
    else { 
        return b; 
    }
} 

int min(int a, int b) { 

    if (a <= b) { 
        return a; 
    } 
    else { 
        return b; 
    }
} 

float genRand(int scale) { 
    return (float) rand() * (float) scale / (float) RAND_MAX; 
} 

void printArray(double* arr, int len) { 

    for (int i = 0; i < len; i++) { 
        printf("%d. %lf \n", i, arr[i]); 
    }
} 

int checkInArray(int a, int* arr, int len) { 

    if (len != 0) { 
        for (int i = 0; i < len; i++) { 
            if (arr[i] == a) { 
                return 1; 
            }
        } 
    } 
    return 0; 
} 

int getLength(int num) { 
    
    char str[20];
    sprintf(str, "%d", num); 
    int maxLen = strlen(str); 
    // printf("%s %d \n", str, maxLen); 
    return maxLen; 
    
}

Data* readFile(FILE* fp, int* catOrig, int dims, int numCatOrig) { 

    double** examples = (double**) malloc(sizeof(double*) * 1); 
    char** names = (char**) malloc(sizeof(char*) * 1); 
    char** features = (char**) malloc(sizeof(char*) * dims); 
    int k = -1; 
    int flag = 0; 
    while (feof(fp) != 1) { 
        char temp[250]; 
        fgets(temp, 250, fp); 
        // printf("%s \n", temp); 
        if (strlen(temp) < 20) { 
            continue; 
        }
        char* point = strtok(temp, ","); 

        if (flag == 0) { 
            int j = 0; 
            int kj = 0; 
            while (point != NULL) { 
                if (checkInArray(j, catOrig, numCatOrig) != 1) { 
                    features[kj] = (char*) malloc(sizeof(char) * (strlen(point) + 1)); 
                    strcpy(features[kj], point); 
                    kj += 1; 
                } 
                j += 1; 
                point = strtok(NULL, ","); 
            }
            flag = 1; 
            continue; 
        } 
        k += 1; 
        if (k != 0) { 
            examples = (double**) realloc(examples, sizeof(double*) * (k + 1)); 
            names = (char**) realloc(names, sizeof(char*) * (k + 1)); 
        }
        examples[k] = (double*) malloc(sizeof(double) * dims); 
        
        int j = 0; 
        int kj = 0; 
        while (point != NULL) 
        { 
            if (checkInArray(j, catOrig, numCatOrig) != 1) { 
                examples[k][kj] = strtod(point, NULL); 
                kj += 1; 
            } 
            else { 
                if (j == 0) { 
                    names[k] = (char*) malloc(sizeof(char) * strlen(point) + 1); 
                    strcpy(names[k], point); 
                }
            }
            
            j++; 
            point = strtok(NULL, ","); 
        } 
    } 

    // printf("Number of training examples: %d \n", k + 1); 
    Data* data = (Data*) malloc(sizeof(Data) * 1); 
    data -> examples = examples; 
    data -> names = names; 
    data -> dims = dims; 
    data -> num = k + 1; 
    data -> cat = (int*) malloc(sizeof(int) * 1); 
    data -> numCat = 0; 
    data -> features = features; 

    return data; 
}

Data* genRandData(int dims) { 

    srand(time(0)); 
    int num = (int) genRand(20); 
    double** examples = (double**) malloc(sizeof(double*) * num); 
    printf("Num = %d \n", num); 
    for (int i = 0; i < num; i++) { 
        examples[i] = (double*) malloc(sizeof(double) * dims); 
        for (int j = 0; j < dims; j++) { 
            examples[i][j] = genRand(255); 
        }
    } 

    for (int i = 0; i < num; i++) { 
        printf("%d. %f %f %f \n", i + 1, examples[i][0], examples[i][1], examples[i][2]); 
    } 

    Data* data = (Data*) malloc(sizeof(Data) * 1); 
    
    
    data -> examples = examples; 
    data -> dims = dims; 
    data -> num = num; 
    data -> cat = (int*) malloc(sizeof(int) * 1); 
    data -> numCat = 0; 

    return data; 
} 

void getRanges(Data* data) { 

    double** ranges = (double**) malloc(sizeof(double*) * data -> dims); 
    for (int i = 0; i < data -> dims; i++) { 
        ranges[i] = (double*) malloc(sizeof(double) * 2); 
        double currMin = pow(10, 9); 
        double currMax = -pow(10, 9); 
        for (int j = 0; j < data -> num; j++) { 
            if (data -> examples[j][i] < currMin) { 
                currMin = data -> examples[j][i]; 
            } 
            if (data -> examples[j][i] > currMax) { 
                currMax = data -> examples[j][i]; 
            }
        } 
        ranges[i][0] = currMin; 
        ranges[i][1] = currMax; 
    } 

    data -> ranges = ranges; 
}

double getDistance(double* currRec, double* currUnit, int dims) { 

    // double* currRec = data[index]; 
    // double* currUnit = grid[h][w]; 
    double sum = 0; 
    for (int i = 0; i < dims; i++) { 
        sum += pow((currRec[i] - currUnit[i]), 2); 
    } 
    return sum; 
} 

int* getBMU(int index, double** examples, Som* som) { 

    double* currRec = examples[index]; 
    double minSum = pow(10, 9); 
    int minH = -1; 
    int minW = -1; 
    // printArray(currRec, som -> dims); 
    for (int i = 0; i < som -> height; i++) { 
        for (int j = 0; j < som -> width; j++) { 
            double currSum = getDistance(currRec, som -> grid[i][j], som -> dims); 
            // printf("%lf %lf \n", currSum, minSum); 
            if (currSum < minSum) { 
                minSum = currSum; 
                minH = i; 
                minW = j; 
            }
        }
    } 
    // printf("minH = %d, minW = %d \n", minH, minW); 

    int* ret = (int*) malloc(sizeof(int) * 2); 
    ret[0] = minH; 
    ret[1] = minW; 

    return ret; 
} 

double getSigma(double sigma0, double distDecay, int currIter) { 

    return sigma0 * exp(- distDecay * (double) currIter); 
} 

double getAlpha(double alpha0, double learnDecay, int currIter) { 

    // printf("In getAlpha : %lf \n", exp(- learnDecay * (double) currIter)); 
    return alpha0 * exp(- learnDecay * (double) currIter); 
} 

double getNDF(Som* som, int a, int b, int i, int j, double sigma) { 

    double dist = 0; 
    for (int k = 0; k < som -> dims; k++) { 
        dist += pow((som -> grid[a][b][k] - som -> grid[i][j][k]), 2); 
    } 
    // printf("In getNDF: %lf %lf \n", dist, sigma); 
    return exp(-1 * dist / (2 * pow(sigma, 2))); 
}

void initialiseGrid(Data* data, Som* som) { 

    // printf("In initialiseGrid, %d %d %d \n", som -> height, som -> width, som -> dims); 
    int num = data -> num; 
    srand(time(0)); 
    double*** grid = (double***) malloc(sizeof(double**) * som -> height); 
    for (int i = 0; i < som -> height; i++) { 
        grid[i] = (double**) malloc(sizeof(double*) * som -> width); 
        for (int j = 0; j < som -> width; j++) { 
            int r = (int) genRand(num); 
            grid[i][j] = (double*) malloc(sizeof(double) * som -> dims);; 
            // printf("%d, %d. %d \n", i, j, r); 
            for (int k = 0; k < som -> dims; k++) { 
                grid[i][j][k] = data -> examples[r][k]; 
            } 

            // printf("Printing datapoint: \n"); 
            // printArray(data[r], som -> dims); 
            // printf("Printing grid unit: \n"); 
            // printArray(grid[i][j], som -> dims); 
        } 
    } 

    som -> grid = grid; 
} 

void initialiseGridRand(Data* data, Som* som) { 

    int num = data -> num; 
    srand(time(0)); 
    double*** grid = (double***) malloc(sizeof(double**) * som -> height); 
    for (int i = 0; i < som -> height; i++) { 
        grid[i] = (double**) malloc(sizeof(double**) * som -> width); 
        for (int j = 0; j < som -> width; j++) { 
            grid[i][j] = (double*) malloc(sizeof(double) * som -> dims); 
            for (int k = 0; k < som -> dims; k++) { 
                grid[i][j][k] = genRand(data -> ranges[k][1] - data -> ranges[k][0]) + data -> ranges[k][0]; 
            }
        }
    } 

    som -> grid = grid; 
}

void update(int index, Data* data, Som* som, int step, double alpha, double sigma, int a, int b) { 

    int al = max(0, a - step); 
    int ah = min(som -> height, a + step); 
    int bl = max(0, b - step); 
    int bh = min(som -> width, b + step); 

    // printf("%d %d %d %d %d %d %d %d \n", al, ah, bl, bh, a - step, a + step, b - step, b + step); 
    for (int i = al; i < ah; i++) { 
        for (int j = bl; j < bh; j++) { 
            double ndf = getNDF(som, a, b, i, j, sigma); 
            double mult = alpha * ndf; 
            // printf("%lf %lf %lf \n", ndf, mult, alpha); 
            // if (mult != (double) 0) { 
            //     printf("mult : %lf, ndf : %lf, alpha : %lf \n", mult, ndf, alpha); 
            // }
            for (int k = 0; k < som -> dims; k++) { 
                double add; 
                if (checkInArray(k, data -> cat, data -> numCat) == 1) { 
                    add = (int) mult * (data -> examples[index][k] - som -> grid[i][j][k]); 
                } 
                else { 
                    add = mult * (data -> examples[index][k] - som -> grid[i][j][k]); 
                }
                som -> grid[i][j][k] += add; 
                if (checkInArray(k, data -> cat, data -> numCat) == 1) { 
                    printf("NEW %lf \n", som -> grid[i][j][k]); 
                } 
            }
        }
    } 
} 

Som* trainSom(Data* data, int epochs, double alpha, double sigma, int height, int width, double learnDecay, double distDecay, int dims, int num, int gridInitialise, int step) { 

    // printf("%d %d %d \n", height, width, dims); 
    Som* som = (Som*) malloc(sizeof(Som) * 1); 
    som -> alpha0 = alpha; 
    som -> sigma0 = sigma; 
    som -> epochs = epochs; 
    som -> height = height; 
    som -> width = width; 
    som -> learnDecay = learnDecay; 
    som -> distDecay = distDecay; 
    som -> dims = dims; 
    som -> step = step; 
    printf("SOM parameters set! \n"); 
    // printf("%d %d %d %d \n", som -> height, som -> width, height, width); 
    
    if (gridInitialise == 0) { 
        initialiseGrid(data, som); 
        printf("Grid initialised using training examples! \n"); 
    } 
    else { 
        initialiseGridRand(data, som); 
        printf("Grid initialised using random values! \n"); 
    }
    // for (int i = 0; i < som -> height; i++) { 
    //     for (int j = 0; j < som -> width; j++) { 
    //         printArray(som -> grid[i][j], som -> dims); 
    //     }
    // }

    for (int i = 0; i < epochs; i++) { 
        printf("Epoch %d of %d \n", i + 1, epochs); 
        printf("\t Learning rate: %lf \n", alpha); 
        printf("\t Sigma: %lf \n", sigma); 
        for (int j = 0; j < num; j++) { 
            
            int* bmu = (int*) malloc(sizeof(int) * 2); 
            bmu = getBMU(j, data -> examples, som); 
            int a = bmu[0]; 
            int b = bmu[1]; 
            // printf("%d %d %d \n", j, a, b); 
            // printArray(data[j], som -> dims); 
            // printArray(som -> grid[a][b], som -> dims); 

            update(j, data, som, step, alpha, sigma, a, b); 
        } 
        alpha = getAlpha(som -> alpha0, learnDecay, i); 
        sigma = getSigma(som -> sigma0, distDecay, i); 
        // printf("NEW %lf %lf \n", alpha, sigma); 
    } 

    return som; 
} 

void getClusters(Som* som, Data* data) { 

    int** groups = (int**) malloc(sizeof(int*) * som -> height); 
    char**** countries = (char****) malloc(sizeof(char***) * som -> height);  

    for (int i = 0; i < som -> height; i++) { 
        groups[i] = (int*) malloc(sizeof(int) * som -> width); 
        countries[i] = (char***) malloc(sizeof(char**) * som -> width); 
        for (int j = 0; j < som -> width; j++) { 
            groups[i][j] = 0; 
        }
    } 
    for (int i = 0; i < data -> num; i++) { 
        int* bmu = (int*) malloc(sizeof(int) * 2); 
        bmu = getBMU(i, data -> examples, som); 
        int a = bmu[0]; 
        int b = bmu[1]; 
        // printf("%d %d %d \n", i, a, b); 
        groups[a][b] += 1; 
        if (groups[a][b] == 1) { 
            countries[a][b] = (char**) malloc(sizeof(char*) * 1); 
        } 
        else { 
            countries[a][b] = (char**) realloc(countries[a][b], sizeof(char*) * groups[a][b]); 
        } 
        countries[a][b][groups[a][b] - 1] = (char*) malloc(sizeof(char) * strlen(data -> names[i]) + 1); 
        strcpy(countries[a][b][groups[a][b] - 1], data -> names[i]); 
    } 

    som -> groups = groups; 
    som -> countries = countries; 
} 

void printClusters(Som* som) { 

    int max = - pow(10, 9); 
    for (int i = 0; i < som -> height; i++) { 
        for (int j = 0; j < som -> width; j++) { 
            if (som -> groups[i][j] > max) { 
                max = som -> groups[i][j]; 
            }
        }
    }  

    int maxLen = getLength(max); 

    for (int i = 0; i < som -> height; i++) { 
        for (int j = 0; j < som -> width; j++) { 
            printf("| "); 
            printf("%d", som -> groups[i][j]); 
            int currLen = getLength(som -> groups[i][j]); 
            // printf("maxLen = %d, currLen = %d, num = %d \n", maxLen, currLen, som -> groups[i][j]); 
            for (int k = 0; k < maxLen - currLen + 1; k++) { 
                printf(" "); 
            } 
        } 
        printf("| \n"); 
        for (int k = 0; k < (maxLen + 2 + 1) * som -> width + 1; k++) { 
            printf("-"); 
        } 
        printf("\n"); 
    }
} 

void printCountries(Som* som) { 

    for (int i = 0; i < som -> height; i++) { 
        for (int j = 0; j < som -> width; j++) { 
            printf("Cluster %d %d \n", i, j); 
            for (int k = 0; k < som -> groups[i][j]; k++) { 
                printf("%d. %s \n", k + 1, som -> countries[i][j][k]); 
            }
        } 
    } 
}

