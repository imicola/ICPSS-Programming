#include "head.h"

void check_all()
{
    system("cls");
    // 在函数开始就清除输入缓冲区
    clearInputBuffer();
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
    _getch();
    system("cls");
    _admin_static();
}

void admin_revise()
{
    system("cls");
    // 用于存储总算力的文件
    const std::string RESOURCES_FILE = "system_resources.txt";
    const std::string GPU_TYPES_FILE = "gpu_types.txt";

    // 算力资源结构
    struct SystemResources
    {
        int total_cpu_cores = 16;
        int total_cpu_threads = 32;
        int total_gpu_count = 4;
        std::string gpu_type = "NVIDIA A100"; // 默认GPU类型
        double total_storage_gb = 1000.0;
    };

    SystemResources resources;
    bool file_exists = false;
    std::vector<std::string> gpu_types;

    // 读取GPU类型列表
    std::ifstream gpu_file(GPU_TYPES_FILE);
    if (gpu_file.is_open()) {
        std::string line;
        while (std::getline(gpu_file, line)) {
            if (!line.empty()) {
                gpu_types.push_back(line);
            }
        }
        gpu_file.close();
    }
    else {
        // 如果文件不存在，创建默认GPU类型
        gpu_types = {"NVIDIA A100", "NVIDIA V100", "AMD Radeon Pro", "Intel Arc"};
        std::ofstream create_gpu_file(GPU_TYPES_FILE);
        if (create_gpu_file.is_open()) {
            for (const auto &gpu : gpu_types) {
                create_gpu_file << gpu << std::endl;
            }
            create_gpu_file.close();
        }
    }

    // 尝试从文件读取资源配置
    std::ifstream infile(RESOURCES_FILE);
    if (infile.is_open()) {
        file_exists = true;
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            std::getline(iss, key, '=');
            std::getline(iss, value);
            if (key == "cpu_cores")
                resources.total_cpu_cores = std::stoi(value);
            else if (key == "cpu_threads")
                resources.total_cpu_threads = std::stoi(value);
            else if (key == "gpu_count")
                resources.total_gpu_count = std::stoi(value);
            else if (key == "gpu_type")
                resources.gpu_type = value;
            else if (key == "storage_gb")
                resources.total_storage_gb = std::stod(value);
        }
        infile.close();
    }

    while (true) {
        system("cls");
        std::cout << "\n\n";
        std::cout << "┌─────────────────────────────────────────────────┐\n";
        std::cout << "│               系统算力资源管理                  │\n";
        std::cout << "├─────────────────────────────────────────────────┤\n";
        std::cout << "│                                                 │\n";
        std::cout << "│  当前系统资源:                                  │\n";
        std::cout << "│                                                 │\n";
        std::cout << "│  1. CPU 核心数: " << std::left << std::setw(28) << resources.total_cpu_cores << "   │\n";
        std::cout << "│  2. CPU 线程数: " << std::left << std::setw(28) << resources.total_cpu_threads << "   │\n";
        std::cout << "│  3. GPU 数量: " << std::left << std::setw(31) << resources.total_gpu_count << "  │\n";
        std::cout << "│  4. GPU 类型: " << std::left << std::setw(31) << resources.gpu_type << "  │\n";
        std::cout << "│  5. 存储空间(GB): " << std::left << std::setw(26) << resources.total_storage_gb << "   │\n";
        std::cout << "│  6. 管理GPU类型列表                             │\n";
        std::cout << "│                                                 │\n";
        std::cout << "│  0. 保存并返回                                  │\n";
        std::cout << "│                                                 │\n";
        std::cout << "└─────────────────────────────────────────────────┘\n";

        if (!file_exists) {
            std::cout << "\n注意: 未检测到资源配置文件，当前显示为默认值。请进行配置后保存。\n";
        }

        std::cout << "\n请选择要修改的选项 (0-6): ";
        char choice = _getch();

        switch (choice) {
        case '1':
            {
                std::cout << "\n\n请输入新的CPU核心数: ";
                int cores;
                std::cin >> cores;
                if (std::cin.fail() || cores < 1) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n输入无效，请输入正整数。";
                    _getch();
                }
                else {
                    resources.total_cpu_cores = cores;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }
        case '2':
            {
                std::cout << "\n\n请输入新的CPU线程数: ";
                int threads;
                std::cin >> threads;
                if (std::cin.fail() || threads < 1) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n输入无效，请输入正整数。";
                    _getch();
                }
                else {
                    resources.total_cpu_threads = threads;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }
        case '3':
            {
                std::cout << "\n\n请输入新的GPU数量: ";
                int gpus;
                std::cin >> gpus;
                if (std::cin.fail() || gpus < 0) { // GPU可以为0
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n输入无效，请输入非负整数。";
                    _getch();
                }
                else {
                    resources.total_gpu_count = gpus;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }
        case '4':
            {
                system("cls");
                std::cout << "\n\n";
                std::cout << "┌─────────────────────────────────────────────────┐\n";
                std::cout << "│               GPU类型选择                       │\n";
                std::cout << "├─────────────────────────────────────────────────┤\n";
                std::cout << "│                                                 │\n";
                std::cout << "│  当前可用GPU类型:                               │\n";
                std::cout << "│                                                 │\n";

                // 显示所有可用GPU类型
                for (size_t i = 0; i < gpu_types.size(); i++) {
                    std::cout << "│  " << (i + 1) << ". " << std::left << std::setw(41) << gpu_types[i] << "   │\n";
                }

                std::cout << "│                                                 │\n";
                std::cout << "│  0. 返回                                        │\n";
                std::cout << "│                                                 │\n";
                std::cout << "└─────────────────────────────────────────────────┘\n";

                std::cout << "\n请选择GPU类型 (0-" << gpu_types.size() << "): ";
                int gpu_choice;
                std::cin >> gpu_choice;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n输入无效，请输入数字。";
                    _getch();
                }
                else if (gpu_choice >= 1 && gpu_choice <= static_cast<int>(gpu_types.size())) {
                    resources.gpu_type = gpu_types[gpu_choice - 1];
                    std::cout << "\nGPU类型已更新为: " << resources.gpu_type;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    _getch();
                }
                else if (gpu_choice != 0) {
                    std::cout << "\n选择无效，请重新选择。";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    _getch();
                }
                else {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }
        case '5':
            {
                std::cout << "\n\n请输入新的存储空间(GB): ";
                double storage;
                std::cin >> storage;
                if (std::cin.fail() || storage <= 0) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "\n输入无效，请输入正数。";
                    _getch();
                }
                else {
                    resources.total_storage_gb = storage;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                break;
            }
        case '6':
            {
                // GPU类型管理子菜单
                bool gpu_menu = true;
                while (gpu_menu) {
                    system("cls");
                    std::cout << "\n\n";
                    std::cout << "┌─────────────────────────────────────────────────┐\n";
                    std::cout << "│               GPU类型管理                       │\n";
                    std::cout << "├─────────────────────────────────────────────────┤\n";
                    std::cout << "│                                                 │\n";
                    std::cout << "│  可用GPU类型列表:                               │\n";
                    std::cout << "│                                                 │\n";

                    // 显示所有GPU类型
                    for (size_t i = 0; i < gpu_types.size(); i++) {
                        std::cout << "│  " << (i + 1) << ". " << std::left << std::setw(41) << gpu_types[i] << "│\n";
                    }

                    std::cout << "│                                                 │\n";
                    std::cout << "│  操作:                                          │\n";
                    std::cout << "│  A. 添加新GPU类型                               │\n";
                    std::cout << "│  D. 删除GPU类型                                 │\n";
                    std::cout << "│  E. 编辑GPU类型                                 │\n";
                    std::cout << "│  S. 保存GPU类型列表                             │\n";
                    std::cout << "│  0. 返回主菜单                                  │\n";
                    std::cout << "│                                                 │\n";
                    std::cout << "└─────────────────────────────────────────────────┘\n";

                    std::cout << "\n请选择操作: ";
                    char gpu_choice = _getch();

                    switch (toupper(gpu_choice)) {
                    case 'A':
                        {
                            std::cout << "\n\n请输入新的GPU类型名称: ";
                            std::string new_gpu;
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::getline(std::cin, new_gpu);
                            if (!new_gpu.empty()) {
                                gpu_types.push_back(new_gpu);
                                std::cout << "\nGPU类型 '" << new_gpu << "' 已添加。";
                                _getch();
                            }
                            break;
                        }
                    case 'D':
                        {
                            if (gpu_types.empty()) {
                                std::cout << "\n\nGPU类型列表为空，无法删除。";
                                _getch();
                                break;
                            }

                            std::cout << "\n\n请输入要删除的GPU类型编号 (1-" << gpu_types.size() << "): ";
                            int del_idx;
                            std::cin >> del_idx;

                            if (std::cin.fail() || del_idx < 1 || del_idx > static_cast<int>(gpu_types.size())) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "\n输入无效。";
                                _getch();
                            }
                            else {
                                std::string deleted = gpu_types[del_idx - 1];
                                gpu_types.erase(gpu_types.begin() + del_idx - 1);

                                // 如果删除的是当前选中的GPU类型，重置为第一个可用类型
                                if (resources.gpu_type == deleted && !gpu_types.empty()) {
                                    resources.gpu_type = gpu_types[0];
                                }

                                std::cout << "\nGPU类型 '" << deleted << "' 已删除。";
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                _getch();
                            }
                            break;
                        }
                    case 'E':
                        {
                            if (gpu_types.empty()) {
                                std::cout << "\n\nGPU类型列表为空，无法编辑。";
                                _getch();
                                break;
                            }

                            std::cout << "\n\n请输入要编辑的GPU类型编号 (1-" << gpu_types.size() << "): ";
                            int edit_idx;
                            std::cin >> edit_idx;

                            if (std::cin.fail() || edit_idx < 1 || edit_idx > static_cast<int>(gpu_types.size())) {
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::cout << "\n输入无效。";
                                _getch();
                            }
                            else {
                                std::cout << "\n当前GPU类型: " << gpu_types[edit_idx - 1];
                                std::cout << "\n请输入新的GPU类型名称: ";
                                std::string old_name = gpu_types[edit_idx - 1];
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                std::getline(std::cin, gpu_types[edit_idx - 1]);

                                // 如果编辑的是当前选中的GPU类型，更新选中类型
                                if (resources.gpu_type == old_name) {
                                    resources.gpu_type = gpu_types[edit_idx - 1];
                                }

                                std::cout << "\nGPU类型已更新。";
                                _getch();
                            }
                            break;
                        }
                    case 'S':
                        {
                            // 保存GPU类型列表到文件
                            std::ofstream gpu_outfile(GPU_TYPES_FILE);
                            if (gpu_outfile.is_open()) {
                                for (const auto &gpu : gpu_types) {
                                    gpu_outfile << gpu << std::endl;
                                }
                                gpu_outfile.close();
                                std::cout << "\n\nGPU类型列表已保存。";
                                _getch();
                            }
                            else {
                                std::cout << "\n\n无法保存GPU类型列表！";
                                _getch();
                            }
                            break;
                        }
                    case '0':
                        gpu_menu = false;
                        break;
                    default:
                        std::cout << "\n选择无效，请重新选择。";
                        _getch();
                        break;
                    }
                }
                break;
            }
        case '0':
            {
                // 保存到文件
                std::ofstream outfile(RESOURCES_FILE);
                if (outfile.is_open()) {
                    outfile << "cpu_cores=" << resources.total_cpu_cores << std::endl;
                    outfile << "cpu_threads=" << resources.total_cpu_threads << std::endl;
                    outfile << "gpu_count=" << resources.total_gpu_count << std::endl;
                    outfile << "gpu_type=" << resources.gpu_type << std::endl;
                    outfile << "storage_gb=" << resources.total_storage_gb << std::endl;
                    outfile.close();
                    std::cout << "\n系统资源配置已保存。";
                    _getch();
                }
                else {
                    std::cout << "\n无法保存系统资源配置文件！";
                    _getch();
                }

                // 同时确保GPU类型列表也已保存
                std::ofstream gpu_outfile(GPU_TYPES_FILE);
                if (gpu_outfile.is_open()) {
                    for (const auto &gpu : gpu_types) {
                        gpu_outfile << gpu << std::endl;
                    }
                    gpu_outfile.close();
                }

                system("cls");
                _admin_static();
                return;
            }
        default:
            std::cout << "\n选择无效，请重新选择。";
            _getch();
            break;
        }
    }
}

void _status()
{
    system("cls");
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│               系统算力使用状态                  │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";

    // 从资源文件读取系统总算力
    const std::string RESOURCES_FILE = "system_resources.txt";
    int total_cpu_cores = 0;
    int total_cpu_threads = 0;
    int total_gpu_count = 0;
    std::string gpu_type;
    double total_storage_gb = 0;

    // 读取系统总资源
    std::ifstream res_file(RESOURCES_FILE);
    if (res_file.is_open()) {
        std::string line;
        while (std::getline(res_file, line)) {
            std::istringstream iss(line);
            std::string key, value;
            std::getline(iss, key, '=');
            std::getline(iss, value);

            if (key == "cpu_cores")
                total_cpu_cores = std::stoi(value);
            else if (key == "cpu_threads")
                total_cpu_threads = std::stoi(value);
            else if (key == "gpu_count")
                total_gpu_count = std::stoi(value);
            else if (key == "gpu_type")
                gpu_type = value;
            else if (key == "storage_gb")
                total_storage_gb = std::stod(value);
        }
    }
    else {
        std::cout << "│ 无法读取系统资源配置文件                      │\n";
        std::cout << "└─────────────────────────────────────────────────┘\n";
        std::cout << "\n按任意键返回...";
        _getch();
        system("cls");
        _admin_static();
        return;
    }
    res_file.close();

    // 读取所有计划信息，计算已分配资源
    int used_cpu_cores = 0;
    int used_cpu_threads = 0;
    int used_gpu_count = 0;
    double used_storage_gb = 0.0;
    std::map<std::string, int> gpu_usage;                       // 各类型GPU使用数量
    std::map<std::string, std::vector<std::string>> user_plans; // 用户ID到计划的映射

    std::ifstream plans_file("computing_plans.txt");
    if (plans_file.is_open()) {
        std::string line;
        while (std::getline(plans_file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> tokens;
            std::string token;

            while (std::getline(iss, token, '|')) {
                tokens.push_back(token);
            }

            if (tokens.size() >= 12) {
                std::string status = tokens[4];
                // 只计算Pending和Running状态的任务占用的资源
                if (status == "Pending" || status == "Running") {
                    used_cpu_cores += std::stoi(tokens[5]);
                    used_cpu_threads += std::stoi(tokens[6]);
                    int plan_gpu_count = std::stoi(tokens[7]);
                    used_gpu_count += plan_gpu_count;
                    if (plan_gpu_count > 0) {
                        std::string plan_gpu_type = tokens[8];
                        gpu_usage[plan_gpu_type] += plan_gpu_count;
                    }
                    used_storage_gb += std::stod(tokens[9]);

                    // 记录用户的计划
                    std::string user_id = tokens[10];
                    user_plans[user_id].push_back(tokens[0]); // 存储计划ID
                }
            }
        }
        plans_file.close();
    }
    else {
        std::cout << "│ 无法读取计划文件                              │\n";
    }

    // 计算资源使用百分比
    double cpu_cores_pct = (total_cpu_cores > 0) ? (used_cpu_cores * 100.0 / total_cpu_cores) : 0;
    double cpu_threads_pct = (total_cpu_threads > 0) ? (used_cpu_threads * 100.0 / total_cpu_threads) : 0;
    double gpu_count_pct = (total_gpu_count > 0) ? (used_gpu_count * 100.0 / total_gpu_count) : 0;
    double storage_pct = (total_storage_gb > 0) ? (used_storage_gb * 100.0 / total_storage_gb) : 0;

    // 显示系统资源使用情况
    std::cout << "│ 系统总资源:                                     │\n";
    std::cout << "│ - CPU核心: " << std::left << std::setw(7) << total_cpu_cores << "  线程: " << std::left
              << std::setw(7) << total_cpu_threads << "  GPU数量: " << std::left << std::setw(4) << total_gpu_count
              << "│\n";
    std::cout << "│ - 默认GPU类型: " << std::left << std::setw(29) << gpu_type << "    │\n";
    std::cout << "│ - 存储空间: " << std::left << std::setw(33) << total_storage_gb << " GB│\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";

    // 显示资源使用进度条
    std::cout << "│ 资源使用情况:                                   │\n";

    // CPU核心使用进度条
    std::cout << "│ CPU核心: [";
    int bar_length = 20;
    int filled = static_cast<int>(cpu_cores_pct / 5);
    for (int i = 0; i < bar_length; i++) {
        if (i < filled)
            std::cout << "■";
        else
            std::cout << "□";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << cpu_cores_pct << "%          │\n";

    // CPU线程使用进度条
    std::cout << "│ CPU线程: [";
    filled = static_cast<int>(cpu_threads_pct / 5);
    for (int i = 0; i < bar_length; i++) {
        if (i < filled)
            std::cout << "■";
        else
            std::cout << "□";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << cpu_threads_pct << "%            │\n";

    // GPU使用进度条
    std::cout << "│ GPU数量: [";
    filled = static_cast<int>(gpu_count_pct / 5);
    for (int i = 0; i < bar_length; i++) {
        if (i < filled)
            std::cout << "■";
        else
            std::cout << "□";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << gpu_count_pct << "%          │\n";

    // 存储空间使用进度条
    std::cout << "│ 存储空间:[";
    filled = static_cast<int>(storage_pct / 5);
    for (int i = 0; i < bar_length; i++) {
        if (i < filled)
            std::cout << "■";
        else
            std::cout << "□";
    }
    std::cout << "] " << std::fixed << std::setprecision(1) << storage_pct << "%           │\n";

    // 显示各类型GPU使用情况
    if (!gpu_usage.empty()) {
        std::cout << "├─────────────────────────────────────────────────┤\n";
        std::cout << "│ GPU使用详情:                                    │\n";
        for (const auto &gpu_pair : gpu_usage) {
            std::string display = " - " + gpu_pair.first + ": " + std::to_string(gpu_pair.second) + " 个";
            std::cout << "│ " << std::left << std::setw(45) << display << "    │\n";
        }
    }

    // 显示用户资源占用情况
    if (!user_plans.empty()) {
        std::cout << "├─────────────────────────────────────────────────┤\n";
        std::cout << "│ 用户资源占用情况:                               │\n";
        std::cout << "│ 用户ID        计划数   CPU核心   CPU线程   存储 │\n";

        for (const auto &user_pair : user_plans) {
            std::string user_id = user_pair.first;
            int plan_count = user_pair.second.size();

            // 计算该用户占用的资源
            int user_cpu_cores = 0;
            int user_cpu_threads = 0;
            double user_storage = 0.0;

            for (const auto &plan_id : user_pair.second) {
                try {
                    ComputingPlan plan = ComputingPlan::loadFromFile(plan_id);
                    user_cpu_cores += plan.getCpuCores();
                    user_cpu_threads += plan.getCpuThreads();
                    user_storage += plan.getStorageGb();
                } catch (const std::exception &) {
                    // 如果加载失败，跳过该计划
                    continue;
                }
            }

            std::cout << "│ " << std::left << std::setw(13) << user_id << " " << std::setw(8) << plan_count << " "
                      << std::setw(9) << user_cpu_cores << " " << std::setw(8) << user_cpu_threads << " "
                      << std::setw(6) << user_storage << "│\n";
        }
    }

    std::cout << "└─────────────────────────────────────────────────┘\n";
    std::cout << "\n按任意键返回...";
    _getch();
    system("cls");
    _admin_static();
}
