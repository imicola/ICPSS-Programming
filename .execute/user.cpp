#include "head.h"

void _plan_edit_interface();
void _edit_plan();
void _create_plan();
void _delete_plan();
void _interface();
void _plan_check();
void power_situation();

// interface 居然是关键字(震惊)
void _interface()
{
    user__interface();
    char _ch;
    _ch = getch();
    // system("cls");
    if (_ch == '1') {
        _plan_check();
    }
    else if (_ch == '2') {
        _plan_edit_interface();
    }
    else if (_ch == '3') {
        power_situation();
    }
    else if (_ch == '0') {
        // 用户登出
        current_user.set_LoggedIn(false);
        // 提示用户已登出
        std::cout << "您已成功登出系统。" << std::endl;
        std::cout << "按任意键返回主菜单...";
        fast_clear();
        head();
    }
    else {
        std::cout << "无效选择，请重试。" << std::endl;
        _interface();
    }
}

// 计划编辑
void _plan_edit_interface()
{
    system("cls");
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
    std::string name, description, user_id, gpu_type;
    int priority, cpu_cores, cpu_threads, gpu_count;
    double storage_gb;
    user_id = current_user.get_User_name(); // 获取当前用户ID
    std::cout << "\n──────── 创建算力使用计划 ────────\n\n";

    std::cout << "计划名称: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "计划描述: ";
    std::getline(std::cin, description);

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
    fast_clear();
    _interface();
}

// 编辑算力使用计划
void _edit_plan()
{
    std::string plan_id;
    std::cout << "\n──────── 编辑算力使用计划 ────────\n\n";

    std::cout << "请输入要编辑的计划ID: ";
    std::cin.ignore();
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
    fast_clear();
    _interface();
}

// 删除算力使用计划
void _delete_plan()
{
    std::string plan_id;
    std::cout << "\n──────── 删除算力使用计划 ────────\n\n";

    std::cout << "请输入要删除的计划ID: ";
    std::cin.ignore();
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
    fast_clear();
    _interface();
}

void _plan_check()
{
    system("cls");
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                 我的算力计划                    │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";

    // 获取用户ID（使用当前登录用户名）
    std::string user_id = current_user.get_User_name();

    try {
        // 加载用户的所有计划
        std::vector<ComputingPlan> user_plans = ComputingPlan::loadUserPlans(user_id, "computing_plans.txt");
        if (user_plans.empty()) {
            std::cout << "│                                                 │\n";
            std::cout << "│            您还没有创建任何算力计划             │\n";
            std::cout << "│                                                 │\n";
            std::cout << "└─────────────────────────────────────────────────┘\n";
        }
        else {
            std::cout << "│                                                 │\n";
            std::cout << "│  计划ID                状态        优先级       │\n";
            std::cout << "│  ────────────────────────────────────────────   │\n";

            for (const auto &plan : user_plans) {
                std::cout << "│  " << std::left << std::setw(20) << plan.getPlanId() << std::left << std::setw(12)
                          << plan.getStatus() << std::left << std::setw(10) << plan.getPriority() << "     │\n";
            }

            std::cout << "│                                                 │\n";
            std::cout << "└─────────────────────────────────────────────────┘\n";

            // 查看详情选项
            std::cout << "\n是否查看计划详情? (y/n): ";
            char choice = _getch();

            if (choice == 'y' || choice == 'Y') {
                std::string plan_id;
                std::cout << "\n\n请输入要查看的计划ID: ";
                std::cin.ignore();
                std::getline(std::cin, plan_id);

                // 在用户计划中查找指定ID
                bool found = false;
                for (const auto &plan : user_plans) {
                    if (plan.getPlanId() == plan_id) {
                        plan.displayPlanInfo();
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    std::cout << "\n未找到ID为 " << plan_id << " 的计划。\n";
                }
            }
        }

    } catch (const std::exception &e) {
        std::cout << "│                                                 │\n";
        std::cout << "│           加载计划时出错: " << std::left << std::setw(19) << e.what() << "│\n";
        std::cout << "│                                                 │\n";
        std::cout << "└─────────────────────────────────────────────────┘\n";
    }

    std::cout << "\n按任意键继续...";
    fast_clear();
    _interface();
}

void power_situation()
{
    system("cls");
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│               算力使用总体情况                  │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";

    // 获取当前用户ID
    std::string user_id = current_user.get_User_name();
    try {
        // 加载用户的所有计划
        std::vector<ComputingPlan> user_plans = ComputingPlan::loadUserPlans(user_id);

        if (user_plans.empty()) {
            std::cout << "│                                                 │\n";
            std::cout << "│         当前用户没有任何算力使用计划            │\n";
            std::cout << "│                                                 │\n";
        }
        else {
            // 计算总体资源使用情况
            int total_plans = user_plans.size();
            int pending_plans = 0;
            int running_plans = 0;
            int completed_plans = 0;
            int failed_plans = 0;

            int total_cpu_cores = 0;
            int total_gpu_count = 0;
            double total_storage = 0.0;

            for (const auto &plan : user_plans) {
                // 统计状态
                std::string status = plan.getStatus();
                if (status == "Pending")
                    pending_plans++;
                else if (status == "Running")
                    running_plans++;
                else if (status == "Completed")
                    completed_plans++;
                else if (status == "Failed")
                    failed_plans++;

                // 统计资源
                total_cpu_cores += plan.getCpuCores();
                total_gpu_count += plan.getGpuCount();
                total_storage += plan.getStorageGb();
            }

            // 显示统计信息
            std::cout << "│  总计划数量: " << std::left << std::setw(34) << total_plans << " │\n";
            std::cout << "│                                                 │\n";
            std::cout << "│  状态分布:                                      │\n";
            std::cout << "│    等待中: " << std::left << std::setw(35) << pending_plans << "  │\n";
            std::cout << "│    运行中: " << std::left << std::setw(35) << running_plans << "  │\n";
            std::cout << "│    已完成: " << std::left << std::setw(35) << completed_plans << "  │\n";
            std::cout << "│    失败: " << std::left << std::setw(37) << failed_plans << "  │\n";
            std::cout << "│                                                 │\n";
            std::cout << "│  资源使用总计:                                  │\n";
            std::cout << "│    CPU核心数: " << std::left << std::setw(33) << total_cpu_cores << " │\n";
            std::cout << "│    GPU数量: " << std::left << std::setw(35) << total_gpu_count << " │\n";
            std::cout << "│    存储空间(GB): " << std::left << std::setw(30) << total_storage << " │\n";
        }

        std::cout << "│                                                 │\n";
        std::cout << "└─────────────────────────────────────────────────┘\n";

    } catch (const std::exception &e) {
        std::cout << "│                                                 │\n";
        std::cout << "│  获取算力使用情况时出错: " << std::left << std::setw(23) << e.what() << "│\n";
        std::cout << "│                                                 │\n";
        std::cout << "└─────────────────────────────────────────────────┘\n";
    }

    std::cout << "\n按任意键继续...";
    fast_clear();
    _interface();
}