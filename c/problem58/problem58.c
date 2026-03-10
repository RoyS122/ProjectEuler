#include <stdio.h>
#include <stdlib.h>

int IsPrime(unsigned int n) {
    if (n < 2) return 0;
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    for (unsigned int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int Solve() {
    
    float tx = 1.0;
    unsigned int count_diag_prime = 0;
    unsigned int count_diag = 1;

    unsigned int check = 1;
    
    for (unsigned int side = 2; 1; side += 2) {
        for(int i = 0; i < 4; i ++) {
            check += side;
            if(IsPrime(check)) {
                count_diag_prime += 1;
            }
            count_diag += 1;
        }
        tx = (float)count_diag_prime / (float)count_diag;
        if (tx < 0.10) {
            return side + 1;
        }
    }
    return 0;
}

int main() {
    printf("reponse: %i", Solve());
   
    return 0;
}