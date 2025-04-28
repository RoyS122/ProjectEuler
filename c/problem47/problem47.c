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
        if(primes->array[j] * primes->array[j] > i) {
            break;
        }
        if(i % primes->array[j] == 0) {
            return 0;
        }
    }
    append(primes, i, 1000);
    return 1;
}
int ThereFourDecompPrime(unsigned int i, DynArray *primes) {
    int decompNBR = 0;
    
    for(int j = 0; j < primes->length; j++) {
        if (primes->array[j] * primes->array[j] > i) 
            break; 
        if (i % primes->array[j] == 0) {
            decompNBR++;
            if (decompNBR > 4) 
                return 0;
            while (i % primes->array[j] == 0) 
                i /= primes->array[j]; 
        }
    }
    if (i > 1) decompNBR++;
    return decompNBR == 4;
}

int solveProblem() {
    DynArray primes = {NULL, 0};
    append(&primes, 2, 1000);
    int streak_count = 0;
    int streak_start = 0;
    for(int i = 3;streak_count != 4; i ++) {
        if(isPrime(i, &primes)) {
            streak_count = 0;
            continue;
        }
        if(ThereFourDecompPrime(i, &primes)) {
            if (streak_count == 0) streak_start = i;
           
            streak_count ++;
        }else{
            streak_count = 0;
        }
    }
    free(primes.array); 
    return streak_start;
}

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

int main() {
    printf("Solution: %i\n", solveProblem());
    wait();
}