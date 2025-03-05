#include "head.h"

// 用户注册
//
void user_register_satic()
{
    __user_register_satic();
    char choice;
    choice = get_ch();
    if (choice == 'y' || choice == 'Y') {
        system("cls");
        user_Register();
    }
    else {
        system("cls");
        head();
    }
}

void user_Register()
{
    std::string username;
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                 用户注册                        │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  请输入用户名: ";
    std::cout << "                                 │\n";
    std::cout << "│  请输入密码: ";
    std::cout << "                                   │\n";
    std::cout << "│  再次输入密码:                                  │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  密码由数字和字母构成，不少于6位，不得多余26位  │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    // windows专有功能
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD posUsername = {16, 6};
    SetConsoleCursorPosition(hConsole, posUsername);
    std::cin >> username;
    // 定位到密码输入位置
    COORD posPassword = {14, 7};
    SetConsoleCursorPosition(hConsole, posPassword);
    std::string password;
    char ch;
    password = "";
    while (true) {
        ch = _getch();                  //获取字符
        if (ch == '\r' || ch == '\n') { // 输入key
            break;
        }
        else if (ch == '\b' && !password.empty()) { // 检查
            password.pop_back();
            std::cout << "\b \b";
        }
        else if (ch != '\b' && isprint(ch)) {
            password.push_back(ch);
            std::cout << '*'; // 显示*
        }
    }
    // 检查密码合法性
    if (password.length() < 6 || password.length() > 26) {
        COORD _pos_cout = {16, 9};
        SetConsoleCursorPosition(hConsole, _pos_cout);
        std::cout << "密码长度不符合要求！";
        fast_clear();
        user_Register();
    }
    bool has_digit = false;
    bool has_letter = false;
    for (char c : password) {
        if (isdigit(c)) has_digit = true;
        if (isalpha(c)) has_letter = true;
    }
    if (!has_digit || !has_letter) {
        COORD _pos_cout = {16, 9};
        SetConsoleCursorPosition(hConsole, _pos_cout);
        std::cout << "密码必须包含数字和字母！";
        fast_clear();
        user_Register();
    }
    // 再次输入密码
    COORD pos_rePassword = {16, 8};
    SetConsoleCursorPosition(hConsole, pos_rePassword);
    std::string repassword;
    ch = 0;
    repassword = "";
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        }
        else if (ch == '\b' && !repassword.empty()) {
            repassword.pop_back();
            std::cout << "\b \b";
        }
        else if (ch != '\b' && isprint(ch)) {
            repassword.push_back(ch);
            std::cout << '*';
        }
    }
    // 检查两次输入的密码是否一致
    if (password != repassword) {
        COORD _pos_cout = {16, 9};
        SetConsoleCursorPosition(hConsole, _pos_cout);
        std::cout << "两次输入的密码不一致！";
        fast_clear();
        user_Register();
    }
    // 注册成功
    COORD _pos_success = {16, 9};
    SetConsoleCursorPosition(hConsole, _pos_success);
    std::cout << "注册成功！";
    
}