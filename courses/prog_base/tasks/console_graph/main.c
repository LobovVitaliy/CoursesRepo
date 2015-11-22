#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void coordinate_axis (int p_x, int p_y);
void first_graph (int p_x, int p_y);
void second_graph (int p_x, int p_y);

int main(void)
{
    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    float x, y, f, i;
    int px, py;
    int num, check = 0;
    int size = 1;
    int p_x = 0, p_y = 0;

    do {
        pos.X = 0;
        pos.Y = 0;
        SetConsoleCursorPosition(hConsole, pos);
        puts("w - Up\ns - Down\na - Left\nd - Right\n\n'-' - decrease\n'+' - increase\nit does not work\n");
        printf("Select a graph ( 1 or 2) ");
        char str[50];
        gets(str);
        num = atoi(str);

        pos.X = 25;
        pos.Y = 9;
        SetConsoleCursorPosition(hConsole, pos);
        puts("                               ");

        if(num > 0 && num < 3) {
            system("cls");
            check = 1;
        }
        else
            puts("Invalid input, please, try again");

    } while (check == 0);

    check = 0;

    do {
        if (num == 1) {
            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, 0x07);
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            puts("F(x) = -2 * sqrt(x + 3)");
            coordinate_axis (p_x, p_y);
            first_graph (p_x, p_y);
        }
        else
        if (num == 2) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_INTENSITY);
            coordinate_axis (p_x, p_y);
            second_graph (p_x, p_y);

            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, 0x07);
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_INTENSITY);
            puts("F(x) = 0.4 * ctg(x) - 2");
        }

        pos.X = 24;
        pos.Y = 0;
        SetConsoleCursorPosition(hConsole, pos);

        char com = getch();

        if (com == 'w') p_y-=3;
        else
        if (com == 's') p_y+=3;
        else
        if (com == 'a') p_x-=5;
        else
        if (com == 'd') p_x+=5;
        else
        if (com == '-') size--;
        else
        if (com == '=') size++;
        else
            continue;

        SetConsoleTextAttribute(hConsole, 0x07);
        system("cls");

    } while (check == 0);

return 0;
}


void coordinate_axis (int p_x, int p_y) {

    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int px,py;

    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_GREEN);
    for (px = 0; px < 80; px++) {
        py = 15;
        pos.X = px;
        pos.Y = py + p_y;
        SetConsoleCursorPosition(hConsole, pos);
        if ((int)px%5 == 0)
            puts("+");
        else
            puts("-");
    }

    for (py = 0; py < 31; py++) {
        px = 40;
        pos.X = px + p_x;
        pos.Y = py;
        SetConsoleCursorPosition(hConsole, pos);
        if ((int)py%3 == 0)
            puts("+");
        else
            puts("|");
    }
}

void first_graph (int p_x, int p_y) {

    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    float x,y,f,i;
    int px,py;

    for (x = -3; x < 8 - p_x/5; x+=0.01) {
        y =  -2 * sqrt(x + 3);

        // floorf(x) - меньше значения аргумента x или равно ему

        if ((int)floorf(x) == -8 - p_x/5)    px = 0;
        if ((int)floorf(x) == -7 - p_x/5)    px = 5;
        if ((int)floorf(x) == -6 - p_x/5)    px = 10;
        if ((int)floorf(x) == -5 - p_x/5)    px = 15;
        if ((int)floorf(x) == -4 - p_x/5)    px = 20;
        if ((int)floorf(x) == -3 - p_x/5)    px = 25;
        if ((int)floorf(x) == -2 - p_x/5)    px = 30;
        if ((int)floorf(x) == -1 - p_x/5)    px = 35;

        if ((int)floorf(x) == 0 - p_x/5)     px = 40;
        if ((int)floorf(x) == 1 - p_x/5)     px = 45;
        if ((int)floorf(x) == 2 - p_x/5)     px = 50;
        if ((int)floorf(x) == 3 - p_x/5)     px = 55;
        if ((int)floorf(x) == 4 - p_x/5)     px = 60;
        if ((int)floorf(x) == 5 - p_x/5)     px = 65;
        if ((int)floorf(x) == 6 - p_x/5)     px = 70;
        if ((int)floorf(x) == 7 - p_x/5)     px = 75;

        f = modff(x, &i);

        if (f > -1   && f <= -0.9)      px += 0;
        if (f > -0.9 && f <= -0.7)      px += 1;
        if (f > -0.7 && f <= -0.5)      px += 2;
        if (f > -0.5 && f <= -0.3)      px += 3;
        if (f > -0.3 && f <= -0.1)      px += 4;
        if (f > -0.1 && f <    0)       px += 5;

        if (f > 0.9 && f <   1)         px += 5;
        if (f > 0.7 && f <= 0.9)        px += 4;
        if (f > 0.5 && f <= 0.7)        px += 3;
        if (f > 0.3 && f <= 0.5)        px += 2;
        if (f > 0.1 && f <= 0.3)        px += 1;
        if (f >  0  && f <= 0.1)        px += 0;

//#####################################################################

        if ((int)ceil(y) == -5 + p_y/3)    break;
        if ((int)ceil(y) == -4 + p_y/3)    py = 27;
        if ((int)ceil(y) == -3 + p_y/3)    py = 24;
        if ((int)ceil(y) == -2 + p_y/3)    py = 21;
        if ((int)ceil(y) == -1 + p_y/3)    py = 18;

        if ((int)ceil(y) == 0 + p_y/3)     py = 15;
        if ((int)ceil(y) == 1 + p_y/3)     py = 12;
        if ((int)ceil(y) == 2 + p_y/3)     py = 9;
        if ((int)ceil(y) == 3 + p_y/3)     py = 6;
        if ((int)ceil(y) == 4 + p_y/3)     py = 3;
        if ((int)ceil(y) == 5 + p_y/3)     py = 0;

        f = modff(y, &i);

        if (f >  -1   && f <= -0.75)   py += 3;
        if (f > -0.75 && f <= -0.45)   py += 2;
        if (f > -0.45 && f <= -0.15)   py += 1;
        if (f > -0.15 && f <    0)     py += 0;

        if (f > 0.75 && f <  1.0)      py += 0;
        if (f > 0.45 && f <= 0.75)     py += 1;
        if (f > 0.15 && f <= 0.45)     py += 2;
        if (f >  0   && f <= 0.15)     py += 3;

        if (px > 79) continue;

        pos.X = px;
        pos.Y = py;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
        puts(" ");
    }
}

void second_graph (int p_x, int p_y) {

    COORD pos;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    float x,y,f,i;
    int px,py;

    for (x = -8 - p_x/5; x < 8 - p_x/5; x+=0.001) {
        y =  0.4 / tanf(x) - 2;

        // floorf(x) - меньше значения аргумента x или равно ему

        if ((int)floorf(x) == -8 - p_x/5)    px = 0;
        if ((int)floorf(x) == -7 - p_x/5)    px = 5;
        if ((int)floorf(x) == -6 - p_x/5)    px = 10;
        if ((int)floorf(x) == -5 - p_x/5)    px = 15;
        if ((int)floorf(x) == -4 - p_x/5)    px = 20;
        if ((int)floorf(x) == -3 - p_x/5)    px = 25;
        if ((int)floorf(x) == -2 - p_x/5)    px = 30;
        if ((int)floorf(x) == -1 - p_x/5)    px = 35;

        if ((int)floorf(x) == 0 - p_x/5)     px = 40;
        if ((int)floorf(x) == 1 - p_x/5)     px = 45;
        if ((int)floorf(x) == 2 - p_x/5)     px = 50;
        if ((int)floorf(x) == 3 - p_x/5)     px = 55;
        if ((int)floorf(x) == 4 - p_x/5)     px = 60;
        if ((int)floorf(x) == 5 - p_x/5)     px = 65;
        if ((int)floorf(x) == 6 - p_x/5)     px = 70;
        if ((int)floorf(x) == 7 - p_x/5)     px = 75;

        f = modff(x, &i);

        if (f > -1   && f <= -0.9)      px += 0;
        if (f > -0.9 && f <= -0.7)      px += 1;
        if (f > -0.7 && f <= -0.5)      px += 2;
        if (f > -0.5 && f <= -0.3)      px += 3;
        if (f > -0.3 && f <= -0.1)      px += 4;
        if (f > -0.1 && f <    0)       px += 5;

        if (f > 0.9 && f <   1)         px += 5;
        if (f > 0.7 && f <= 0.9)        px += 4;
        if (f > 0.5 && f <= 0.7)        px += 3;
        if (f > 0.3 && f <= 0.5)        px += 2;
        if (f > 0.1 && f <= 0.3)        px += 1;
        if (f >  0  && f <= 0.1)        px += 0;

//#####################################################################

        if ((int)ceil(y) == -5 + p_y/3)    continue;
        else
        if ((int)ceil(y) == -4 + p_y/3)    py = 27;
        else
        if ((int)ceil(y) == -3 + p_y/3)    py = 24;
        else
        if ((int)ceil(y) == -2 + p_y/3)    py = 21;
        else
        if ((int)ceil(y) == -1 + p_y/3)    py = 18;
        else
        if ((int)ceil(y) == 0 + p_y/3)     py = 15;
        else
        if ((int)ceil(y) == 1 + p_y/3)     py = 12;
        else
        if ((int)ceil(y) == 2 + p_y/3)     py = 9;
        else
        if ((int)ceil(y) == 3 + p_y/3)     py = 6;
        else
        if ((int)ceil(y) == 4 + p_y/3)     py = 3;
        else
        if ((int)ceil(y) == 5 + p_y/3)     py = 0;
        else
            continue;

        f = modff(y, &i);

        if (f >  -1   && f <= -0.75)   py += 3;
        if (f > -0.75 && f <= -0.45)   py += 2;
        if (f > -0.45 && f <= -0.15)   py += 1;
        if (f > -0.15 && f <    0)     py += 0;

        if (f > 0.75 && f <  1.0)      py += 0;
        if (f > 0.45 && f <= 0.75)     py += 1;
        if (f > 0.15 && f <= 0.45)     py += 2;
        if (f >  0   && f <= 0.15)     py += 3;

        if (px > 79) continue;

        pos.X = px;
        pos.Y = py;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY);
        puts(" ");
    }
}
