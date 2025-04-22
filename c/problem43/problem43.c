#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))


typedef struct {
    unsigned int *array;
    unsigned int length;
} DynArray;

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

// Add an element to the dynamic array
void append(DynArray *da, unsigned int val) {
    if (da->length == 0) {
        da->array = (unsigned  int *)malloc(sizeof(unsigned  int));
    } else {
        da->array = (unsigned  int *)realloc(da->array, (da->length + 1) * sizeof(unsigned  int));
    }
    da->array[da->length] = val;
    da->length++;
}

void prepend(DynArray *da, unsigned int val) {
    if (da->length == 0) {
        da->array = (unsigned int *)malloc(sizeof(unsigned int));
    } else {
        da->array = (unsigned int *)realloc(da->array, (da->length + 1) * sizeof(unsigned int));
        for (unsigned int i = da->length; i > 0; i--) {
            da->array[i] = da->array[i - 1];
        }
    }
    da->array[0] = val;
    da->length++;
}


// get the length of a number (in digits)
unsigned int getDigitLength(unsigned long int val) {
    unsigned int l = 0;
    while (val > 0) {
        l += 1;
        val = val / 10;
    }
    return l;
}

DynArray getDigits(unsigned long int val) {
    DynArray res = {NULL, 0};
    
    while(val > 0) {
        prepend(&res, val % 10);
        val = val / 10;
    }

    return res ;
}

// function to check if a number is pangdigital
bool isPanDigit(unsigned long int val) {
   
    if (getDigitLength(val) != 10) {
        return false;
    }
    bool digits[10] = {false}; 
    while (val > 0) {
        unsigned long int current_digit = val % 10;
        if (digits[current_digit]) {
            return false;
        }
        digits[current_digit] = true;
        val = val / 10;
    }
    return true;
}

bool checkNumber(unsigned long int nbr) {
    if (!isPanDigit(nbr)) {
        return false;
    }
    DynArray digits = getDigits(nbr);
    return (
        (digits.array[3] + digits.array[2] * 10 + digits.array[1] * 100) % 2 == 0 && 
        (digits.array[4] + digits.array[3] * 10 + digits.array[2] * 100) % 3 == 0 &&
        (digits.array[5] + digits.array[4] * 10 + digits.array[3] * 100) % 5 == 0 &&
        (digits.array[6] + digits.array[5] * 10 + digits.array[4] * 100) % 7 == 0 &&
        (digits.array[7] + digits.array[6] * 10 + digits.array[5] * 100) % 11 == 0 &&
        (digits.array[8] + digits.array[7] * 10 + digits.array[6] * 100) % 13 == 0 &&
        (digits.array[9] + digits.array[8] * 10 + digits.array[7] * 100) % 17 == 0   
    );
}

unsigned long int solveProblem() {
    unsigned long int res = 0;
    for (unsigned long int i = 1023456789; i <= 9876543210; i ++) {
        if(checkNumber(i)) {
            res += i;
        }
    }
    return res;
}

int main() {
    unsigned long int result = solveProblem();
    printf("result: %lu\n%d", result, checkNumber(1923456780));
    wait();
    return 0;
}