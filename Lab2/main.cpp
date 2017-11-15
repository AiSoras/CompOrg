#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int COLORS_NUMBER = 16;

void gotoxy(int x, int y) // set cursor position
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}


enum COLORS {
    BLACK,     BLUE,      GREEN,     CYAN,       RED,       MAGENTA,  BROWN,    
    LIGHTGRAY, DARKGRAY,  LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA,
    YELLOW,   WHITE
};


void set_color(COLORS backgroud, COLORS foreground) // set color for printing
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int x = (backgroud<<4) + foreground;
    SetConsoleTextAttribute(hConsole, x);
}

int color_to_text(int x) // prints color and return length of word
{
    switch (x) {
    case BLACK: { cout << "BLACK"; return 5; }
    case BLUE: { cout << "BLUE"; return 4; }
    case GREEN: { cout << "GREEN"; return 5; }
    case CYAN: { cout << "CYAN"; return 4; }
    case RED: { cout << "RED"; return 3; }
    case MAGENTA: { cout << "MAGENTA"; return 7; }
    case BROWN: { cout << "BROWN"; return 5; }
    case LIGHTGRAY: { cout << "LIGHTGRAY"; return 9; }
    case DARKGRAY: { cout << "DARKGRAY"; return 8; }
    case LIGHTBLUE: { cout << "LIGHTBLUE"; return 9; }
    case LIGHTGREEN: { cout << "LIGHTGREEN"; return 10; }
    case LIGHTCYAN: { cout << "LIGHTCYAN"; return 9; }
    case LIGHTRED: { cout << "LIGHTRED"; return 8; }
    case LIGHTMAGENTA: { cout << "LIGHTMAGENTA"; return 12; }
    case YELLOW: { cout << "YELLOW"; return 6; }
    case WHITE: { cout << "WHITE"; return 5; }
    default:
    { cout << "undefined"; }
    }
}

void row(int b, int f, int width)
{
    int least = width;
    least -= color_to_text(b);
    cout << " ";
    least--;
    least -= color_to_text(f);
    for (int i = 0; i < least; i++) {
        cout << " ";
    }
}

void shift(int* arr, int length, int last_element)
{
    for (int i = 0; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[length - 1] = last_element;
}

void init()
{
    int x1 = 25, x2 = 55;
    int y1 = 5,  y2 = 15;

    int rows = y2 - y1;
    int width = x2 - x1;

    int color = 0; // Covers all combinations. Changes on each iteration.

    int* background = new int[rows];
    int* foreground = new int[rows];

    memset(background, 0, sizeof(int)*rows);
    memset(foreground, 0, sizeof(int)*rows);
    
    while (true)
    {
        for (int i = 0; i < rows; i++) { // in this loop renders every row
            gotoxy(x1, y1 + i);
            set_color((COLORS)background[i], (COLORS)foreground[i]);
            row(background[i], foreground[i], width);
        }
        // we made shift for each array
        shift(background, rows, (color>>4));
        shift(foreground, rows, (color&15));
        color++;
        Sleep(600);
    }
}


int main()
{
    init();
    return 0;
}
