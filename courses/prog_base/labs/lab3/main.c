#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <string.h>
//#include <ctype.h>

void printMas (int mas[], int size);
void fillRand_diapason (int mas[], int size, int diapason_left, int diapason_right); // - Заповнити випадковими числами у діапазоні
void resetElements (int mas[], int size);                                            // - Обнулити всі елементи масиву
void editElements (int mas[], int size, int edit_index, int edit_value);             // - Змінити елемент масиву
void reverseOrder (int mas[], int size);                                             // - Вивести елементи масиву у зворотньому порядку
int quantityPositiveElements (int mas[], int size);                                  // - Вивести кількість додатніх елементів масиву (0також)
void leftShift (int mas[], int size, int number_of_positions);                       // - Простий зсув вліво на введену кількість позицій
void cyclic_leftShift (int mas[], int size, int number_of_positions);                // - Циклічний зсув вліво на введену кількість позицій
void min_to_max (int mas[], int size);                                               // - Поміняти останній мін і перший макс елементи місцями
void raisingDegree (int mas[], int size, int degree);                                // - Підняття всіх елементів до визначеного степеня
int maxElement (int mas[], int size);                                                // - Вивести максимальний елемент масиву
int index_maxElement (int mas[], int size);                                          // - Вивести індекс максимального елемента масиву

int new_size (int mas[], int size);                                                  // - допоміжна для new_mas
void new_mas (int mas[], int m[], int size, int sum);                                // - Вивести тільки додатні елементи масиву (0 також)

void first_window ();
void second_window ();

void help ();
void clean ();
void pos_of_output (int size, int diapason_left, int diapason_right);  // позиція виведення масиву
void pos_error ();      // позиція виведення помилок
void press_continue (); // для продовження операції
void enter_word ();     // введення слова
void remove_word ();    // видалення слова

char  *command[40] = {
  "clean",                  "to set all elements to zeros",
  "set $i $j",              "to set $i to new $element",
  "random $i $j",           "to flip in diapason $left $right",
  "reverse",                "to get elements in reverse order",
  "positive",               "to get only positive elements",
  "num of pos",             "to get a number of positive elements",
  "left sh $i",             "left shift. $number of position",
  "cyclic left sh &i",      "cyclic left shift. $number of position",
  "degree $i",              "to get elements in $degree",
  "max",                    "to get the first maximum and his index",
  "min to max",             "to set the last minimum to the first maximum",
  "exit",                   "to close program",
};

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    srand (time(NULL));

    int i;
    int size;
    int check;
    char str[50];
    char word[50];

    int diapason_left;
    int diapason_right;

// ввод размера массива
    first_window ();
    check = 0;
    do {
        pos.X = 28;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        printf("                        ");
        pos.X = 28;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);
        gets(str);
        size = atoi(str);
        SetConsoleTextAttribute(hConsole, 0x07);

        if(size > 0 && size < 13) {
            system("cls");
            check = 1;
        }
        else {
            pos.X = 23;
            pos.Y = 9;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole,FOREGROUND_RED | BACKGROUND_GREEN);
            puts("Invalid input, please, try again");
        }
    } while(check == 0);
// end

    int mas[size];

// операции над массивом
    second_window ();
    check = 0;
    do {
        enter_word ();
        gets(word);

        if (strcmp(word,"help") == 0) {
            help();
            getch();
        }
        else
        if (strncmp(word,"random",6) == 0) {

            diapason_left = atoi(strpbrk(word,"-0123456789")); // первое вхождение
            int h = diapason_left;
            int sum; // количество знаков в числе

            if (h>0)
                sum = 1;    // если число положительное, то как минимум 1 знак
            else
                sum = 2;    // если число отрицательное, то как минимум 2 знака

            while (abs(h)>9) {
                h = h / 10;
                sum++;
            }

            diapason_right = atoi(strpbrk(word,"-0123456789")+sum);

            if (diapason_left < -100 || diapason_right > 100) {
                pos_error ();
                puts ("Invalid restart argument.            -100 < diapason < 100");
                press_continue ();
            }
            else
            if (diapason_left > diapason_right) {
                pos_error ();
                puts ("Invalid restart argument.            left diapason < right diapason");
                press_continue ();
            }
            else {
                fillRand_diapason (mas,size,diapason_left,diapason_right);
                pos_of_output (size, diapason_left, diapason_right);
                printMas (mas,size);

                SetConsoleTextAttribute(hConsole, 0x07);

                do {
                    remove_word ();
                    enter_word ();
                    gets(word);

                    if (strcmp(word,"help") == 0) {
                        help();
                        getch();
                    }
                    else
                    if (strcmp(word,"clean") == 0) {
                        resetElements (mas,size);
                        pos_of_output (size, diapason_left, diapason_right);
                        printMas (mas,size);
                    }
                    else
                    if (strncmp(word,"random",6) == 0) {

                        diapason_left = atoi(strpbrk(word,"-0123456789")); // первое вхождение
                        int h = diapason_left;
                        int sum; // количество знаков в числе

                        if (h>0)
                            sum = 1;    // если число положительное, то как минимум 1 знак
                        else
                            sum = 2;    // если число отрицательное, то как минимум 2 знака

                        while (abs(h)>9) {
                            h = h / 10;
                            sum++;
                        }

                        diapason_right = atoi(strpbrk(word,"-0123456789")+sum);

                        if (diapason_left < -100 || diapason_right > 100) {
                            pos_error ();
                            puts ("Invalid restart argument.            -100 < diapason < 100");
                            press_continue ();
                        }
                        else
                        if (diapason_left > diapason_right) {
                            pos_error ();
                            puts ("Invalid restart argument.            left diapason < right diapason");
                            press_continue ();
                        }
                        else {
                            fillRand_diapason (mas,size,diapason_left,diapason_right);
                            pos_of_output (size, diapason_left, diapason_right);
                            printMas (mas,size);
                        }
                    }
                    else
                    if (strcmp(word,"max") == 0) {
                        pos.X = 5;
                        pos.Y = 13;
                        SetConsoleCursorPosition(hConsole, pos);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                        printf("Maximal element is ");
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printf("%i\t", maxElement (mas, size));

                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                        printf("Index of maximal element is ");
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printf("%i", index_maxElement (mas, size));

                        press_continue ();
                    }
                    else
                    if (strcmp(word,"num of pos") == 0) {
                        pos.X = 5;
                        pos.Y = 13;
                        SetConsoleCursorPosition(hConsole, pos);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                        printf("The number of positive elements is ");
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                        printf("%i\t", quantityPositiveElements (mas,size));

                        press_continue ();
                    }
                    else
                    if (strcmp(word,"reverse") == 0) {
                        reverseOrder (mas,size);
                        pos_of_output (size, diapason_left, diapason_right);
                        printMas (mas,size);
                    }
                    else
                    if (strcmp(word,"min to max") == 0) {
                        min_to_max (mas,size);
                        pos_of_output (size, diapason_left, diapason_right);
                        printMas (mas,size);
                    }
                    else
                    if (strcmp(word,"positive") == 0) {
                        pos.X = 5;
                        pos.Y = 13;
                        SetConsoleCursorPosition(hConsole, pos);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

                        int sum = new_size (mas,size);
                        int m[sum];

                        if (sum != 0) {

                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                            if (sum==1)
                                printf("The positive element is ");
                            else
                                printf("The positive elements are ");

                            new_mas (mas, m, size, sum);
                            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                            for (i = 0; i < sum; i++)
                                printf("%i ", m[i]);
                        }
                        else {
                            pos.X = 5;
                            pos.Y = 13;
                            SetConsoleCursorPosition(hConsole, pos);
                            puts ("No positive elements");
                        }

                        press_continue ();
                    }
                    else
                    if (strncmp(word,"set",3) == 0) {

                        int edit_index = atoi(strpbrk(word,"-0123456789")); // первое вхождение
                        int h = edit_index;
                        int sum; // количество знаков в числе

                        if (h>0)
                            sum = 1;    // если число положительное, то как минимум 1 знак
                        else
                            sum = 2;    // если число отрицательное, то как минимум 2 знака

                        while (abs(h)>9) {
                            h = h / 10;
                            sum++;
                        }

                        int edit_value = atoi(strpbrk(word,"-0123456789")+sum);

                        if (edit_index < 0 || edit_index >= size) {
                            pos_error ();
                            puts ("Invalid restart argument.            0 <= index < size");
                            press_continue ();
                        }
                        else {
                            editElements (mas, size, edit_index, edit_value);
                            pos_of_output (size, diapason_left, diapason_right);
                            printMas (mas,size);
                        }
                    }
                    else
                    if (strncmp("degree",word,6) == 0) {

                        int degree = atoi(strpbrk(word,"-0123456789")); // первое вхождение

                        if (degree < 0) {
                            pos_error ();
                            puts ("Invalid restart argument.            degree >= 0");
                            press_continue ();
                        }
                        else {
                            raisingDegree (mas, size, degree);
                            pos_of_output (size, diapason_left, diapason_right);
                            printMas (mas,size);
                        }
                    }
                    else
                    if (strncmp("cyclic left sh",word,14) == 0) {

                        int number_of_positions = atoi(strpbrk(word,"-0123456789")); // первое вхождение

                        if (number_of_positions < 0 ) {
                            pos_error ();
                            puts ("Invalid restart argument.            number of positions >= 0");
                            press_continue ();
                        }
                        else {
                            cyclic_leftShift (mas, size, number_of_positions);
                            pos_of_output (size, diapason_left, diapason_right);
                            printMas (mas,size);
                        }
                    }
                    else
                    if (strncmp("left sh",word,7) == 0) {

                        int number_of_positions = atoi(strpbrk(word,"-0123456789")); // первое вхождение

                        if (number_of_positions < 0 ) {
                            pos_error ();
                            puts ("Invalid restart argument.            number of positions >= 0");
                            press_continue ();
                        }
                        else {
                            leftShift (mas, size, number_of_positions);
                            pos_of_output (size, diapason_left, diapason_right);
                            printMas (mas,size);
                        }
                    }
                    else
                    if (strcmp(word,"exit") == 0) {
                        check = 1;
                    }
                    else {
                        pos_error ();
                        puts ("No such command");
                        press_continue ();
                    }

                    SetConsoleTextAttribute(hConsole, 0x07);
                    clean();
                    remove_word ();

                } while (check == 0);
            }
        }
        else
        if (strcmp(word,"exit") == 0) {
            check = 1;
        }
        else {
            pos_error ();
            puts ("No such command or the array is not specified");
            press_continue ();
        }

        SetConsoleTextAttribute(hConsole, 0x07);
        clean();
        remove_word ();

    } while (check == 0);
// end

    pos.X = 0;
    pos.Y = 40;
    SetConsoleCursorPosition(hConsole, pos);

return EXIT_SUCCESS;
}


// функции для работы с массивом
void fillRand_diapason (int mas[], int size, int diapason_left, int diapason_right) {
    int i;

    for (i = 0; i < size; i++) {
        mas[i] = rand()%(diapason_right - diapason_left + 1) + diapason_left;
    }
}

void printMas (int mas[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        printf("%i  ",mas[i]);
    }
}

void resetElements (int mas[], int size) {
    int i;

    for (i = 0; i < size; i++) {
        mas[i] = 0;
    }
}

void editElements (int mas[], int size, int edit_index, int edit_value) {
    mas[edit_index] = edit_value;
}

void reverseOrder (int mas[], int size) {
    int i;
    int mas_help[size];

    for (i = 0; i < size; i++) {
        mas_help[size-i-1] = mas[i];
    }

    for (i = 0; i < size; i++) {
        mas[i] = mas_help[i];
    }
}

int new_size (int mas[], int size){
    int i;
    int sum = 0;

    for (i = 0; i < size; i++) {
        if (mas[i] >= 0) {
            sum++;
        }
    }

return sum;
}

void new_mas (int mas[], int m[], int size, int sum) {
    int i,j = 0;

    for (i = 0; i < size; i++) {
        if (mas[i] >= 0) {
            m[j] = mas[i];
            j++;
        }
    }
}

int quantityPositiveElements (int mas[], int size) {
    int i,quantity_positive_elements = 0;

    for (i = 0; i < size; i++) {
        if (mas[i] >= 0)
            quantity_positive_elements++;
    }

return quantity_positive_elements;
}

void leftShift (int mas[], int size, int number_of_positions) {
    int i;
    int mas_help[size];

    for (i = 0; i < size; i++) {
        mas_help[i] = mas[i];
    }

    if (number_of_positions < size) {
        for (i = size-1; i >= number_of_positions; i--)
            mas[i-number_of_positions] = mas_help[i];

        for (i = size-1; i > size - 1 - number_of_positions; i--)
            mas[i] = 0;
    }
    else
        for (i = size-1; i >= 0; i--)
            mas[i] = 0;
}

void cyclic_leftShift (int mas[], int size, int number_of_positions) {
    int i;
    int mas_help[size];
    int k = 0;

    for (i = 0; i < size; i++) {
        mas_help[i] = mas[i];
    }

    while (number_of_positions >= size)
        number_of_positions-=size;

    for (i = size-1; i >= number_of_positions; i--)
        mas[i-number_of_positions] = mas_help[i];

    for (i = size - number_of_positions; i < size; i++,k++)
        mas[i] = mas_help[k];
}

void min_to_max (int mas[], int size) {
    int i;
    int index_max;
    int index_min;

    int max = mas[0];
    for (i = size - 1; i >= 0; i--) {
        if (max <= mas[i]) {
            max = mas[i];
            index_max = i;
        }
    }

    int min = mas[0];
    for (i = 0; i < size; i++) {
        if (min >= mas[i]) {
            min = mas[i];
            index_min = i;
        }
    }

    for (i = 0; i < size; i++) {
        if (i == index_max)
            mas[i] = min;
        else
        if (i == index_min)
            mas[i] = max;
    }
}

void raisingDegree (int mas[], int size, int degree) {
    int i;

    for (i = 0; i < size; i++) {
        mas[i] = 0.5 + pow(mas[i],degree);
    }
}

int maxElement (int mas[], int size) {
    int i;
    int max = mas[0];

    for (i = size -1; i >= 0; i--) {
        if (max <= mas[i]) {
            max = mas[i];
        }
    }
return max;
}

int index_maxElement (int mas[], int size) {
    int i,index_max;
    int max = mas[0];

    for (i = size -1; i >= 0; i--) {
        if (max <= mas[i]) {
            max = mas[i];
            index_max = i;
        }
    }
return index_max;
}

// вспомогательные функции
void help () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    int y;
    int i;

    for (i = 0, y = 13; i < 24; i+=2, y++) {
        pos.X = 8;
        pos.Y = y;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        printf("%s", command[i]);
        printf("\n");
    }

    for (i = 0, y = 13; i < 23; i+=2, y++) {
        pos.X = 35;
        pos.Y = y;
        SetConsoleCursorPosition(hConsole, pos);
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
        printf("%s", command[i+1]);
        printf("\n");
    }

    pos.X = 8;
    pos.Y = 26;
    SetConsoleCursorPosition(hConsole, pos);
    puts("Press any key to continue");

    pos.X = 33;
    pos.Y = 26;
    SetConsoleCursorPosition(hConsole, pos);
}

void first_window () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    int x,y;

    for (y = 3; y < 12; y++) {
        for (x = 19; x < 59; x++) {
            pos.X = x;
            pos.Y = y;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
            if (y==3 || y==11 || x==19 || x==58)
                puts("%");
            else
                puts(" ");
        }
    }

    pos.X = 26;
    pos.Y = 5;
    SetConsoleCursorPosition(hConsole, pos);
    puts("Enter matrix size [1..12]:");

    pos.X = 26;
    pos.Y = 7;
    SetConsoleCursorPosition(hConsole, pos);
    puts(">>");
}

void second_window () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    int x,y;

    for (y = 1; y < 8; y++) {
        for (x = 2; x < 78; x++) {
            pos.X = x;
            pos.Y = y;
            SetConsoleCursorPosition(hConsole, pos);
            SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
            if (y==1 || y==7 || x==2 || x==77)
                puts("%");
            else
                puts(" ");
        }
    }

    SetConsoleTextAttribute(hConsole, 0x07);

    pos.X = 3;
    pos.Y = 9;
    SetConsoleCursorPosition(hConsole, pos);
    puts("Please, enter your command:");

    pos.X = 3;
    pos.Y = 11;
    SetConsoleCursorPosition(hConsole, pos);
    puts(">>");
}

void clean () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    int y;

    for (y = 12; y < 27; y++) {
        pos.X = 0;
        pos.Y = y;
        SetConsoleCursorPosition(hConsole, pos);
        puts("                                                                                ");
    }
}

void pos_of_output (int size, int diapason_left, int diapason_right) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    int x;

    pos.X = 3;
    pos.Y = 4;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    puts("                                                                          ");

    // индусский код:...
    switch (size) {
        case 1: x = 39;  break;
        case 2: x = 36;  break;
        case 3: x = 33;  break;
        case 4: x = 30;  break;
        case 5: x = 27;  break;
        case 6: x = 25;  break;
        case 7: x = 21;  break;
        case 8: x = 18;  break;
        case 9: x = 15;  break;
        case 10: x = 15; break;
        case 11: x = 14; break;
        case 12: x = 14; break;
    }

    if (diapason_left > -10 && diapason_left < 10 && diapason_right > -10 && diapason_right < 10) {
        x+=4;
    }
    // конец)

    pos.X = x;
    pos.Y = 4;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN | FOREGROUND_BLUE);
}

void pos_error () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X = 5;
    pos.Y = 13;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void press_continue () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X = 5;
    pos.Y = 15;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    puts("Press any key to continue");

    pos.X = 30;
    pos.Y = 15;
    SetConsoleCursorPosition(hConsole, pos);
    getch();
}

void enter_word () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X = 5;
    pos.Y = 11;
    SetConsoleCursorPosition(hConsole, pos);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
}

void remove_word () {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;

    pos.X = 5;
    pos.Y = 11;
    SetConsoleCursorPosition(hConsole, pos);
    puts("                                                                           ");
}
