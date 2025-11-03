#include <stdio.h>
#include <stdlib.h>

#define MAX_POWER 11


int char2int(char number) {
    return number - '0';
}


int is_number(char number) {
    return (number >= '0' && number <= '9');
}


int extract_multiplier(int* i, char* array) {
    int multiplier = 0;
    int sign = 1;
    if (array[*i] == '-') {
        sign = -1;
        (*i)++;
    } else if (array[*i] == '+') {
        (*i)++;
    }
    if (array[*i] == 'x') {
        return sign;
    }
    while (is_number(array[*i])) {
        multiplier *= 10;
        multiplier += char2int(array[*i]);
        (*i)++;
    }
    return sign * multiplier;
}


int extract_power(int* i, char* array) {
    int power = 0;
    if (array[*i] == 'x') {
        (*i)++;
        if (array[*i] == '^') {
            (*i)++;
            while (is_number(array[*i])) {
                power *= 10;
                power += char2int(array[*i]);
                (*i)++;
            }
        } else {
            power = 1;
        }
    } else {
        power = 0;
    }
    return power;
}


void read_polynomial(char* polynomial, int* multipliers) {
    int i = 0;
    int power = 1;
    int multiplier;
    while (polynomial[i] != '\0') {
        multiplier = extract_multiplier(&i, polynomial);
        power = extract_power(&i, polynomial);
        multipliers[power] = multiplier;
    }
}


void get_multiplication(int* result, int* multipliers1, int* multipliers2) {
    int i, j;
    for (i = 0; i < MAX_POWER; i++) {
        for (j = 0; j < MAX_POWER; j++) {
            result[i + j] += multipliers1[i] * multipliers2[j];
        }
    }
}


void print_polynomial(int* polynomial) {
    int i;
    int counter = 0;
    for (i = 2 * MAX_POWER - 2; i >= 0; i--) {
        if (polynomial[i] != 0) {
            if (counter > 0 && polynomial[i] > 0) {
                printf("+");
            }
            if (polynomial[i] != 1 || i == 0) {
                if (polynomial[i] == -1) {
                    printf("-");
                    if (i == 0) {
                        printf("1");
                    }
                } else {
                    printf("%d", polynomial[i]);
                }
            }
            if (i > 1) {
                printf("x^%d", i);
            } else if (i == 1) {
                printf("x");
            }
            counter++;
        }
    }
    if (counter == 0) {
        printf("0");
    }
}


int main(void) {
    char polynomial1[100];
    char polynomial2[100];
    scanf("%s", polynomial1);
    scanf("%s", polynomial2);
    int multipliers1[MAX_POWER] = {0};
    int multipliers2[MAX_POWER] = {0};
    read_polynomial(polynomial1, multipliers1);
    read_polynomial(polynomial2, multipliers2);
    int result[MAX_POWER * 2] = {0};
    get_multiplication(result, multipliers1, multipliers2);
    print_polynomial(result);
    return 0;
}
