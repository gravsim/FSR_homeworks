#include <stdio.h>
#include <stdlib.h>


typedef struct Queue {
    long long front;
    long long back;
    long long capacity;
    long long* values;
} Queue;


struct Game {
    long long teams_number;
    Queue* queue;
    long long team1;
    long long team2;
    long long winner;
    long long loser;
    long long max_team;
    long long max_team_index;
    long long games_played;
    long long* teams1;
    long long* teams2;
} typedef Game;


int norm_index(Queue* queue, long long index) {
    return (index % queue->capacity + queue->capacity) % queue->capacity;
}


int is_full(Queue* queue) {
    if (!queue) {
        return 0;
    }
    return queue->back - queue->front == queue->capacity;
}


void expand(Queue* queue) {
    if (!queue) {
        return;
    }
    queue->front = norm_index(queue, queue->front);
    queue->back = norm_index(queue, queue->back);
    long long old_capacity = queue->capacity;
    queue->capacity *= 2;
    long long* tmp_values = realloc(queue->values, queue->capacity * sizeof(long long));
    if (!tmp_values) {
        return;
    }
    queue->values = tmp_values;
    long long i;
    if (queue->front >= queue->back) {
        for (i = 0; i < queue->back; i++) {
            queue->values[i + old_capacity] = queue->values[i];
        }
        queue->back += old_capacity;
    }
}


int push(Queue* queue, long long* value) {
    if (!queue || !value) {
        return -1;
    }
    if (is_full(queue)) {
        expand(queue);
    }
    queue->values[norm_index(queue, queue->back)] = *value;
    queue->back++;
    return 0;
}


int pop(Queue* queue, long long* value) {
    if (!queue || !value) {
        return -1;
    }
    *value = queue->values[norm_index(queue, queue->front)];
    queue->front++;
    return 0;
}


Queue* init_queue(long long N) {
    Queue* queue = malloc(sizeof(Queue));
    queue->front = 0;
    queue->back = 0;
    queue->capacity = N + 1;
    queue->values = (long long*)calloc(queue->capacity, sizeof(long long));
    return queue;
}


void swap(long long* a, long long* b) {
    long long tmp = *a;
    *a = *b;
    *b = tmp;
}


void quick_sort(long long* main_array, long long* side_array, long long size){
    /*
         Слегка измененный QuickSort.
         Над побочным массивом (в нашем случае indices) производим все те же операции,
         что и над главным массивом, который мы сортируем. Это нужно, чтобы запомнить
         исходный порядок элементов в главном массиве, и в дальнейшем его восстановить.
    */
    long long down = 0;
    long long up = size - 1;
    long long pivot = main_array[size / 2];
    if (size > 1){
        while (down <= up){
            while (main_array[down] < pivot) down++;
            while (pivot < main_array[up]) up--;
            if (down <= up){
                swap(&main_array[down], &main_array[up]);
                swap(&side_array[down], &side_array[up]);
                down++;
                up--;
            }
        }
        quick_sort(main_array, side_array, up + 1);
        quick_sort(main_array + down, side_array + down, size - down);
    }
}


int array_max(long long* array, long long size, long long* max, long long* max_index) {
    /*
     Ищем максимальный элемент в массиве и его индекс
    */
    if (!array) {
        return -1;
    }
    *max = array[0];
    long long i;
    for (i = 1; i < size; i++) {
        if (array[i] > *max) {
            *max = array[i];
            if (max_index) {
                *max_index = i;
            }
        }
    }
    return 1;
}


int fight(Game* game) {
    /*
     Выбираем из двух команд победителя и проигравшего
    */
    if (!game) {
        return -1;
    }
    if (game->team1 > game->team2) {
        game->winner = game->team1;
        game->loser = game->team2;
    } else {
        game->winner = game->team2;
        game->loser = game->team1;
    }
    return 1;
}


int print_results(long long Q, long long* answers1, long long* answers2) {
    if (!answers1 || !answers2) {
        return -1;
    }
    long long i;
    for (i = 0; i < Q; i++) {
        printf("%lli %lli\n", answers1[i], answers2[i]);
    }
    return 1;
}


int sort_back(long long Q,
    long long* answers1,
    long long* answers2,
    long long* indices,
    Game* game) {
    /*
        С помощью вспомогательного массива indices, который содержит информацию
        о том, в каком порядке изначально находились неотсортированные элементы
        rhymes заполняем массивы с окончательными ответами в правильном порядке.
    */
    if (!game || !answers1 || !answers2 || !indices) {
        return -1;
    }
    long long i;
    for (i = 0; i < Q; i++) {
        answers1[indices[i]] = game->teams1[i];
        answers2[indices[i]] = game->teams2[i];
    }
    return 1;
}


int read_teams(Game* game) {
    if (!game) {
        return -1;
    }
    long long i;
    long long value;
    for (i = 0; i < game->teams_number; i++) {
        scanf("%lli", &value);
        push(game->queue, &value);
    }
    return 1;
}


int read_rhymes(long long Q, long long* rhymes) {
    if (!rhymes) {
        return -1;
    }
    long long i;
    for (i = 0; i < Q; i++) {
        scanf("%lli", &rhymes[i]);
    }
    return 1;
}


int fill_indices(long long Q, long long* indices) {
    /*
     Заполняем вспомогательный массив indices индексами от 0 до Q.
    */
    if (!indices) {
        return -1;
    }
    long long i;
    for (i = 0; i < Q; i++) {
        indices[i] = i;
    }
    return 1;
}


int manual_games(Game* game, long long Q, long long* rhyme_index, long long* rhymes) {
    /*
        Вручную считаем, какие команды попадут на разные считалки, добавляя и
        убирая команды из очереди, сравниваем их силы и отправляем обратно в
        очередь проигравшего, пока не дойдем до команды с максимальной силой.
        После этой команды последовательность игр будет повторятся (т.к. все
        другие команды с меньшей силой и всегда будут проигравшими) и для
        большей скорости вычислений будем считать номера команд по формуле,
        а не ручным перебором.
    */
    if (!game || !rhymes) {
        return -1;
    }
    pop(game->queue, &game->team1);
    while (game->games_played <= game->max_team_index) {
        /*
            Идем по очереди до максимальной по величине команды, после
            этого участники игры будут повторятся с периодом N - 1, т. к. одна
            команда (с наибольшим значением) играет всегда, и ее мы вычитаем.
        */
        pop(game->queue, &game->team2);
        while (*rhyme_index < Q && game->games_played == rhymes[*rhyme_index] - 1) {
            /*
                Вычитаем единицу, т. к. массив индексируется с 0,
                а во входных данных матчи начинаются с 1.
            */
            game->teams1[*rhyme_index] = game->team1;
            game->teams2[*rhyme_index] = game->team2;
            (*rhyme_index)++;
        }
        fight(game);
        push(game->queue, &game->loser);
        game->team1 = game->winner;
        game->games_played++;
    }
    return 1;
}


int auto_games(Game* game, long long Q, long long* rhyme_index, long long* rhymes) {
    /*
        Тут считаем команды по формуле, как говорилось ранее, учитывая что
        есть цикличность в последовательности команд.
        (Картинка с примером в моем красном блокноте (если я его не забыл)).
    */
    if (!game || !rhymes) {
        return -1;
    }
    long long cycle_len = game->teams_number - 1;
    long long offset;
    long long value;
    while (*rhyme_index < Q) {
        game->teams1[*rhyme_index] = game->max_team;
        offset = (rhymes[*rhyme_index] - game->games_played - 1) % cycle_len;
        value = game->queue->values[norm_index(game->queue, game->queue->front + offset)];
        game->teams2[*rhyme_index] = value;
        (*rhyme_index)++;
    }
    return 1;
}


int main(void) {
    /*
        В коде везде используем long long потому что входные значения
        могут быть размером до 10^18, long размером 2^32 (32 бит) < 10^18,
        а long long размером 2^64 (64 бит) > 10^18.
    */
    long long Q;
    Game* game = malloc(sizeof(Game));
    game->max_team_index = 0;
    game->games_played = 0;
    scanf("%lli", &game->teams_number);
    game->queue = init_queue(game->teams_number);
    read_teams(game);
    scanf("%lli", &Q);
    /*
        * rhymes - массив со считалками.
        * indices - массив индексов, который мы отсортируем вместе с rhymes,
        чтобы потом восстановить порядок. Rhymes мы отсортируем, чтобы в цикле
        не искать постоянно считалку под текущий шаг, а просто сдвигаться по порядку.
        * teams1 и teams2 - массивы, в которые мы на места, соответствующие
        считалкам из rhymes будем класть команды на данном шаге.
        * answers1 и answers2 - в них кладем команды после обратной сортировки.
        с помощью индексов из indices.
    */
    long long* rhymes = calloc(Q, sizeof(long long));
    long long* indices = calloc(Q, sizeof(long long));
    game->teams1 = calloc(Q, sizeof(long long));
    game->teams2 = calloc(Q, sizeof(long long));
    long long* answers1 = calloc(Q, sizeof(long long));
    long long* answers2 = calloc(Q, sizeof(long long));

    read_rhymes(Q, rhymes);
    fill_indices(Q, indices);
    array_max(game->queue->values, game->teams_number, &game->max_team, &game->max_team_index);
    quick_sort(rhymes, indices, Q);

    long long rhyme_index = 0;
    manual_games(game, Q, &rhyme_index, rhymes);
    auto_games(game, Q, &rhyme_index, rhymes);

    sort_back(Q, answers1, answers2, indices, game);
    print_results(Q, answers1, answers2);

    free(game->queue->values);
    free(game->queue);
    free(indices);
    free(game->teams1);
    free(game->teams2);
    free(answers1);
    free(answers2);
    free(rhymes);
    return 0;
}
