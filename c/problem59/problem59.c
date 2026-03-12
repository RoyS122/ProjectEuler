#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BATCHSIZE 256
#define DIGITSBACTH 500

typedef struct {
    unsigned long length;
    unsigned char *arr;
} DynArray;

int printarr(DynArray *a) {
    for(unsigned long i= 0; i < a->length; i ++) {
        printf("%c", a->arr[i]);
    }
    return 0;
}

int append(DynArray *a, unsigned char c ) {
    if(a->length == 0) {
        a->arr = (unsigned char *)malloc(DIGITSBACTH);
    }else{
        if (a->length % DIGITSBACTH == 0) {
            a->arr = (unsigned char *)realloc(a->arr,a->length + DIGITSBACTH);
        } 
    }
    a->arr[a->length] = c;
    a->length += 1;
    return 0;
}

int contain(DynArray *a, const char *s) {
    unsigned int point = 0;
    unsigned int lens = strlen(s);
    for(unsigned long i = 0; i < a->length - lens; i ++) {
        if(a->arr[i] == s[point]) {
            point += 1;
            if(point == lens) {
                return 1;
                point = 0;
            }
            continue;
        }
        point = 0;
    }
    return 0;
} 

DynArray XOR(DynArray *a, const char *s) {
    DynArray r =  {0};
    const char maxS = strlen(s);
    
    for(unsigned long i = 0; i < a->length; i ++) {
        unsigned char newC = a->arr[i] ^ s[i % maxS];
        append(&r, newC);
    }
    return r;
}

DynArray ReadFile(const char* path) {
    DynArray str = {0, NULL};

    FILE *file;
    char batch[BATCHSIZE];
    printf("%s \n", path);

    file = fopen(path, "r");

    unsigned char val = 0;
   
    for (int c = fgetc(file); c != EOF; c = fgetc(file)) {
        if(c == ',') {
            append(&str, val);        
            val = 0;
            continue;
        }

        val = val * 10 + (c - '0');
    }
    append(&str, val);  
    fclose(file);
    return str;
}

unsigned long long SumAscii(DynArray *a) {
    unsigned long long res = 0;

    for(unsigned long i = 0; i < a->length; i ++) {
        res += a->arr[i]; 
    }

    return res; 
}

int Solve() {
    DynArray v = ReadFile("../data/0059_cipher.txt");
    DynArray xored = {0}; 

    unsigned char code[4];
    code[3] = 0;
    int stop = 0;
    for(code[0] = 'a'; stop != 1 && code[0] < 'z' + 1; code[0] ++) {
        for(code[1] = 'a'; stop != 1 && code[1] < 'z' + 1; code[1] ++) {
            for(code[2] = 'a'; stop != 1 && code[2] < 'z' + 1 ; code[2] ++) {
                free(xored.arr);
                xored = XOR(&v, code);
                if(contain(&xored, " the ") && contain(&xored, " and ")) {
                    printf("\n %s \n \n",code);
                    printarr(&xored);

                    printf("\nresult: %llu \n", SumAscii(&xored));
                    return 0;
                }

            }
        }   
    }
   
}

int main() {

    Solve();

    return 0;
}


