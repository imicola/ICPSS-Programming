#include "head.h"

HANDLE _hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
const std::string ad_username = "imicola";
const std::string ad_password = "123qweasdzxc";
std::string _username;
std::string _password;

void _admin_static();
void check_all();

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

        break;
    case '2':
        check_all();
        break;
    case '3':

        break;
    default:
        system("cls");
        head();
        break;
    }
}

void check_all()
{
    system("cls");
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│               管理所有算力计划                  │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    try {
        // 读取所有计划
        std::ifstream infile("computing_plans.txt");
        if (!infile.is_open()) {
            throw std::runtime_error("无法打开计划文件");
        }

        std::vector<ComputingPlan> all_plans;
        std::string line;

        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string plan_id;
            std::getline(iss, plan_id, '|');
            try {
                ComputingPlan plan = ComputingPlan::loadFromFile(plan_id);
                all_plans.push_back(plan);
            } catch (const std::exception &e) {
                // 跳过加载失败的计划
                continue;
            }
        }

        infile.close();

        if (all_plans.empty()) {
            std::cout << "│                                                 │\n";
            std::cout << "│            系统中没有任何算力计划               │\n";
            std::cout << "│                                                 │\n";
            std::cout << "└─────────────────────────────────────────────────┘\n";
        }
        else {
            std::cout << "│                                                 │\n";
            std::cout << "│  计划ID              用户        状态    优先级 │\n";
            std::cout << "│  ────────────────────────────────────────────   │\n";

            for (size_t i = 0; i < all_plans.size(); i++) {
                std::cout << "│  " << std::left << std::setw(18) << all_plans[i].getPlanId() << std::left
                          << std::setw(12) << all_plans[i].getUserId() << std::left << std::setw(10)
                          << all_plans[i].getStatus() << std::left << std::setw(7) << all_plans[i].getPriority()
                          << "│\n";
            }

            std::cout << "│                                                 │\n";
            std::cout << "└─────────────────────────────────────────────────┘\n";

            // 选择操作
            std::cout << "\n请选择操作:\n";
            std::cout << "1. 查看计划详情\n";
            std::cout << "2. 修改计划状态\n";
            std::cout << "3. 修改计划优先级\n";
            std::cout << "4. 删除计划\n";
            std::cout << "0. 返回上级菜单\n";

            char choice;
            std::cout << "\n请选择 (0-4): ";
            choice = _getch();

            if (choice == '1') {
                std::string plan_id;
                std::cout << "\n\n请输入要查看的计划ID: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, plan_id);

                try {
                    ComputingPlan plan = ComputingPlan::loadFromFile(plan_id);
                    plan.displayPlanInfo();
                } catch (const std::exception &e) {
                    std::cout << "\n错误: " << e.what() << std::endl;
                }
            }
            else if (choice == '2' || choice == '3') {
                std::string plan_id;
                std::cout << "\n\n请输入要修改的计划ID: ";
                std::cin.ignore();
                std::getline(std::cin, plan_id);

                try {
                    ComputingPlan plan = ComputingPlan::loadFromFile(plan_id);

                    if (choice == '2') {
                        std::cout << "\n当前状态: " << plan.getStatus();
                        std::cout << "\n新状态 (Pending/Running/Completed/Failed): ";
                        std::string new_status;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::getline(std::cin, new_status);

                        if (plan.updateStatus(new_status)) {
                            std::cout << "\n计划状态更新成功！" << std::endl;
                        }
                        else {
                            std::cout << "\n计划状态更新失败！" << std::endl;
                        }
                    }
                    else { // choice == '3'
                        std::cout << "\n当前优先级: " << plan.getPriority();
                        std::cout << "\n新优先级 (1-10): ";
                        int new_priority;
                        std::cin >> new_priority;
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        plan.setPriority(new_priority);
                        if (plan.updateStatus(plan.getStatus())) { // 使用updateStatus来保存
                            std::cout << "\n计划优先级更新成功！" << std::endl;
                        }
                        else {
                            std::cout << "\n计划优先级更新失败！" << std::endl;
                        }
                    }
                } catch (const std::exception &e) {
                    std::cout << "\n错误: " << e.what() << std::endl;
                }
            }
            else if (choice == '4') {
                std::string plan_id;
                std::cout << "\n\n请输入要删除的计划ID: ";
                std::cin.ignore();
                std::getline(std::cin, plan_id);

                try {
                    ComputingPlan plan = ComputingPlan::loadFromFile(plan_id);
                    plan.displayPlanInfo();

                    std::cout << "\n确定要删除此计划吗? (y/n): ";
                    char confirm = _getch();

                    if (confirm == 'y' || confirm == 'Y') {
                        // 读取所有计划
                        std::ifstream infile("computing_plans.txt");
                        std::vector<std::string> all_lines;
                        std::string line;

                        while (std::getline(infile, line)) {
                            std::istringstream iss(line);
                            std::string id;
                            std::getline(iss, id, '|');

                            if (id != plan_id) {
                                all_lines.push_back(line);
                            }
                        }

                        infile.close();

                        // 写回文件
                        std::ofstream outfile("computing_plans.txt", std::ios::trunc);
                        for (const auto &line : all_lines) {
                            outfile << line << std::endl;
                        }
                        outfile.close();

                        std::cout << "\n计划已成功删除！" << std::endl;
                    }
                    else {
                        std::cout << "\n已取消删除。" << std::endl;
                    }
                } catch (const std::exception &e) {
                    std::cout << "\n错误: " << e.what() << std::endl;
                }
            }
        }
    } catch (const std::exception &e) {
        std::cout << "│                                                 │\n";
        std::cout << "│  查看计划时出错: " << std::left << std::setw(29) << e.what() << "│\n";
        std::cout << "│                                                 │\n";
        std::cout << "└─────────────────────────────────────────────────┘\n";
    }

    std::cout << "\n按任意键继续...";
    fast_clear();
    _admin_static();
}