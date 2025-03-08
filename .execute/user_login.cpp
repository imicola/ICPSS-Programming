#include "head.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::string username;
std::string password;

// 定义全局用户对象
user_info current_user;

void login();

void user_login()
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
    SetConsoleCursorPosition(hConsole, posUsername);
    std::cin >> username;
    COORD posPassword = {14, 7};
    SetConsoleCursorPosition(hConsole, posPassword);
    char ch;
    password = "";
    while (true) {
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        }
        else if (ch == '\b' && !password.empty()) {
            password.pop_back();
            std::cout << "\b \b";
        }
        else if (ch != '\b' && isprint(ch)) {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    COORD __pos_cout = {3, 8};
    SetConsoleCursorPosition(hConsole, __pos_cout);
    login();
}

void login()
{
    //登录逻辑验证
    int login_uuid = get_uuid(username, password);
    int login_success = 0;
    std::string file_path = "user_info.txt";
    // 检查文件是否存在
    std::ifstream check_file(file_path);
    bool file_exists = check_file.good();
    check_file.close();
    if (file_exists) {
        std::ifstream read_file(file_path);
        std::string file_user_name, file_password;
        int file_uuid;
        while (read_file >> file_uuid >> file_user_name >> file_password) {
            if (file_uuid == login_uuid && file_password == password) {
                // 登录成功，创建用户对象并设置登录状态
                current_user = user_info(username, password);
                current_user.setLoggedIn(true);
                login_success = 1;
                break;
            }
            else if (file_user_name == username && file_password != password) {
                std::cout << "登录失败，请检查密码";
                login_success = -1;
                username.clear();
                password.clear();
                fast_clear();
                user_login();
                break;
            }
        }
        read_file.close();
        // 如果循环结束后login_success仍为0且未找到匹配用户名
        if (login_success == 0) {
            std::cout << "未检测到用户，请检查是否注册";
            username.clear();
            password.clear();
            COORD _pos_cout_2 = {0, 10};
            SetConsoleCursorPosition(hConsole, _pos_cout_2);
            std::cout << "按 1 重新登录" << "\n";
            std::cout << "按 2 返回注册" << "\n";
            std::cout << "按 3 返回主菜单" << "\n";
            std::cout << "按 0 退出系统" << "\n";
            char choice;
            choice = getch();
            if (choice == '1') {
                system("cls");
                user_login();
            }
            else if (choice == '2') {
                system("cls");
                user_register_satic();
            }
            else if (choice == '3') {
                system("cls");
                head();
            }
            else if (choice == '0') {
                system("cls");
                exit(0);
            }
        }
    }
    else {
        std::cerr << "无法打开文件: " << file_path << " 请检查是否注册";
        fast_clear();
        head();
    }
    std::cout << "登录成功！即将前往用户界面";
    fast_clear();
    _interface();
}
