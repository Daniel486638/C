// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <math.h>

void AddTwoNumbers(int First[], int Second[], int Length, int *Array);
int ConvertIntoNumber(int *Array, int Length);
void ConvertIntoArray(int *Loop, int Number);
int Pow(int First, int Second);

int main() {
	int Array[] = {2, 4, 3};
	int Array2[] = {5, 6, 4};
    int Length = sizeof(Array) / sizeof(Array[0]);
    int Result[Length];
    AddTwoNumbers(Array, Array2, Length, Result);
    printf("{");
    for (int i = 0; i <= 2; i++) {
        if (i == 2) {
            printf("%i", Result[i]);
            continue;
        }
        printf("%i, ", Result[i]);
    };
    printf("}");
	return 0;
};

void AddTwoNumbers(int First[], int Second[], int Length, int *Array) {
	int FirstN = ConvertIntoNumber(First, Length);
	int SecondN = ConvertIntoNumber(Second, Length);
	ConvertIntoArray(Array, FirstN + SecondN);
};

int Pow(int First, int Second) {
    if (Second) {
        return First * Pow(First, Second - 1);
    } else {
        return 1;
    };
};

int ConvertIntoNumber(int *Array, int Length) {
    int Result = 0;
    for (int i = 0; i < Length; i++) {
        Result += Array[i] * Pow(10, i);
    };
    return Result;
};

void ConvertIntoArray(int *Loop, int Number) {
    int Length = log10(Number) + 1; // Floored by int type
    for (int i = 1; i <= Length; i++) {
        int Num = Number / Pow(10, Length - i);
        Loop[Length - i] = Num;
        Number -= Num * Pow(10, Length - i);
    };
};
