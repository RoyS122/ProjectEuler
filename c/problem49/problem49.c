#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

bool is_permutation(unsigned int a, unsigned int b) {
    int count[10] = {0};
    while (a > 0) { count[a%10]++; a /= 10; }
    while (b > 0) { count[b%10]--; b /= 10; }
    for (int i = 0; i < 10; i++) if (count[i] != 0) return false;
    return true;
}

void find_sequence(DynArray primes) {
    for (unsigned int i = 0; i < primes.length; i++) {
        unsigned int p1 = primes.array[i];
        if (p1 < 1000) continue;

        for (unsigned int j = i+1; j < primes.length; j++) {
            unsigned int p2 = primes.array[j];
            unsigned int diff = p2 - p1;
            unsigned int p3 = p2 + diff;

            if (p3 > 9999) continue;
            if (!contains(p3, &primes)) continue;
            if (!is_permutation(p1, p2)) continue;
            if (!is_permutation(p1, p3)) continue;
            if (p1 == 1487) continue;

            
            printf("12-digit number: %u%u%u\n", p1, p2, p3);
            return;
        }
    }
    printf("No sequence found!\n");
}
void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}
int main() {
    DynArray primes = {NULL, 0};
    append(&primes, 2, 1000);
    for(int i = 3; i < 10000; i += 2) isPrime(i, &primes);
    
    find_sequence(primes);
    wait();
    free(primes.array);
    
    return 0;
}