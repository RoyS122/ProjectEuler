#include <stdio.h>
#include <stdlib.h>


typedef struct {
    unsigned int *array;
    unsigned int length;
} DynArray;

void append(DynArray *da, unsigned int val, unsigned int buffersize) { 
    if (da->length == 0) {
        da->array = malloc(buffersize * sizeof(unsigned int));
    } else if (da->length % buffersize == 0) { 
        da->array = realloc(da->array, (da->length + buffersize) * sizeof(unsigned int));
    }
    da->array[da->length++] = val;
}

int isPrime(const unsigned int i, DynArray *primes) {
    for(int j = 0; j < primes->length; j ++) {
        if(i % primes->array[j] == 0) {
            return 0;
        }
    }
    append(primes, i, 10);
    return 1;
}
int checkGoldbach(const unsigned int i, DynArray *primes) {
    if(i % 2 == 0) {
        return 1;
    }
    
    if(isPrime(i, primes)) {
        return 1; 
    }

    for(int p = 0; p < primes->length; p ++) {
        int k;
        for(k = 0; i > primes->array[p] + 2 * (k * k); k ++);
        if (i == primes->array[p] + 2 * (k * k)) {
            return 1;
        }
    }

    return 0;
}

int solveProblem() {
    DynArray primes = {NULL, 0}; 
    append(&primes, 2, 10);
    int i;
    for(i = 2; checkGoldbach(i, &primes) ; i ++);
    free(primes.array);
    return i;
}

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

int main() {
    printf("Solution: %i\n", solveProblem());
    wait();
}