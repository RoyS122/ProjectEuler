#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <pthread.h>

#define DIGITSBACTH 1000

typedef struct {
    unsigned char *arr;
    unsigned long length;
} BigInt;


int appendDigits(BigInt *d, unsigned char a ) {
    if(d->length == 0) {
        d->arr = (unsigned char *)malloc(DIGITSBACTH);
    }else{
        if (d->length % DIGITSBACTH == 0) {
            d->arr = (unsigned char *)realloc(d->arr,d->length + DIGITSBACTH);
        } 
    }
    d->arr[d->length] = a;
    d->length += 1;
    return 0;
}

BigInt createDigits(unsigned char v) {
    BigInt res = {NULL, 0};
    while (v > 10) {
        appendDigits(&res, v %10);
        v /= 10;
    }
    appendDigits(&res, v);
    
    return res;
}



int Mult(BigInt *a,unsigned short b) { 
    int carry = 0;
    for(int i = 0; i < a->length; i ++) {
        int product = (a->arr[i] * b) + carry;
        a->arr[i] = product % 10;
        carry = product / 10;
    }

    while(carry > 0) {
        appendDigits(a, carry%10);
        carry /= 10;
    }
    return 0;
}

int Power(BigInt *a, unsigned char b, unsigned char origin_a) {
    if (b > 1) {
        Mult(a, origin_a);
        Power(a, b - 1, origin_a);
    }
    return 0;
}

unsigned long long DigitSum(BigInt *a) {
    unsigned long long res = 0;
    for(unsigned long i = 0; i < a->length; i ++) {
        res += a->arr[i];
    }
    return res;
} 




unsigned long  solveProblem() {
    unsigned long res = 0;

    for(unsigned int i = 1; i < 100; i ++) {
        for(unsigned int j = 1; j < 100; j ++) {
            BigInt a = createDigits(i);
            Power(&a, j, i);
            unsigned long output = DigitSum(&a);
            if(res < output) {
                res = output;
            }
        }    
    }
   
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