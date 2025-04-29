#include <stdio.h>
#include <stdlib.h>


void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

#include <stdio.h>

int main() {
    unsigned long long sum = 0;
    unsigned long long mod = 10000000000ULL;
    
    for (unsigned int i = 1; i <= 1000; i++) {
        unsigned long long term = 1;
        for (unsigned int j = 0; j < i; j++) {
            term = (term * i) % mod;
        }
        sum = (sum + term) % mod;
    }
    
    printf("Last 10 digits: %010llu\n", sum);
    wait();
    return 0;
}