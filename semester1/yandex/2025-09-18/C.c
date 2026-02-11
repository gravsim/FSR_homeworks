#include <stdio.h>


int main(void){
    char characters[1000];
    scanf("%s", characters);
    int iteration = 0;
    while (characters[iteration] != '\0'){
    	printf("%c", characters[iteration]);
        if (characters[iteration] >= 'a' && characters[iteration] <= 'z'
            && characters[iteration + 1] >= 'A' && characters[iteration + 1] <= 'Z'){
            printf(" ");
        }
        iteration++;
    }
    return 0;
}
