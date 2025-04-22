#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int *array;
    unsigned int length;
} DynArray;

void append(DynArray *da, unsigned int val) { 
    if (da->length == 0) {
        da->array = malloc(1000 * sizeof(unsigned int));
    } else if (da->length % 1000 == 0) { 
        da->array = realloc(da->array, (da->length + 1000) * sizeof(unsigned int));
    }
    da->array[da->length++] = val;
}

unsigned int GetPentagonal(int n) {
    return (unsigned int)(n * (3 * n - 1) / 2);
}

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

int isPentagon(unsigned int c, const DynArray *pentagonList) { // searching with dichotomy the number in the array and result is if the number is pantagonal
    int left = 0, right = pentagonList->length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (pentagonList->array[mid] == c) return 1;
        if (pentagonList->array[mid] < c) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

int checkPentagonPair(unsigned int a, unsigned int b, const DynArray *pentagonList) { // check if a pair of number is pentagon
    return (isPentagon(a, pentagonList) && isPentagon(b, pentagonList));
}

int solveProblem() {
    int res = 0;
    int p_solved = 0;
    DynArray arr = {NULL, 0};
    
    for(int l = 1; !p_solved; l++) {
        unsigned int p = GetPentagonal(l);
        append(&arr, p);
        
        if (arr.length <= 1) {
            continue;
        }
        
        for(int a = 0; a < arr.length - 1; a++) {
            for(int b = a + 1; b < arr.length; b++) {
                unsigned int sum = arr.array[a] + arr.array[b];
                unsigned int diff = abs(arr.array[a] - arr.array[b]);
                if (isPentagon(sum, &arr) && isPentagon(diff, &arr)) {
                    printf("Pair found: P%d = %u and P%d = %u\n", 
                           a+1, arr.array[a], b+1, arr.array[b]);
                    printf("Sum: %u, Difference: %u\n", sum, diff);
                    res = diff;
                    p_solved = 1;
                    break;
                }
            }
            if (p_solved) break;
        }
    }
    
    free(arr.array);
    return res;
}

int main() {
    printf("Result: %i\n", solveProblem());
    wait();
    return 0;
}