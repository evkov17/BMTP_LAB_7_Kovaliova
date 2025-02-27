#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <windows.h>

#define ARRAY_SIZE 20

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    setlocale(LC_ALL, "uk_UA.UTF-8");
    
    printf("Автор програми: Ковальова Єва\n");
    printf("Програма замінює найменший елемент масиву на суму всіх елементів.\n");
    printf("Масив з %d натуральних чисел генерується автоматично.\n\n", ARRAY_SIZE);
    
    int minRange = 1;
    int maxRange = 100;
    
    srand((unsigned int)time(NULL));
    
    int array[ARRAY_SIZE];
    
    printf("Вхідний масив:\n[ ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = minRange + rand() % (maxRange - minRange + 1);
        printf("%d", array[i]);
        if (i < ARRAY_SIZE - 1) {
            printf(", ");
        }
        if ((i + 1) % 10 == 0) {
            printf("\n  ");
        }
    }
    printf(" ]\n\n");
    
    int minValue = array[0];
    int minIndex = 0;
    int sum = array[0];
    
    for (int i = 1; i < ARRAY_SIZE; i++) {
        sum += array[i];
        
        if (array[i] < minValue) {
            minValue = array[i];
            minIndex = i;
        }
    }
    
    printf("Найменший елемент: %d (індекс %d)\n", minValue, minIndex);
    printf("Сума всіх елементів: %d\n\n", sum);
    
    array[minIndex] = sum;
    
    printf("Вихідний масив (після заміни найменшого елемента на суму):\n[ ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d", array[i]);
        if (i < ARRAY_SIZE - 1) {
            printf(", ");
        }
        if ((i + 1) % 10 == 0) {
            printf("\n  ");
        }
    }
    printf(" ]\n");
    
    printf("\nНатисніть Enter для завершення програми...");
    getchar();
    
    return 0;
}
