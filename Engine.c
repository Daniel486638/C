// Copyright (c) 2026 Марченко Даниил

#include <stdio.h>
#include <stdbool.h>

struct Square {
    struct PosType {
        int x;
        int y;
    } Position;
    struct SizeType {
        int x;
        int y;
    } Size;
};

enum Keys {
    DOWN = 's', 
    UP = 'w', 
    LEFT = 'a', 
    RIGHT = 'd'
};

int CheckAxis(int Symbol, int Axis, int AxisSize);

int main() {
    puts("Choose the square.");
    int CS = getchar() - '1';
    struct Square SquareArray[] = {
        {{5, 12}, {2, 4}},
        {{3, 5}, {4, 3}},
        {{28, 7}, {4, 3}}
    };
    for (int Iteration = 0; 1; Iteration++) {
        for (int Line = 16; Line > 0; Line--) {
            for (int Symbol = 0; Symbol < 34; Symbol++) {
                bool Fill = false;
                for (int SI = 0; SI < sizeof(SquareArray) / sizeof(SquareArray[0]); SI++) { // SI = Square Index
                    struct Square *Sqr = &SquareArray[SI];
                    struct PosType *Pos = &Sqr->Position;
                    struct SizeType *Size = &Sqr->Size;
                    bool xn = CheckAxis(Symbol, Pos->x, -Size->x) >= 0;
                    bool xp = CheckAxis(Symbol, Pos->x, Size->x) <= 0;
                    bool yn = CheckAxis(Line, Pos->y, -Size->y) >= 0;
                    bool yp = CheckAxis(Line, Pos->y, Size->y) <= 0;
                    if (xn && xp && yn && yp) {
                        Fill = true;
                        break;
                    };
                };
                if (Fill == true) {
                    printf("#");
                } else {
                    printf("-");
                };
            };
            puts("");
        };
struct PosType *Pos = &SquareArray[CS].Position;
        getchar();
        char Char;
        Char = getchar();
		bool Exit = false;
        switch(Char) {
            case LEFT:
                Pos->x -= 2;
                break;
            case RIGHT:
                Pos->x += 2;
                break;
            case DOWN:
                Pos->y--;
                break;
            case UP:
                Pos->y++;
                break;
			case 'e':
				Exit = true;
				break;
            default:
                CS = Char - '1';
        };
		if (Exit) {
			break;
		}
    };

    return 0;
}

int CheckAxis(int Symbol, int Axis, int AxisSize) {
    return Symbol - (Axis + AxisSize / 2);
}
