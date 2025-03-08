#include "head.h"

void _plan_edit_interface();
void _edit_plan();
void _create_plan();
void _delete_plan();
void _interface();

// interface 居然是关键字(震惊)
void _interface()
{
    user__interface();
    char _ch;
    _ch = getch();
    system("cls");
    if (_ch == '1') {
        // _plan_check();
    }
    else if (_ch == '2') {
        _plan_edit_interface();
    }
}

// 计划编辑
void _plan_edit_interface()
{
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                  算力计划编辑                   │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  1. 创建算力使用计划                            │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  2. 编辑算力使用计划                            │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  2. 删除算力使用计划                            │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    std::cout << "请选择操作 (1-3): ";
    char choice = _getch();
    system("cls");

    switch (choice) {
    case '1':
        _create_plan();
        break;
    case '2':
        _edit_plan();
        break;
    case '3':
        _delete_plan();
        break;
    default:
        std::cout << "无效选择，请重试。" << std::endl;
        break;
    }
}

// 创建算力使用计划
void _create_plan()
{
    std::cin.ignore();
    std::string name, description, user_id, gpu_type;
    int priority, cpu_cores, cpu_threads, gpu_count;
    double storage_gb;

    std::cout << "\n──────── 创建算力使用计划 ────────\n\n";

    std::cout << "计划名称: ";
    std::getline(std::cin, name);

    std::cout << "计划描述: ";
    std::getline(std::cin, description);

    std::cout << "用户ID: ";
    std::getline(std::cin, user_id);

    std::cout << "优先级 (1-10): ";
    std::cin >> priority;

    std::cout << "CPU核心数: ";
    std::cin >> cpu_cores;

    std::cout << "CPU线程数: ";
    std::cin >> cpu_threads;

    std::cout << "GPU数量: ";
    std::cin >> gpu_count;

    if (gpu_count > 0) {
        std::cin.ignore(); // 清除输入缓冲区
        std::cout << "GPU类型: ";
        std::getline(std::cin, gpu_type);
    }

    std::cout << "存储空间 (GB): ";
    std::cin >> storage_gb;

    // 创建计算计划对象
    ComputingPlan plan(name, user_id, cpu_cores, cpu_threads, gpu_count, gpu_type, storage_gb);
    plan.setDescription(description);
    plan.setPriority(priority);

    // 保存计划到文件
    if (plan.saveToFile()) {
        std::cout << "\n 计划创建成功！计划ID: " << plan.getPlanId() << std::endl;
    }
    else {
        std::cout << "\n 计划创建失败！" << std::endl;
    }

    std::cout << "\n按任意键继续...";
    _getch();
}

// 编辑算力使用计划
void _edit_plan()
{
    std::cin.ignore();
    std::string plan_id;
    std::cout << "\n──────── 编辑算力使用计划 ────────\n\n";

    std::cout << "请输入要编辑的计划ID: ";
    std::getline(std::cin, plan_id);

    try {
        // 从文件加载计划
        ComputingPlan plan = ComputingPlan::loadFromFile(plan_id);

        // 显示当前计划信息
        plan.displayPlanInfo();

        // 编辑菜单
        std::cout << "\n请选择要编辑的部分:\n";
        std::cout << "1. 计划名称\n";
        std::cout << "2. 计划描述\n";
        std::cout << "3. 优先级\n";
        std::cout << "4. 状态\n";
        std::cout << "5. 预计运行时间\n";
        std::cout << "0. 保存并退出\n";

        char choice;
        bool modified = false;

        do {
            std::cout << "\n请选择 (0-5): ";
            choice = _getch();

            std::string new_value;
            int new_int_value;

            switch (choice) {
            case '1':
                std::cout << "\n新计划名称: ";
                std::getline(std::cin, new_value);
                plan.setPlanName(new_value);
                modified = true;
                break;
            case '2':
                std::cout << "\n新计划描述: ";
                std::getline(std::cin, new_value);
                plan.setDescription(new_value);
                modified = true;
                break;
            case '3':
                std::cout << "\n新优先级 (1-10): ";
                std::cin >> new_int_value;
                plan.setPriority(new_int_value);
                std::cin.ignore();
                modified = true;
                break;
            case '4':
                std::cout << "\n新状态 (Pending/Running/Completed/Failed): ";
                std::getline(std::cin, new_value);
                plan.setStatus(new_value);
                modified = true;
                break;
            case '5':
                std::cout << "\n预计运行时间(秒): ";
                std::cin >> new_int_value;
                plan.setEstimatedDuration(new_int_value);
                std::cin.ignore();
                modified = true;
                break;
            case '0':
                break;
            default:
                std::cout << "无效选择，请重试。";
            }
        } while (choice != '0');

        // 保存更改
        if (modified && plan.updateStatus(plan.getStatus())) {
            std::cout << "\n 计划已成功更新！" << std::endl;
        }
        else if (modified) {
            std::cout << "\n 计划更新失败！" << std::endl;
        }

    } catch (const std::runtime_error &e) {
        std::cout << "\n错误: " << e.what() << std::endl;
    }

    std::cout << "\n按任意键继续...";
    _getch();
}

// 删除算力使用计划
void _delete_plan()
{
    std::string plan_id;
    std::cout << "\n──────── 删除算力使用计划 ────────\n\n";

    std::cout << "请输入要删除的计划ID: ";
    std::getline(std::cin, plan_id);

    try {
        // 尝试加载计划以验证其存在
        ComputingPlan plan = ComputingPlan::loadFromFile(plan_id);

        // 显示计划信息
        plan.displayPlanInfo();

        // 确认删除
        std::cout << "\n确定要删除此计划吗? (y/n): ";
        char confirm = _getch();

        if (confirm == 'y' || confirm == 'Y') {
            // 读取所有计划
            std::ifstream infile("computing_plans.txt");
            if (!infile.is_open()) {
                std::cout << "\n 无法打开计划文件！" << std::endl;
                return;
            }

            std::vector<std::string> all_plans;
            std::string line;
            bool found = false;

            while (std::getline(infile, line)) {
                std::istringstream iss(line);
                std::string id;
                std::getline(iss, id, '|');

                if (id != plan_id) {
                    all_plans.push_back(line);
                }
                else {
                    found = true;
                }
            }

            infile.close();

            if (!found) {
                std::cout << "\n 未找到指定ID的计划！" << std::endl;
                return;
            }

            // 写回文件
            std::ofstream outfile("computing_plans.txt", std::ios::trunc);
            if (!outfile.is_open()) {
                std::cout << "\n 无法写入计划文件！" << std::endl;
                return;
            }

            for (const auto &plan_line : all_plans) {
                outfile << plan_line << std::endl;
            }

            outfile.close();
            std::cout << "\n 计划已成功删除！" << std::endl;
        }
        else {
            std::cout << "\n已取消删除。" << std::endl;
        }

    } catch (const std::runtime_error &e) {
        std::cout << "\n错误: " << e.what() << std::endl;
    }

    std::cout << "\n按任意键继续...";
    _getch();
}
