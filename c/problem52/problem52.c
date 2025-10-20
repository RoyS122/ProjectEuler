#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int getDigits(unsigned int n, int digits[]) {
    int len = 0;
    while (n > 0) {
        digits[len++] = n % 10;
        n /= 10;
    }
    return len;
}

int compareDigitsUnordered(int digits1[], int digits2[], int length) {
    int count1[10] = {0}; 
    int count2[10] = {0}; 

    for (int i = 0; i < length; i++) {
        count1[digits1[i]]++;
        count2[digits2[i]]++;
    }

    for (int i = 0; i < 10; i++) {
        if (count1[i] != count2[i])
            return 0; 
    }
    return 1; 
}

unsigned int solveProblem() {
    int solved = 0;
    int digits_init[10];
    int digits_to_check[10];
    for(int i = 10; solved == 0; i ++) {
        // printf("%d\n", i);
        int length = getDigits(i, digits_init);
        int check = 1;
        for(int j = 1; j < 7; j ++) {
            int length_check = getDigits(j * i ,digits_to_check);
            if (length_check != length) {
                check = 0;
                break;
            } 
            if (compareDigitsUnordered(digits_init, digits_to_check, length)) {
                continue;
            }else{
                check = 0;
                break;
            }
        }
        if (check) {
            solved = 1;
            return i;
        }
    }
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