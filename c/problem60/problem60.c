#include <stdio.h>
#include <stdlib.h>
#define BATCH 10000
#define TARGETSETSIZE 5

int IsPrime(unsigned int n) {
    if (n == 2 || n == 3) return 1;
    if (n < 2) return 0;
    if (n % 2 == 0) return 0;
    if (n % 3 == 0) return 0;

    for(int i = 5; i * i < n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

int IsPrimeLong(unsigned long long n) {
    if (n == 2 || n == 3) return 1;
    if (n < 2) return 0;
    if (n % 2 == 0) return 0;
    if (n % 3 == 0) return 0;

    for(unsigned long long i = 5; i * i < n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    }
    return 1;
}

typedef struct {
    unsigned int *arr;
    unsigned long length;
} PrimeArray;

int append(PrimeArray *p, unsigned int n) {
    if(p->length == 0) {
        p->arr = (unsigned int *)malloc(BATCH * sizeof(unsigned int));
    }else{
        if (p->length % BATCH == 0) {
            p->arr = (unsigned int *)realloc(p->arr,(p->length + BATCH)* sizeof(unsigned int));
        } 
    }
    if(IsPrime(n)) {
        p->arr[p->length] = n;
        p->length += 1;
    }    
    return 0;
}

int newChunk(PrimeArray *p) {
    
    unsigned long targetLength = p->length + BATCH;
    unsigned int start = 3;
    if (p->length > 0) {
        start = p->arr[p->length - 1];
    }
    for(unsigned int i = start; p->length < targetLength; i += 2) {
        append(p, i);
    }

    return 0;
}


unsigned long long ConcatInt(unsigned int a, unsigned int b) {
    unsigned long long mult = 10;
    while (b >= mult) {
        mult *= 10;
    }

    return (unsigned long long)a * mult + b;;
}


int IsConnected(unsigned int a, unsigned int b) {
 
    if(!IsPrimeLong(ConcatInt(a,b))) return 0;
    if(!IsPrimeLong(ConcatInt(b,a))) return 0;
    return 1;
}

int freeArr(PrimeArray *a) {
    free(a->arr);
    return 0;
}

unsigned long long find_clique(PrimeArray *p, unsigned int *current_set, int set_size, unsigned int start_index, unsigned long long *minV) {
    unsigned long long currentSum = 0;
    for (int i = 0; i < set_size; i ++) {
           currentSum+= current_set[i];
    }
    if (currentSum >= *minV) {
        return 0;
    }
   
    if(TARGETSETSIZE == set_size) {
        // unsigned long long res = 0;
        printf("\nFound: ");
        for (int i = 0; i < set_size - 1; i ++) {
            printf("%i,", current_set[i]);
        }
        printf("%i", current_set[set_size-1]);

        if(currentSum < *minV) {
            *minV = currentSum;
        }
        printf("\nResult: %llu", currentSum);
        return 1;
    }
  

    for(unsigned int i = start_index; i < p->length; i ++) {
        int compat = 1;
        for(int j = 0; j < set_size; j ++) {
            if(!IsConnected(current_set[j], p->arr[i])) {            
                compat = 0;
                break;
            }
        }
        unsigned long long sum_so_far = 0;
        if(compat) {
            // printf("%i" ,p->arr[i]);
            unsigned long long remaining = TARGETSETSIZE - set_size;
            if (sum_so_far + (remaining * p->arr[start_index]) >= *minV) {
                return 0; // Coupe la branche !
            }
            current_set[set_size] = p->arr[i];
            find_clique(p, current_set, set_size + 1, i + 1, minV);      
        }
    }
    
    if (*minV < 10000000) {
        return 1;
    }
    return 0;

}

int main() {
    

    PrimeArray p = {NULL, 0};
    newChunk(&p);

    unsigned int *currentSet = malloc(sizeof(unsigned int) * TARGETSETSIZE);
    unsigned long long minV =10000000; 
    while (find_clique(&p, currentSet, 0, 0, &minV) != 1) {
        newChunk(&p);
    }
    return 0;
}