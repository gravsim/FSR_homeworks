#include <stdio.h>
#include <stdlib.h>


#define CHUNK_SIZE (8 * sizeof(unsigned long long))


char** allocate_matrix(int size) {
    char** matrix = calloc(size, sizeof(char*));
    int i;
    for (i = 0; i < size; i++) {
        matrix[i] = calloc(size, sizeof(char));
    }
    return matrix;
}


unsigned long long check_bit(unsigned long long number, int bit_index) {
    return number & 1ULL << (bit_index % CHUNK_SIZE);
}

int set_bit(unsigned long long* number, int bit_index) {
    /*
    1ULL - unsigned long long размером CHUNK_SIZE бита, значение: 1.
    Выглядит так: 000...(63 нуля)...0001
    Делаем побитовый сдвиг влево единицы на остаток при делении индекса j+1 на CHUNK_SIZE.
    Получаем смещение в числе которое выглядит так: 000000100..((j+1)%CHUNK_SIZE нулей)..00
    Делаем побитовое или для строки смежности i-й вершины и этого сдвига,
    чтобы вершина j+1 в i-й строке матрицы смежности стала единицей.
    */
    if (!number) {
        return -1;
    }
    *number |= 1ULL << (bit_index % CHUNK_SIZE);
    return 1;
}


int main(void) {
    /*
     Т.к. булов в си нету, будем хранить значения есть/нету
     пути из вершины i в вершину j
     в битах CHUNK_SIZE-разрядных чисел. Таких чисел понадобится
     (N + 63) / CHUNK_SIZE (округление в большую сторону).
     Создаем два массива с числами, в которых будем хранить
     состояния посещенных вершин: red_reached: N * N, blue_reached: N ^ N.
     В i-й строке j-м столбце матрицы стоит 1, если из i-й вершины
     в j-ю есть путь только по цвету матрицы. Иначе стоит 0 (одноцветного пути нет).
    */
    int N;
    scanf("%d", &N);
    char** connections = allocate_matrix(N);
    int i;
    int j;
    int k;
    int answer = 1;
    int numbers = (N + CHUNK_SIZE - 1) / CHUNK_SIZE;
    unsigned long long** red_reached = malloc(N * sizeof(unsigned long long*));
    unsigned long long** blue_reached = malloc(N * sizeof(unsigned long long*));
    for (i = 0; i < N; i++) {
        red_reached[i] = calloc(numbers, sizeof(unsigned long long));
        blue_reached[i] = calloc(numbers, sizeof(unsigned long long));
    }
    for (i = 0; i < N - 1; i++) {
        scanf("%s", connections[i] + i);
    }
    i = N - 2;
    while (answer == 1 && i >= 0) {
        /*
         Идем от последней вершины к первой. Заполняем оба массива путями из
         i-й вершины в вершины i+1, i+2, ..., N-1, а потом копируем эти ребра для
         вершин, у которых есть ребра, ведущие в i-ю вершину.
        */
        for (j = i; j < N; j++) {
            if (connections[i][j] == 'R') {
                set_bit(&red_reached[i][(j + 1) / CHUNK_SIZE], j + 1);
                for (k = 0; k < numbers; k++) {
                    red_reached[i][k] |= red_reached[(j + 1)][k];
                    /*
                    Есть два числа, с ребрами в битах. Например:
                    i = 0110...
                    j+1 = 0101...
                    Делаем для них побитовое ИЛИ |, тем самым копируя все ребра из
                    строки вершины с индексом j + 1 в строку предшествующей ей
                    вершины с индексом i
                    i = i | j+1 = 0110... | 0101... = 0111...
                    и результат присваивается строке смежности i-й вершины.
                    */
                }
            } else if (connections[i][j] == 'B') {
                set_bit(&blue_reached[i][(j + 1) / CHUNK_SIZE], j + 1);
                for (k = 0; k < numbers; k++) {
                    blue_reached[i][k] |= blue_reached[(j + 1)][k];
                }
            }
        }
        k = 0;
        while (answer == 1 && k < numbers) {
            /*
            Сравниваем строки в матрицах смежности через побитовое И & для чисел.
            Если вышло, что путь из вершины A в вершину B есть и в синей и в красной матрице,
            значит раскраска стрелок не однотонная.
            */
            if (red_reached[i][k] & blue_reached[i][k]) {
                // Пример: 1010111 & 0011010 = 0010010
                answer = 0;
            }
            k++;
        }
        i--;
    }
    if (answer) {
        printf("YES");
    } else {
        printf("NO");
    }
    for (i = 0; i < N; i++) {
        free(connections[i]);
    }
    free(connections);
    for (i = 0; i < N; i++) {
        free(red_reached[i]);
        free(blue_reached[i]);
    }
    free(red_reached);
    free(blue_reached);
    return 0;
}
