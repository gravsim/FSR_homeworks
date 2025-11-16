#include <stdio.h>


int check_digits(int number) {
    int k, l, m, n;

    k = number % 10;
    number /= 10;

    l = number % 10;
    number /= 10;

    m = number % 10;
    number /= 10;
    
    n = number % 10;
    number /= 10;
    if ((n == m && m == l && k != l) ||
        (k == n && n == m && l != m) ||
        (k == l && l == n && m != n) ||
        (k == l && l == m && n != k)) {
        return 1;
    }
    return 0;
}

int main(void) {
    int A, B;
    int number;
    scanf("%d %d", &A, &B);
    for (number = A; number < B; number++) {
        if (check_digits(number)) {
            printf("%d ", number);
        }
    }
    return 0;
}
