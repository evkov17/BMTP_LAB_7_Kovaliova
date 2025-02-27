#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>

void cleanWordCyrillic(char *word) {
    char *dest = word;
    unsigned char c;
    
    while (*word) {
        c = (unsigned char)*word;
        
        if ((c == 0xD0 || c == 0xD1) && *(word + 1)) {
            *dest++ = *word++;
            *dest++ = *word;
        }
        word++;
    }
    *dest = '\0';
}

void cleanWordEnglish(char *word) {
    char *dest = word;
    unsigned char c;
    
    while (*word) {
        c = (unsigned char)*word;
        
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            *dest++ = *word;
        }
        word++;
    }
    *dest = '\0';
}

bool looksLikeEnglish(const char *word) {
    int englishChars = 0;
    int cyrillicChars = 0;
    unsigned char c;
    
    while (*word) {
        c = (unsigned char)*word;
        
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
            englishChars++;
        } else if ((c == 0xD0 || c == 0xD1) && *(word + 1)) {
            cyrillicChars++;
            word++;
        }
        word++;
    }
    
    return englishChars > cyrillicChars;
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    setlocale(LC_ALL, "uk_UA.UTF-8");
    
    printf("Автор програми: Ковальова Єва\n");
    printf("Програма перевіряє, чи є слово, яке закінчується символом '|', словом 'Кропивницький'.\n");
    printf("Введення може бути українською ('Кропивницький') або англійською ('Kropyvnytskyi') мовою.\n\n");
    
    char sentence[1000];
    char targetWord[100] = "";
    char cleanedWord[100] = "";
    bool foundWordWithPipe = false;
    
    printf("Введіть речення (слово, яке треба перевірити, повинно закінчуватися '|'): ");
    fgets(sentence, sizeof(sentence), stdin);
    
    sentence[strcspn(sentence, "\n")] = '\0';
    
    char *word = strtok(sentence, " \t\n");
    while (word != NULL) {
        int len = strlen(word);
        if (len > 0 && word[len - 1] == '|') {
            strncpy(targetWord, word, len - 1);
            targetWord[len - 1] = '\0';
            foundWordWithPipe = true;
            break;
        }
        word = strtok(NULL, " \t\n");
    }
    
    if (foundWordWithPipe) {
        printf("Знайдено слово з символом '|': %s\n", targetWord);
        
        if (strcmp(targetWord, "Кропивницький") == 0 || strcmp(targetWord, "Kropyvnytskyi") == 0) {
            printf("Результат перевірки: Так, знайдене слово є 'Кропивницький'/'Kropyvnytskyi'.\n");
        } else {
            strcpy(cleanedWord, targetWord);
            
            bool isEnglish = looksLikeEnglish(targetWord);
            
            if (isEnglish) {
                cleanWordEnglish(cleanedWord);
                printf("Після очищення від спеціальних символів (англійською): %s\n", cleanedWord);
                
                if (strcmp(cleanedWord, "Kropyvnytskyi") == 0) {
                    printf("Результат перевірки: Так, знайдене слово є 'Kropyvnytskyi'.\n");
                } else {
                    printf("Результат перевірки: Ні, знайдене слово не є 'Kropyvnytskyi'.\n");
                }
            } else {
                cleanWordCyrillic(cleanedWord);
                printf("Після очищення від спеціальних символів (українською): %s\n", cleanedWord);
                
                if (strcmp(cleanedWord, "Кропивницький") == 0) {
                    printf("Результат перевірки: Так, знайдене слово є 'Кропивницький'.\n");
                } else {
                    printf("Результат перевірки: Ні, знайдене слово не є 'Кропивницький'.\n");
                }
            }
        }
    } else {
        printf("У реченні немає слова, яке закінчується символом '|'.\n");
    }
    
    printf("\nНатисніть Enter для завершення програми...");
    getchar();
    
    return 0;
}