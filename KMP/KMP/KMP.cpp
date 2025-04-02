#include <iostream>
#include <cstring>
#include <clocale>
using namespace std;

// Функция для вычисления префикс-функции
void computeLPSArray(const char* pattern, int patternLength, int* lps) {
    int len = 0; // Длина предыдущего наибольшего префикса, который также является суффиксом
    lps[0] = 0;  // lps[0] всегда 0

    int i = 1;
    while (i < patternLength) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Функция для поиска подстроки с использованием алгоритма КМП
void KMPSearch(const char* text, const char* pattern) {
    int textLength = strlen(text);
    int patternLength = strlen(pattern);

    // Создаем массив для хранения префикс-функции
    int* lps = new int[patternLength];

    // Вычисляем префикс-функцию
    computeLPSArray(pattern, patternLength, lps);

    int i = 0; // Индекс для текста
    int j = 0; // Индекс для паттерна
    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == patternLength) {
            cout << "Найдено вхождение подстроки в позиции " << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    delete[] lps;
}

int main() {
    setlocale(LC_ALL, "russian");
    const char* text = "ABABDABACDABABCABAB";
    const char* pattern = "ABABCABAB";

    cout << "Текст: " << text << endl;
    cout << "Поиск подстроки: " << pattern << endl;

    KMPSearch(text, pattern);

    return 0;
}