#include "head.h"

// 生成唯一计划ID
std::string ComputingPlan::generatePlanId() const {
    std::hash<std::string> hasher;
    std::string base = plan_name + user_id + std::to_string(create_time);
    size_t hash_val = hasher(base);
    return "PLAN-" + std::to_string(hash_val).substr(0, 8);
}

// 默认构造函数
ComputingPlan::ComputingPlan() : 
    priority(1), cpu_cores(1), cpu_threads(2), gpu_count(0), 
    storage_gb(1.0), create_time(std::time(nullptr)), estimated_duration(0) {
    status = "Pending";
}

// 参数化构造函数
ComputingPlan::ComputingPlan(const std::string& name, const std::string& uid, 
             int cpu_c, int cpu_t, int gpu_c, const std::string& gpu_t, 
             double storage) : 
    plan_name(name), user_id(uid), priority(1),
    cpu_cores(cpu_c), cpu_threads(cpu_t),
    gpu_count(gpu_c), gpu_type(gpu_t), 
    storage_gb(storage), create_time(std::time(nullptr)), estimated_duration(0) {
    status = "Pending";
    plan_id = generatePlanId();
}

// 设置函数
void ComputingPlan::setPlanName(const std::string& name) { plan_name = name; }
void ComputingPlan::setDescription(const std::string& desc) { description = desc; }
void ComputingPlan::setPriority(int p) { priority = (p > 0 && p <= 10) ? p : 1; }
void ComputingPlan::setStatus(const std::string& stat) { status = stat; }
void ComputingPlan::setUserId(const std::string& uid) { user_id = uid; }
void ComputingPlan::setEstimatedDuration(int seconds) { estimated_duration = seconds; }

// 获取函数
std::string ComputingPlan::getPlanName() const { return plan_name; }
std::string ComputingPlan::getPlanId() const { return plan_id; }
std::string ComputingPlan::getDescription() const { return description; }
int ComputingPlan::getPriority() const { return priority; }
std::string ComputingPlan::getStatus() const { return status; }
int ComputingPlan::getCpuCores() const { return cpu_cores; }
int ComputingPlan::getCpuThreads() const { return cpu_threads; }
int ComputingPlan::getGpuCount() const { return gpu_count; }
std::string ComputingPlan::getGpuType() const { return gpu_type; }
double ComputingPlan::getStorageGb() const { return storage_gb; }
std::string ComputingPlan::getUserId() const { return user_id; }
std::time_t ComputingPlan::getCreateTime() const { return create_time; }
std::time_t ComputingPlan::getEstimatedDuration() const { return estimated_duration; }

// 保存计划到文件
bool ComputingPlan::saveToFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::app | std::ios::binary); // 添加二进制模式
    if (!file.is_open()) {
        return false;
    }
    
    file << plan_id << "|"
         << plan_name << "|"
         << description << "|"
         << priority << "|"
         << status << "|"
         << cpu_cores << "|"
         << cpu_threads << "|" 
         << gpu_count << "|"
         << gpu_type << "|"
         << storage_gb << "|"
         << user_id << "|"
         << create_time << "|"
         << estimated_duration << std::endl;
    
    file.close();
    return true;
}

// 从文件加载特定计划
ComputingPlan ComputingPlan::loadFromFile(const std::string& plan_id, const std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // 使用二进制模式
    if (!file.is_open()) {
        throw std::runtime_error("无法打开计划文件");
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id;
        std::getline(iss, id, '|');
        
        if (id == plan_id) {
            ComputingPlan plan;
            plan.plan_id = id;
            
            std::getline(iss, plan.plan_name, '|');
            std::getline(iss, plan.description, '|');
            
            std::string temp;
            std::getline(iss, temp, '|');
            plan.priority = std::stoi(temp);
            
            std::getline(iss, plan.status, '|');
            
            std::getline(iss, temp, '|');
            plan.cpu_cores = std::stoi(temp);
            
            std::getline(iss, temp, '|');
            plan.cpu_threads = std::stoi(temp);
            
            std::getline(iss, temp, '|');
            plan.gpu_count = std::stoi(temp);
            
            std::getline(iss, plan.gpu_type, '|');
            
            std::getline(iss, temp, '|');
            plan.storage_gb = std::stod(temp);
            
            std::getline(iss, plan.user_id, '|');
            
            std::getline(iss, temp, '|');
            plan.create_time = std::stoll(temp);
            
            std::getline(iss, temp, '|');
            plan.estimated_duration = std::stoll(temp);
            
            file.close();
            return plan;
        }
    }
    
    file.close();
    throw std::runtime_error("未找到指定ID的计划");
}

// 加载用户的所有计划
std::vector<ComputingPlan> ComputingPlan::loadUserPlans(const std::string& user_id, const std::string& filename) {
    std::vector<ComputingPlan> plans;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return plans;  // 返回空向量
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        
        while (std::getline(iss, token, '|')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() >= 11 && tokens[10] == user_id) {
            ComputingPlan plan;
            plan.plan_id = tokens[0];
            plan.plan_name = tokens[1];
            plan.description = tokens[2];
            plan.priority = std::stoi(tokens[3]);
            plan.status = tokens[4];
            plan.cpu_cores = std::stoi(tokens[5]);
            plan.cpu_threads = std::stoi(tokens[6]);
            plan.gpu_count = std::stoi(tokens[7]);
            plan.gpu_type = tokens[8];
            plan.storage_gb = std::stod(tokens[9]);
            plan.user_id = tokens[10];
            plan.create_time = std::stoll(tokens[11]);
            plan.estimated_duration = std::stoll(tokens[12]);
            
            plans.push_back(plan);
        }
    }
    
    file.close();
    return plans;
}

// 显示计划信息
void ComputingPlan::displayPlanInfo() const {
    std::cout << "\n┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                  算力计划详情                     │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│ 计划ID: " << std::left << std::setw(39) << plan_id << "│\n";
    std::cout << "│ 计划名称: " << std::left << std::setw(37) << plan_name << "│\n";
    std::cout << "│ 状态: " << std::left << std::setw(41) << status << "│\n";
    std::cout << "│ 优先级: " << std::left << std::setw(39) << priority << "│\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                  资源需求                       │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│ CPU核心数: " << std::left << std::setw(36) << cpu_cores << "│\n";
    std::cout << "│ CPU线程数: " << std::left << std::setw(36) << cpu_threads << "│\n";
    std::cout << "│ GPU数量: " << std::left << std::setw(38) << gpu_count << "│\n";
    if (gpu_count > 0) {
        std::cout << "│ GPU类型: " << std::left << std::setw(38) << gpu_type << "│\n";
    }
    std::cout << "│ 存储空间(GB): " << std::left << std::setw(33) << storage_gb << "│\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    
    // 格式化时间
    char time_buf[100];
    std::tm* create_tm = std::localtime(&create_time);
    std::strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", create_tm);
    
    std::cout << "│ 创建时间: " << std::left << std::setw(37) << time_buf << "│\n";
    
    // 计算预计完成时间
    if (estimated_duration > 0) {
        std::time_t est_complete = create_time + estimated_duration;
        std::tm* est_tm = std::localtime(&est_complete);
        std::strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", est_tm);
        std::cout << "│ 预计完成时间: " << std::left << std::setw(33) << time_buf << "│\n";
    }
    
    std::cout << "└─────────────────────────────────────────────────┘\n";
}

// 更新计划状态
bool ComputingPlan::updateStatus(const std::string& new_status, const std::string& filename) {
    // 读取所有计划
    std::ifstream infile(filename, std::ios::binary); // 使用二进制模式
    if (!infile.is_open()) {
        return false;
    }
    
    std::vector<std::string> all_plans;
    std::string line;
    bool found = false;
    
    while (std::getline(infile, line)) {
        std::istringstream iss(line);
        std::string id;
        std::getline(iss, id, '|');
        
        if (id == plan_id) {
            found = true;
            status = new_status;
            
            // 更新这一行
            std::ostringstream updated_line;
            updated_line << plan_id << "|"
                      << plan_name << "|"
                      << description << "|"
                      << priority << "|"
                      << status << "|"
                      << cpu_cores << "|"
                      << cpu_threads << "|" 
                      << gpu_count << "|"
                      << gpu_type << "|"
                      << storage_gb << "|"
                      << user_id << "|"
                      << create_time << "|"
                      << estimated_duration;
                      
            all_plans.push_back(updated_line.str());
        } else {
            all_plans.push_back(line);
        }
    }
    
    infile.close();
    
    if (!found) {
        return false;
    }
    
    // 写回文件
    std::ofstream outfile(filename, std::ios::trunc | std::ios::binary); // 使用二进制模式
    if (!outfile.is_open()) {
        return false;
    }
    
    for (const auto& plan : all_plans) {
        outfile << plan << std::endl;
    }
    
    outfile.close();
    return true;
}

