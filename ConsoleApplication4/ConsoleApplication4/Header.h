#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cmath>
#include <vector>
#include <string>
#include <conio.h>
#include <fcntl.h>
#include <io.h>
using namespace std;

enum Colors { BLACK, DARKBLUE, DARKGREEN, DARKCYAN, DARKRED, DARKMAGENTA, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE };
enum Directions { LEFT = 75, RIGHT = 77, DOWN = 80, UP = 72 };
enum Objects { HALL = 0, WALL = 1, COIN = 2, ENEMY = 3, HEAL = 4 };
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void SetCursor(int x, int y, Colors color, string text, char t)
{

    COORD position;
    position.X = x;
    position.Y = y;
    SetConsoleCursorPosition(h, position);
    SetConsoleTextAttribute(h, color);
    cout << text;
    cout << t;
    cout << "\n";
}