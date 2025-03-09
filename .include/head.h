#include <bits/stdc++.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

class ComputingPlan {
private:
    // 基本信息
    std::string plan_name;
    std::string description;       // 计划描述
    int priority;                  // 1-10，数字越大优先级越高
    std::string status;            // "Pending", "Running", "Completed", "Failed"
    // 资源需求
    int cpu_cores;                 // 所需CPU核心数
    int cpu_threads;               // 所需CPU线程数
    int gpu_count;                 // 所需GPU数量
    std::string gpu_type;          // GPU类型 (例如 "NVIDIA A100")
    double storage_gb;             // 所需存储空间(GB)
    // 计划元数据
    std::string user_id;           // 用户ID
    std::time_t create_time;       // 创建时间
    std::time_t estimated_duration; // 预计运行时间(秒)
    // 生成唯一计划ID
    std::string generatePlanId() const;

public:
    std::string plan_id;           // 计划唯一标识符
    // 默认构造函数
    ComputingPlan();
    
    // 参数化构造函数
    ComputingPlan(const std::string& name, const std::string& uid, 
                 int cpu_c, int cpu_t, int gpu_c, const std::string& gpu_t, 
                 double storage);
    
    // 设置函数
    void setPlanName(const std::string& name);
    void setDescription(const std::string& desc);
    void setPriority(int p);
    void setStatus(const std::string& stat);
    void setUserId(const std::string& uid);
    void setEstimatedDuration(int seconds);
    
    // 获取函数
    std::string getPlanName() const;
    std::string getPlanId() const;
    std::string getDescription() const;
    int getPriority() const;
    std::string getStatus() const;
    int getCpuCores() const;
    int getCpuThreads() const;
    int getGpuCount() const;
    std::string getGpuType() const;
    double getStorageGb() const;
    std::string getUserId() const;
    std::time_t getCreateTime() const;
    std::time_t getEstimatedDuration() const;
    // 保存计划到文件
    bool saveToFile(const std::string& filename = "computing_plans.txt");
    // 从文件加载特定计划
    static ComputingPlan loadFromFile(const std::string& plan_id, const std::string& filename = "computing_plans.txt");
    // 加载用户的所有计划
    static std::vector<ComputingPlan> loadUserPlans(const std::string& user_id, const std::string& filename = "computing_plans.txt");
    // 显示计划信息
    void displayPlanInfo() const;
    // 更新计划状态
    bool updateStatus(const std::string& new_status, const std::string& filename = "computing_plans.txt");
};

// 创建一个 “用户类” 保存用户信息
class user_info {
private:
    std::string user_name;
    std::string user_password;
    int user_hash_uuid;
    bool is_logged_in;
public:
    user_info(const std::string &_user_name, const std::string &_user_password);
    // 无参构造函数
    user_info();
    // Getters
    int _get_uuid();
    std::string get_User_name() const;
    int get_UID() const;
    bool is_LoggedIn() const;
    // Setters
    void set_LoggedIn(bool status);
    void in_file();

};

// 声明全局用户对象
extern user_info current_user;

void head();
void displayResourceInfo();
void displaySystemInfo();
void SchedulingStrategies();
void __user_register_satic();
void user_register_satic();
void user_Register();
void fast_clear();
int get_uuid(const std::string &user_name, const std::string &user_password);
void user_login();
void user__interface();
void _create_plan();
void _edit_plan();
void _delete_plan();
void _interface();
void administrator_interface();
void admin_login();