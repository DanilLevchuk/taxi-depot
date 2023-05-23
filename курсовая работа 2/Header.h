#pragma once


#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "interface.h"
#include <chrono>
#include <thread>

using namespace std;



struct User {
    string login;
    string password;
    bool isAdmin;
    bool isBanned;
    struct Info {
        string FIO;
        int age;
    }info;

};



struct Car {
    string name;
    float price;
    string manufacturer;
    int quantity;
    int minAge;
    int quantityseats;
    float fuelcosumption;
    string body;

};

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
    CONSOLE_CURSOR_INFO structCursorInfo;
    GetConsoleCursorInfo(hStdOut, &structCursorInfo);
    structCursorInfo.bVisible = show; // изменяем видимость
    structCursorInfo.dwSize = size; // изменяем размер
    SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}
void Cyan() {
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
}
void Yellow() {
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void Orange() {
    SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN);
}
void Red() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
}