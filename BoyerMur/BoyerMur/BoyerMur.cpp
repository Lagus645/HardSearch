#include <iostream>
#include <clocale>
#include <cstring> // для strlen()
using namespace std;

// Максимальный размер алфавита (ASCII)
const int ALPHABET_SIZE = 256;

// Функция для создания таблицы "плохого символа"
void buildBadCharTable(const char* pattern, int patternLen, int badChar[ALPHABET_SIZE]) {
    // Инициализация таблицы значением -1 (символ не встречается)
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        badChar[i] = -1;
    }
    // Заполнение таблицы последними вхождениями символов
    for (int i = 0; i < patternLen; ++i) {
        badChar[(unsigned char)pattern[i]] = i;
    }
}

// Основная функция поиска по алгоритму Бойера-Мура
void boyerMooreSearch(const char* text, const char* pattern) {
    int textLen = strlen(text);
    int patternLen = strlen(pattern);

    if (patternLen == 0 || textLen < patternLen) {
        cout << "Подстрока не найдена" << endl;
        return;
    }

    int badChar[ALPHABET_SIZE];
    buildBadCharTable(pattern, patternLen, badChar);

    int shift = 0; // Текущий сдвиг в тексте
    while (shift <= (textLen - patternLen)) {
        int j = patternLen - 1; // Идём с конца шаблона

        // Поиск несовпадения справа налево
        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        // Если весь шаблон совпал
        if (j < 0) {
            cout << "Подстрока найдена на позиции: " << shift << endl;
            // Сдвигаем шаблон на длину шаблона или 1 (упрощённо)
            shift += (shift + patternLen < textLen) ?
                patternLen - badChar[(unsigned char)text[shift + patternLen]] : 1;
        }
        else {
            // Сдвигаем шаблон на максимум из плохого символа и 1
            shift += max(1, j - badChar[(unsigned char)text[shift + j]]);
        }
    }
}

int main() {
    setlocale(LC_ALL, "russian");
    const char* text = "ABAAABCDABC";
    const char* pattern = "ABC";
    boyerMooreSearch(text, pattern);
    return 0;
}