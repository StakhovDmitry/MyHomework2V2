#define _CRT_SECURE_NO_WARNINGS

#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <iostream>
#include <stdio.h>

int main() {
    int n;
    int k = 0;
    int f = 0;
    int t = 1;
    bool flag = false;
    scanf_s("%d", &n);
    int* arr = (int*)malloc(n * n * sizeof(int));

    for (int i = 0; i < n; i++) {
        printf("%d:", i);

        for (int j = 0; j < n; j++) {
            scanf_s("%d", (arr + i * n + j));
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((i == j) && (arr[i * n + j] != 0)) {    //проверка диагонали
                printf("not a simple cycle");
                return (-1);
            }

            if (arr[i * n + j] != arr[j * n + i]) {     //проверка симметричности относительно диагонали
                printf("not a simple cycle");
                return (-1);
            }

            if (arr[i * n + j] != 0 && arr[i * n + j] != 1) {      //проверка либо отсутвия ребра между вершинами, либо наличия лишь 1 таковой
                printf("not a simple cycle\n");
                return (-1);
            }

            if (arr[i * n + j] == 1) {      //проверка того, что из каждой вершины выходит ровно ребра
                k++;
            }

            if (k > 2) {
                printf("not a simple cycle\n");
                return (-1);
            }
        }
        k = 0;
    }

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {

            if ((arr[k * n + j] == 1) && (j != t) && (flag == false)) {     //проверка обходом
                t = k;
                k = j;
                flag = true;
            }
        }
        flag = false;

        if ((k == 0) && (i != n - 1)) {
            printf("not a simple cycle\n");
            return (-1);
        }

        if ((i == n - 1) && (k != 0)) {
            printf("not a simple cycle\n");
            return (-1);
        }
    }
    printf("simple cycle");

 // визуализация //

    FILE* file;

    if ((file = fopen("Dot_file.txt", "w")) == NULL) {
        printf("Cannot open file.\n");
        exit(1);
    }
    fprintf(file, "graph G{\n");

    for (int i = 1; i < n; i++) {

        for (int j = 0; j < i; j++) {

            if (arr[i * n + j] == 1) {
                fprintf(file, "%d -- %d;\n", (i + 1), (j + 1));
            }
        }
    }
    fprintf(file, "}");
    fclose(file);
    system("dot C:\\Users\\User\\Desktop\\Алгоритмы\\MyHomework2V2\\Homework2\\Homework2\\Dot_file.txt -Tbmp -o Dot_file.bmp");
    system("rundll32 \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\User\\Desktop\\Алгоритмы\\MyHomework2V2\\Homework2\\Homework2\\Dot_file.bmp");
    return (0);
}
