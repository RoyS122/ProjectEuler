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

DynArray getDigits(unsigned long long val) {
    DynArray res = {NULL, 0};
    
    if(val == 0) append(&res, 0, 10);

    while(val > 0) {
        append(&res, val % 10, 10);
        val /= 10;
    }

    return res;
}

DynArray getReverseArray(DynArray da) {
    DynArray newArray = {NULL, 0};
    for(unsigned int i = da.length; i > 0; i--) {
        append(&newArray, da.array[i - 1], 10);
    }
    return newArray;
}

unsigned long long getUInt(DynArray da) {
    unsigned long long res = 0;
    unsigned long long factor = 1;
    for(unsigned int i = 0; i < da.length; i++) {
        res += da.array[i] * factor;
        factor *= 10;
    }
    return res;
}

int isPalindrom(unsigned long long n) {
    return getUInt(getReverseArray(getDigits(n))) == n ? 1 : 0;
}

int isLychrels(unsigned long long n, int depth) {
    if(depth >= 50) return 1;

    unsigned long long reversed = getUInt(getReverseArray(getDigits(n)));
    unsigned long long sum = n + reversed;

    if(isPalindrom(sum)) return 0;
    return isLychrels(sum, depth + 1);
}

unsigned int solveProblem() {
    unsigned int lychrels = 0;

    for(unsigned int i = 1; i < 10000; i++) {
        if(isLychrels(i, 0)) lychrels++;
    }

    return lychrels;
}

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

int main() {
    printf("%u\n", solveProblem());
    wait();
    return 0;
}
