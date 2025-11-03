#include <stdio.h>


#define ilya_klopov_zero 0
#define ilya_klopov_two 2
#define ilya_klopov_three 3
typedef int ilya_klopov_int;
typedef void ilya_klopov_void;


ilya_klopov_void ilya_klopov_scanf(ilya_klopov_int* variable) {
    scanf("%d", &variable);
}


ilya_klopov_void ilya_klopov_printf(ilya_klopov_int* variable) {
    printf("%d", &variable);
}


ilya_klopov_void ilya_klopov_increment(ilya_klopov_int* variable) {
    (*variable)++;
}


ilya_klopov_void ilya_klopov_cicle(
    ilya_klopov_int* iteration,
    ilya_klopov_int* N,
    ilya_klopov_int* A,
    ilya_klopov_int* B,
    ilya_klopov_int* C,
    ilya_klopov_int* amount) {
    for (*iteration = ilya_klopov_zero; *iteration < *N - ilya_klopov_two; ilya_klopov_increment(iteration)) {
        ilya_klopov_scanf(&C);
        if (*A < *B && *B > *C) {
            ilya_klopov_increment(amount);
        }
        *A = *B;
        *B = *C;
    }
}


ilya_klopov_int main(ilya_klopov_void) {
    ilya_klopov_int N;
    ilya_klopov_scanf(&N);
    ilya_klopov_int A, B, C;
    ilya_klopov_int iteration;
    ilya_klopov_int amount = ilya_klopov_zero;
    if (N < ilya_klopov_three) {
        ilya_klopov_printf(ilya_klopov_zero);
        return ilya_klopov_zero;
    }
    ilya_klopov_scanf(&A);
    ilya_klopov_scanf(&B);
    ilya_klopov_cicle(&iteration, &N, &A, &B, &C, &amount);
    ilya_klopov_printf(amount);
    return ilya_klopov_zero;
}
