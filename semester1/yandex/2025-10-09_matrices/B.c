#include <stdio.h>


int main(void) {
    int number = 0;
    enum sounds {meow = 1, woof, oink, cow, whoosh, byebye};
    while (number != 6) {
        scanf("%d", &number);
        switch (number) {
            case meow:
                printf("meow\n");
                break;
            case woof:
                printf("woof\n");
                break;
            case oink:
                printf("oink\n");
                break;
            case cow:
                printf("caw\n");
                break;
            case whoosh:
                printf("whoosh\n");
                break;
            case byebye:
                printf("bye-bye");
                break;
        }
    }
    return 0;
}
