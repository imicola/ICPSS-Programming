#include "head.h"

//创建一个 “用户类” 保存用户信息
class user_info
{
private:
    std::string user_name;
    std::string user_password;
    int _get_uuid()
    {
        // 使用user_name和user_passworld生成int类型哈希uuid，使得写入文件和查找的时候更加容易
        std::hash<std::string> hash_func;
        size_t name_hash = hash_func(user_name);
        size_t pass_hash = hash_func(user_password);
        //组合hash确保在int范围
        return static_cast<int>((name_hash ^ (pass_hash << 1)) % INT_MAX);
    }
    int user_hash_uuid = _get_uuid();
    void in_file()
    {
        // 检查文件是否存在
        // 然后存入数据
        std::ofstream file;
        std::string file_path = "user_info.txt";
        // 尝试以只读模式打开文件检查文件是否存在
        std::ifstream check_file(file_path);
        bool file_exists = check_file.good();
        check_file.close();
        // 打开文件
        file.open(file_path, std::ios::app);
        if (file.is_open()) {
            file << user_hash_uuid << " " << user_name << " " << user_password << std::endl;
            file.close();
        }
        else {
            std::cerr << "无法打开或创建文件: " << file_path << std::endl;
        }
    }

public:
    user_info(const std::string &_user_name, const std::string &_user_password)
    {
        user_name = _user_name;
        user_password = _user_password;
    }
    void call_in_file()
    {
        in_file();
    }
};

// 用户注册
void user_register_satic()
{
    __user_register_satic();
    char choice;
    choice = getch();
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
    // 使用 windows.h 确定光标位置，实现在特定位置输入文本
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
        ch = _getch();
        if (ch == '\r' || ch == '\n') {
            break;
        }
        // "\b 作为退格符，检查用户退格情况，并对输出退格，同时从字符串弹出上一个字符"
        else if (ch == '\b' && !password.empty()) {
            password.pop_back();
            std::cout << "\b \b";
        }
        else if (ch != '\b' && isprint(ch)) {
            password.push_back(ch);
            std::cout << '*';
        }
    }
    // 检查密码长度合法性
    if (password.length() < 6 || password.length() > 26) {
        COORD _pos_cout = {16, 9};
        SetConsoleCursorPosition(hConsole, _pos_cout);
        std::cout << "密码长度不符合要求！";
        fast_clear();
        user_Register();
    }
    //检查密码字符/数字合法性
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
    // 将user_info保存到类中
    user_info _user(username, password);
    // 模拟password销毁过程
    password.clear();
    username.clear();
    _user.call_in_file();
}