#include <stdio.h>


int main() {
    int N;
    scanf("%d", &N);
    int colors[1000];
    int i;
    int buffer;
    for (i = 0; i < N; i++) {
        scanf("%d", &colors[i]);
    }
    int destroyed = 0;
    int found;
    int changed = 1;
    int k;
    int j;
    while (changed) {
        changed = 0;
        i = 0;
        while (i < N && changed != 1) {
            j = i;
            while (colors[j] == colors[i] && j < N) {
                j++;
            }
            found = j - i;
            if (found >= 3) {
                for (k = j; k < N; k++) {
                    colors[k - found] = colors[k];
                }
                N -= found;
                changed = 1;
                destroyed += found;
            }
            i++;
        }
    }
    printf("%d", destroyed);
    return 0;
}
