#include <stdio.h>


int get_factorial(int n){
    if (n == 0){
        return 1;
    }
    return n * get_factorial(n - 1);
}


int find_number(int k, int n){
    return get_factorial(n) / (get_factorial(k) * get_factorial(n - k));
}


int print_spaces(int spaces_number){
    int i;
    for (i = 0; i < spaces_number; i++){
        printf(" ");
    }
    return 1;
}


int main(void) {
    int rows_number;
    scanf("%d", &rows_number);
    for (int row_index = 0; row_index < rows_number; row_index++) {
        if (rows_number > 5 && rows_number < 10) {
            print_spaces(1);
        }
        for (int number_index = 0; number_index <= row_index; number_index++) {
            int result = find_number(number_index, row_index);
            int spaces_number;
            int indents_number;
            if (rows_number <= 5) {
                spaces_number = 4;
                indents_number = 2;
            } else if (rows_number > 5 && rows_number < 10) {
                spaces_number = 6;
                indents_number = 3;
            } else if (rows_number == 10) {
                spaces_number = 7;
                indents_number = 4;
            }
            if (number_index == 0) {
                print_spaces(indents_number * (rows_number - row_index - 1));
            }
            printf("%*d", spaces_number, result);
        }
        printf("\n");
    }
    return 0;
}
