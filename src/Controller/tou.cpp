// 界面/tou.cpp
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#include <stdio.h>
#include <string.h> 
#include "tou.h"
#include <windows.h> 


// 实现setColor（控制台文字颜色设置）
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// 实现resetColor（恢复默认颜色）
void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); // 默认控制台颜色
}