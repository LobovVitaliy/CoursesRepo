#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main() {
    int x,y=0;
    int s=0,k=40;

    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_yellow = BACKGROUND_RED | BACKGROUND_GREEN;   // YELLOW
    int color_red = BACKGROUND_RED;                         // RED
    int color_purple = BACKGROUND_RED | BACKGROUND_BLUE;    // PURPLE

    do {
        for (x = 0; x < 80; x++) {
            position.X = x;
            position.Y = y;
            SetConsoleCursorPosition(hConsole, position);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                    if (y>=s && y<s+5 && (x<k | x>=k+40))
                            SetConsoleTextAttribute(hConsole, color_yellow);
                    else
                    if (y>=s && y<s+5 && x<k+10)
                           SetConsoleTextAttribute(hConsole, color_purple);
                    else
                    if (y>=s && y<s+5 && x<k+30)
                            SetConsoleTextAttribute(hConsole, color_red);
                    else
                    if (y>=s && y<s+5 && x<k+40)
                            SetConsoleTextAttribute(hConsole, color_purple);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

            puts("*");
            Sleep(1);
        }

        if (y==24) break;

        x--;
        y++;

            position.X = x;
            position.Y = y;
            SetConsoleCursorPosition(hConsole, position);
            puts("*");
            Sleep(1);

        if (y%5==0) {
            s+=5; k-=10;
        }

        for (x = 79; x >= 0; x--) {
            position.X = x;
            position.Y = y;
            SetConsoleCursorPosition(hConsole, position);

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
                    if (y>=s && y<s+5 && (x<k | x>=k+40))
                            SetConsoleTextAttribute(hConsole, color_yellow);
                    else
                    if (y>=s && y<s+5 && x<k+10)
                           SetConsoleTextAttribute(hConsole, color_purple);
                    else
                    if (y>=s && y<s+5 && x<k+30)
                            SetConsoleTextAttribute(hConsole, color_red);
                    else
                    if (y>=s && y<s+5 && x<k+40)
                            SetConsoleTextAttribute(hConsole, color_purple);
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

            puts("*");
            Sleep(1);
        }

        y++;

        if (y%5==0) {
            s+=5; k-=10;
        }

    } while (y<25);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return 0;
}
