#include "head.h"

HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const std::string ad_username = "imicola";
const std::string ad_password = "123qweasdzxc";
std::string _username;
std::string _password;

void admin_login()
{
    //从注册那里改的代码
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                 用户登录                        │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  请输入用户名: ";
    std::cout << "                                 │\n";
    std::cout << "│  请输入密码: ";
    std::cout << "                                   │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    COORD posUsername = {16, 6};
    SetConsoleCursorPosition(_hConsole, posUsername);
    std::cin >> _username;
    COORD posPassword = {14, 7};
    SetConsoleCursorPosition(_hConsole, posPassword);
    char ch;
    _password = "";
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        }
        else if (ch == '\b' && !_password.empty()) {
            _password.pop_back();
            std::cout << "\b \b";
        }
        else if (ch != '\b' && isprint(ch)) {
            _password.push_back(ch);
            std::cout << '*';
        }
    }
    COORD __pos_cout = {3, 8};
    SetConsoleCursorPosition(_hConsole, __pos_cout);
    if (_username == ad_username && _password == ad_password) {
        std::cout << "登录成功！欢迎管理员 " << _username << std::endl;
        fast_clear();
        _admin_static();
    }
    else {
        std::cout << "用户名或密码错误，登录失败！" << std::endl;
        fast_clear();
        head();
    }
}

void _admin_static()
{
    administrator_interface();
    char ch;
    ch = _getch();
    switch (ch) {
    case '1':
        std::cin.clear();
        std::cin.sync();
        _status();
        break;
    case '2':
        std::cin.clear();
        std::cin.sync();
        check_all();
        break;
    case '3':
        std::cin.clear();
        std::cin.sync();
        admin_revise();
        break;
    default:
        system("cls");
        head();
        break;
    }
}

