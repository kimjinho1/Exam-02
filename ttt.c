#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int check(int arr[], int rd) {
    for (int i = 0; i < 6; i++) {
        if (arr[i] == rd)
            return (0);
    }
    return (1);
}

void random_no(int arr[]) {
    int i = 0;
    int rd;

    srand(time(NULL));
    while (i < 6) {
        rd = rand() % 44 + 1;
        if (check(arr, rd))
            arr[i++] = rd;
    }
}

void sort(int arr[]) {
    int t;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 5; j++) {
            if (arr[j] > arr[j + 1]) {
                t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
        }
    }
}

void print_lotto(int arr[]) {
    for (int i = 0; i < 6; i++) {
        if (i < 5)
            printf("%d   ", arr[i]);
        else
            printf("%d\n", arr[i]);
    }
    printf("종료하시려면 ESC키를 눌러 주시고 계속하려면 Enter키를 눌러 주세요\n");
}

int main(void)
{
    int arr[6], c;
    int flag = 1;

    while (flag) {
        random_no(arr);
        sort(arr);
        print_lotto(arr);
        while (1) {
            c = _gecth();
            if (c == 27) {
                flag = 0;
                break;
            }
            else if (c == 13)
                break;
        }
    }
}