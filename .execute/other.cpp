/*
本文件用于对程序中 「按任意键继续」等一些功能的合集，用于存放一些零散函数
*/
#include <iostream>
#include "head.h"

void fast_clear()
{
    char ch;
    ch = _getch(); // 快速读取清空缓冲区
    system("cls");
}

// 获取哈希值
int get_uuid(const std::string &user_name, const std::string &user_password)
{
    // 使用user_name和user_passworld生成int类型哈希uuid，使得写入文件和查找的时候更加容易
    std::hash<std::string> hash_func;
    size_t name_hash = hash_func(user_name);
    size_t pass_hash = hash_func(user_password);
    //组合hash确保在int范围
    return static_cast<int>((name_hash ^ (pass_hash << 1)) % INT_MAX);
}