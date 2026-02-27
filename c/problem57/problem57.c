#include <stdio.h>
#include <stdlib.h>

#define DIGITSBACTH 1000

typedef struct {
    unsigned char *arr;
    unsigned long length;
} BigInt;


typedef struct {
    BigInt num;
    BigInt den;
} Frac;

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

BigInt MultBInt(BigInt *a,unsigned short b) { 
    BigInt result = {NULL, 0};

    int carry = 0;
    for(int i = 0; i < a->length; i ++) {
        int product = (a->arr[i] * b) + carry;
        appendDigits(&result,  product % 10);
        carry = product / 10;
    }

    while(carry > 0) {
        appendDigits(&result, carry%10);
        carry /= 10;
    }
    return result;
}

BigInt AddBInt(BigInt *a, BigInt *b) { 
    BigInt result = {NULL, 0};

    BigInt *max = NULL;
    BigInt *min = NULL;
    if(a->length > b->length) {
        max = a;
        min = b;
    }else{
        max = b;
        min = a; 
    }
    
    int carry = 0;
    int latest_i = 0;
    for(int i = 0; i < min->length  ; i ++) {
        int sum = (min->arr[i] + max->arr[i]) + carry;
        appendDigits(&result,  sum % 10);
        carry = sum / 10;
        latest_i = min->length;
    }

    for(int rest = latest_i; rest < max->length; rest ++ ) {
        int sum = max->arr[rest] + carry;
        appendDigits(&result,  sum % 10);
        carry = sum / 10;
    }
   
    while(carry > 0) {
        appendDigits(&result, carry%10);
        carry /= 10;
    }

    return result;
}

int DisplayFrac(Frac *fraction) {
    for(int i = fraction->num.length - 1; i >= 0 ; i --) {
        printf("%i", fraction->num.arr[i]);
    }
    printf(" / ");
    for(int i = fraction->den.length - 1; i >= 0; i --) {
        printf("%i", fraction->den.arr[i]);
    }
    printf("\n");

}

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
    return fraction->num.length > fraction->den.length;
}

int solveProblem(Frac* fraction, unsigned int depth) {
   
    BigInt product_nnum = MultBInt(&fraction->den, 2); 
    BigInt nnum = AddBInt(&product_nnum, &fraction->num);
    BigInt nden = AddBInt(&fraction->num, &fraction->den);
    
    free(product_nnum.arr);
    free(fraction->num.arr);
    free(fraction->den.arr);

    fraction->num = nnum;
    fraction->den = nden;      
    
    if (depth > 1) {
        return fractionNumeratorCheck(fraction) + solveProblem(fraction, depth - 1);
    }
    return 0;
}



int main() { 
    Frac startF = {createDigits(3),createDigits(2)}; 
    
    printf("%i \n", solveProblem(&startF, 1000));
    // DisplayFrac(startF)
    return 0;
} // It's working