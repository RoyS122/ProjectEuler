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

int getDigits(unsigned int n, int digits[]) {
    int len = 0;
    while (n > 0) {
        digits[len++] = n % 10;
        n /= 10;
    }
    return len;
}
unsigned int makeNumber(int digits[], int length) {
    unsigned int n = 0;
    for (int i = length - 1; i >= 0; i--) {
        n = n * 10 + digits[i];
    }
    return n;
}

int positionsSameDigit(int digits[], int mask, int length) {
    int ref = -1;
    for (int i = 0; i < length; i++) {
        if (mask & (1 << i)) {
            if (ref == -1)
                ref = digits[i];
            else if (digits[i] != ref)
                return 0; 
        }
    }
    return 1; 
}


int check(unsigned int nbr, DynArray *primeArray) {
    int digits[10];
    int length = getDigits(nbr, digits);

    if (length < 3) return 0;

    int maxMask = (1 << length);
    int validGroups = 0; 

    for (int mask = 1; mask < maxMask; mask++) {
        int bitCount = __builtin_popcount(mask);

        if (bitCount < 2 || bitCount > 4) continue;
        if (mask & 1) continue; 
        if (!positionsSameDigit(digits, mask, length)) continue;

        int count = 0;

        for (int d = 0; d <= 9; d++) {
            if ((mask & (1 << (length - 1))) && d == 0)
                continue;

            int tmp[10];
            for (int i = 0; i < length; i++)
                tmp[i] = (mask & (1 << i)) ? d : digits[i];

            unsigned int val = makeNumber(tmp, length);

            if (contains(val, primeArray))
                count++;
        }

        if (count >= 8) {
            validGroups++;
        }
    }

    return validGroups;
}


unsigned int solveProblem() {
    DynArray primes = {NULL, 0};
    append(&primes, 2, 1000);
    for(int i = 3; i < 1000000; i += 2) isPrime(i, &primes);

    for (int i = 0; i < primes.length; i++) {
    unsigned int n = primes.array[i];
    int groups = checkNumberRotation(n, &primes);
        if (groups > 0) {
            printf("%u -> %d groupes de 8 primes\n", n, groups);
        }
    }   

    unsigned int res = 0;

    return res;
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