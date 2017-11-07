#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

int sx = 35, sy = 7;

void gotoxy(int x, int y)
{
    COORD p = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

void render_window(int x1, int x2, int y1, int y2) {
    gotoxy(x1, y1-2);
    for (int xi = 0; xi < (x2 - x1); xi++) cout << "-";
    for (int yi = y1; yi < y2; yi++) {
        gotoxy(x1-2, yi); cout << "|";
        gotoxy(x2, yi); cout << "|";
    }
    gotoxy(x1-2, y2);
    for (int xi = 0; xi <= (x2 - x1); xi++) cout << "-";
}

void draw_symbol()
{
    gotoxy(sx - 1, sy - 1);
    cout << "0";
}

void remove_symbol()
{
    gotoxy(sx - 1, sy - 1);
    cout << " ";
}

void move_symbol(int c, int x1, int x2, int y1, int y2)
{
    //cout << c;
    switch (c)
    {
    case 97: { // left
        remove_symbol();
        sx = sx == x1 ? sx : sx - 1;
        draw_symbol();
        break;
    }
    case 100: { //right
        remove_symbol();
        sx = sx == x2 ? sx : sx + 1;
        draw_symbol();
        break;
    }
    case 119: { //up
        remove_symbol();
        sy = sy == y1 ? sy : sy - 1;
        draw_symbol();
        break;
    }
    case 115: { // down
        remove_symbol();
        sy = sy == y2 ? sy : sy + 1;
        draw_symbol();
        break;
    }
    default:
    {gotoxy(sx - 1, sy - 1); cout << "0"; }
    }
}

void main()
{
    int c;
    int x1 = 25, x2 = 55;
    int y1 = 5, y2 = 15;
    
    render_window(x1, x2, y1, y2);
    while (1) {
        c = _getch();
        move_symbol(c, x1,x2,y1,y2);
    }
    return;
}