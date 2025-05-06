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
    for(int j = 0; j < primes->length; j++) {
        if(primes->array[j] * primes->array[j] > i) break;
        if(i % primes->array[j] == 0) return 0;
    }
    append(primes, i, 1000);
    return 1;
}

int contains(const unsigned int n, const DynArray *da) {
    int left = 0, right = da->length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (da->array[mid] == n) return 1;
        if (da->array[mid] < n) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

unsigned int MaxStreakPrime(DynArray *primes) {
    unsigned int max_res = 0; 
    unsigned int max_streak = 0;
    
    for(int start = 0; start < primes->length; start ++) {
        unsigned int streak_length = 0;
        unsigned int res = 0;
        for(unsigned int i = start; i < primes->length && res + primes->array[i] < 1000000; i ++) {
            streak_length += 1;
            res += primes->array[i];
            if(streak_length > max_streak && contains(res, primes)) {
                max_streak = streak_length;
                max_res = res;
            }
        }
    }
    return max_res;
}





unsigned int solveProblem() {
    DynArray primes = {NULL, 0};
    append(&primes, 2, 1000);
    for(int i = 3; i < 1000000; i += 2) isPrime(i, &primes);

    unsigned int maxdecompvalue = MaxStreakPrime(&primes);
    free(primes.array);
    return maxdecompvalue;
}




void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}


int main() {
    
    printf("%i \n", solveProblem());
    wait();
    
    return 0;
}