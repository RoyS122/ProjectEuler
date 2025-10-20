#include <stdio.h>
#include <stdlib.h>

double factorial(int nbr) {
    double res = 1;
    for(int i = nbr; i > 0; i --) {
        res *= i;
    }
    return res;
}

unsigned int solveProblem() {
    unsigned int result = 0;
    for(int n = 1; n <= 100; n ++) {
        for (int r = 1; r <= n; r ++) {
            if((factorial(n) / (factorial(r)*factorial(n-r))) > 1*1000*1000) {
                result += 1;
            }
        }
    }
    return result;
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