#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define LEN(arr) (sizeof(arr) / sizeof((arr)[0]))


typedef struct {
    unsigned long int *array;
    unsigned int length;
} DynArray;

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

// Add an element to the dynamic array
void append(DynArray *da, unsigned long int val) {
    if (da->length == 0) {
        da->array = (unsigned long int *)malloc(sizeof(unsigned long int));
    } else {
        da->array = (unsigned long int *)realloc(da->array, (da->length + 1) * sizeof(unsigned long int));
    }
    da->array[da->length] = val;
    da->length++;
}

// check if the number is prime
bool isPrime(unsigned long int val) {
    if (val <= 1) return false;
    if (val == 2 || val == 3) return true;
    if (val % 2 == 0 || val % 3 == 0) return false;
    for (unsigned long int i = 5; i * i <= val; i += 6) { // increment by 6 because of after 5 all the primes are shape like 6k +- 1
        if (val % i == 0 || val % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

// get the length of a number (in digits)
unsigned int getDigitLength(unsigned int val) {
    unsigned int l = 0;
    while (val > 0) {
        l += 1;
        val = val / 10;
    }
    return l;
}

// function to check if a number is pangdigital
bool isPanDigit(int val) {
    if (getDigitLength(val) != 9) {
        return false;
    }
    bool digits[10] = {false}; 
    while (val > 0) {
        unsigned long int current_digit = val % 10;
        if (current_digit == 0 || digits[current_digit]) {
            return false;
        }
        digits[current_digit] = true;
        val = val / 10;
    }
    return true;
}

// generate some permutation of a number
void permuteAndCheck(int *arr, int left, int right, DynArray *primes) {
    if (left == right) {
        unsigned long int num = 0;
        for (int i = 0; i <= right; i++) {
            num = num * 10 + arr[i];
        }
        if (isPrime(num)) {
            append(primes, num);
        }
    } else {
        for (int i = left; i <= right; i++) {
            int temp = arr[left];
            arr[left] = arr[i];
            arr[i] = temp;
            permuteAndCheck(arr, left + 1, right, primes);
            temp = arr[left];
            arr[left] = arr[i];
            arr[i] = temp;
        }
    }
}

// solve the problem
unsigned long int largestPandigitalPrime() {
    unsigned long int largestPrime = 0;

    for (int n = 9; n > 0; n--) {
        int digits[n];
        for (int i = 0; i < n; i++) {
            digits[i] = i + 1;
        }

        DynArray primes = {NULL, 0};
        permuteAndCheck(digits, 0, n - 1, &primes);

        for (unsigned int i = 0; i < primes.length; i++) {
            if (primes.array[i] > largestPrime) {
                largestPrime = primes.array[i];
            }
        }

        if (largestPrime > 0) {
            break;
        }
    }

    return largestPrime;
}

int main() {
    unsigned long int result = largestPandigitalPrime();
    printf("Largest pandigital prime: %lu\n", result);
    wait();
    return 0;
}
