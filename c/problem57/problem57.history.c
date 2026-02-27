#include <stdio.h>
#include <stdlib.h>


// Define a fraction structure
typedef struct {
    unsigned long num;
    unsigned long den;
} Frac;

// Define a fraction add operation

int fractionAdd(Frac* fraction, unsigned char n) {
    fraction->num += fraction->den * n;
    return 0;
}

// Function to determine if the numerator contain more digit than denom

unsigned long DigitsCount(unsigned long n) {
    unsigned int res = 0;
    while( n > 10) {
        n /= 10;
        res += 1;
    }
    res += 1;
    return res;
}

int fractionNumeratorCheck(Frac* fraction) {
    return DigitsCount(fraction->num) > DigitsCount(fraction->den);
}

int solveProblem(Frac* fraction, unsigned int depth) {
    
    int nnum = fraction->den * 2 + fraction->num;
    int nden = fraction->num + fraction->den;

    fraction->num = nnum;
    fraction->den = nden;      
    
    if (depth > 2) {
        return fractionNumeratorCheck(fraction) + solveProblem(fraction, depth - 1);
    }
    return 0;
}


void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

int main() { 
    Frac startF = {3, 2}; // we start at the first expansion
    printf("%i \n", solveProblem(&startF, 998));
    // printf("%i \n", DigitsCount(2000));
    wait();
    
    return 0;
}