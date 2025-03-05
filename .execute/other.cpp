/*
本文件用于对程序中 「按任意键继续」等一些功能的合集，用于存放一些零散函数
*/
#include <iostream>
#include "head.h"
char get_ch()
{
    return _getch();
}

void fast_clear()
{
    char ch;
    ch = get_ch(); // 快速读取清空缓冲区
    system("cls");
}