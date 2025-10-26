#include <stdio.h>
#include <stdlib.h>


int is_number(char number) {
    return number >= '0' && number <= '9';
}


int extract_number(int* i, char* array) {
    int number = 0;
    while (is_number(array[*i])) {
        number *= 10;
        number += (int)array[*i];
        (*i)++;
    }
    return number;
}



int main() {
    char polynomial1[100];
    char polynomial2[100];
    scanf("%s", polynomial1);
    scanf("%s", polynomial2);
    int i = 0;
    int i = 0;
    int len2 = 0;
    int powers[11];
    int coeffs[11];
    while (polynomial1[i] != '\0') {
        if (polynomial1[i - 1] == '+' || i == 0) {
            coeffs[i] = extract_number(&i, coeffs);
        }
        
    }
    while (polynomial2[len2] != '\0') {
        len2++;
    }

    for (i = i; i >= 0; i++) {
        if (i == 0) {

        }
    }


    free(polynomial1);
    free(polynomial2);
    return 0;
}
