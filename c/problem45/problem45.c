#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned int *array;
    unsigned int length;
} DynArray;

void append(DynArray *da, unsigned long val, unsigned int buffersize) { 
    if (da->length == 0) {
        da->array = malloc(buffersize * sizeof(unsigned long));
    } else if (da->length % buffersize == 0) { 
        da->array = realloc(da->array, (da->length + buffersize) * sizeof(unsigned long));
    }
    da->array[da->length++] = val;
}

int contains(const unsigned long c, const DynArray *da) { // searching with dichotomy the number in the array and result is if the number is in the dynamic array
    int left = 0, right = da->length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (da->array[mid] == c) return 1;
        if (da->array[mid] < c) left = mid + 1;
        else right = mid - 1;
    }
    return 0;
}

unsigned long GetPentagonal(int n) {
    return (unsigned long)(n * (3UL * n - 1) / 2);
}
unsigned long GetTriangle(int n) {
    return (unsigned long)(n * ( n + 1UL) / 2); 
}
unsigned long GetHexagonal(int n) {
    return (unsigned long)(n * (2UL * n - 1));
}

unsigned long int solveProblem() {
    int starts[3] = {286, 166, 144}; 
    int res = 0;

    DynArray h_array = {NULL, 0};
    DynArray p_array = {NULL, 0};
    DynArray t_array = {NULL, 0};
   int  p_solved = 0;
    for(int i = 0; !p_solved; i ++ ) {
        append(&t_array, GetTriangle(starts[0] + i), 100);
        append(&h_array, GetHexagonal(starts[2] + i), 100);
        append(&p_array, GetPentagonal(starts[1] + i), 100);
        const unsigned long check = t_array.array[t_array.length - 1];
        if( contains( check,  &h_array) == 1 &&  contains( check,  &p_array) == 1) {
            p_solved = 1;
            res = check;
        }
    }
    free(p_array.array);
    free(h_array.array);
    free(t_array.array);
    return res;
}
void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

// as I see on others solutions the triangle numbers are include in hexagonals and i don't have to check it but i post my solution as i designed
int main() {
    printf("Solution: %lu\n", solveProblem());
    wait();
    return 0;
}