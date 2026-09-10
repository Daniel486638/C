// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define GetCurrency \
    String = ToCurrency(Currency); \
    printf("%s\n", String); \
    free(String);

char* ToCurrency(signed int);
int Pow(short, short);

int main() {
    int Currency = 68082;
    char *String;
    GetCurrency;
    Currency += 118;
    GetCurrency;
    String = NULL;
    
    return 0;
};

char* ToCurrency(signed int Number) {
    signed char Length = log10(Number) + 1;
    char *String = malloc(Length);
    char Offset = -2;
    bool Point = 0;
    for (int i = 1; i <= Length; i++) {
        signed int Value = Number - Number % Pow(10, Length - i);
        Number -= Value;
        String[i - 1 + Point] = Value / Pow(10, Length - i) + '0';
        if (i == Length + Offset) {
            String[Length + Offset] = '.';
            Point = 1;
        };
    };
    return String;
};

int Pow(short Num1, short Num2) {
    if (Num2) {
        return Num1 * Pow(Num1, Num2 - 1);
    } else {
        return 1;
    };
};
