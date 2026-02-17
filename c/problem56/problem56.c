#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <pthread.h>


unsigned long int digitSum(unsigned int nbr) {
    unsigned long int sum = 0;
    while(nbr >= 10) {
        sum +=  nbr % 10;
        nbr /= 10;
    }
    return sum + nbr;
} 


// typedef struct
// {
// 	unsigned int *array;
// 	unsigned int length;
// 	unsigned int max;
// 	unsigned int min;
// } DynArray;

typedef struct {
    unsigned int input;
    unsigned long  output;
} DigitSumTask;


void *threadSum(void *arg) {
    DigitSumTask *t = (DigitSumTask*) arg;
	t->output = digitSum(t->input);
    printf("thread:%i, result: %i.\n", t->input, t->output);
	// Arr�t propre du thread
	pthread_exit(EXIT_SUCCESS);
}


unsigned long  solveProblem() {

    pthread_t thread1;
    pthread_t thread2;
    DigitSumTask t1 = {input: 3432693, 0};
    DigitSumTask t2 = {1782934, 0};
    pthread_create(&thread1, NULL, threadSum, &t1);
    pthread_create(&thread2, NULL, threadSum, &t2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    if (t1.output > t2.output) return t1.output;
    return t2.output ;
}

void wait() {
    printf("Press Enter to exit...\n");
    getchar();
}

int main() {
    // pthread_t thread1;
    // pthread_create(&thread1, NULL, thread_1, NULL);
    // pthread_join(thread1, NULL);
   
    printf("%i \n", solveProblem());
    wait();
    
    return 0;
}