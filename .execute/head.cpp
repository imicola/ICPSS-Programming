#include "head.h"

void head()
{
    std::cout << R"(  
    ██╗ ██████╗██████╗ ███████╗███████╗
    ██║██╔════╝██╔══██╗██╔════╝██╔════╝
    ██║██║     ██████╔╝███████╗███████╗
    ██║██║     ██╔═══╝ ╚════██║╚════██║
    ██║╚██████╗██║     ███████║███████║
    ╚═╝ ╚═════╝╚═╝     ╚══════╝╚══════╝
    )" << "\n";
    std::cout << R"(Intelligent Computing Power Scheduling System)" << "\n";
    std::cout << "智能算力调度系统" << "\n";
    std::cout << "Version: 1.0.0" << "\n";
    std::cout << "Author: imicola" << "\n" << "\n";
    // 显示边框
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│             欢迎使用智能算力调度系统            │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  [1] 用户登录                                   │\n";
    std::cout << "│  [2] 新用户注册                                 │\n";
    std::cout << "│  [3] 系统说明                                   │\n";
    std::cout << "│  [4] 查看算力资源                               │\n";
    std::cout << "│  [5] 调度策略介绍                               │\n";
    std::cout << "│  [6] 系统状态监控                               │\n";
    std::cout << "│  [7] 算力任务提交                               │\n";
    std::cout << "│  [8] 历史记录查询                               │\n";
    std::cout << "│  [0] 退出系统                                   │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n\n";
    std::cout << "请输入对应数字选择功能: ";
    char _head_get_num;
    _head_get_num = getch();
    system("cls");
    // 修改head()函数中的部分代码
    if (_head_get_num == '3')
        displaySystemInfo();
    else if (_head_get_num == '4')
        displayResourceInfo();
    else if (_head_get_num == '5')
        SchedulingStrategies();
    else if (_head_get_num == '0')
        exit(0);
    else if (_head_get_num == '2')
        user_register_satic();
    else if (_head_get_num == '1')
        user_login();
}