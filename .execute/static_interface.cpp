#include "head.h"

void displaySystemInfo()
{
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                  系统说明                       │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  智能算力调度系统(ICPSS)是一个用于优化计算资源  │\n";
    std::cout << "│  分配的平台,主要功能包括:                     │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  · 智能任务排队与优先级分配                     │\n";
    std::cout << "│  · 动态资源分配与释放                           │\n";
    std::cout << "│  · 节点状态监控与故障转移                       │\n";
    std::cout << "│  · 用户配额管理                                 │\n";
    std::cout << "│  · 历史使用数据分析                             │\n";
    std::cout << "│  · 支持多种计算节点类型                         │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  本系统采用多种调度算法,确保算力资源的高效利用  │\n";
    std::cout << "│  和公平分配.                                   │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    fast_clear();
    head();
}

void displayResourceInfo()
{
    int Random_wait_time, Random_load;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // 2 到 15 的随机数,用于模拟等待时间
    Random_wait_time = 2 + (std::rand() % 35);
    // 使用 wait_time 做基数生成负载随机数
    Random_load = 10 + (std::rand() % 90);
    // 生成负载随机数
    Random_load = (Random_load + Random_wait_time) % 100;
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                可用算力资源                     │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  高性能计算节点:                                │\n";
    std::cout << "│  · CPU集群: 128核心/256线程 x 12节点            │\n";
    std::cout << "│  · GPU集群: NVIDIA A100 x 16节点                │\n";
    std::cout << "│  · 专用AI芯片: TPU v4 x 8节点                   │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  存储资源:                                      │\n";
    std::cout << "│  · 高性能存储: 500TB (读写速度: 12GB/s)         │\n";
    std::cout << "│  · 冷存储: 2PB                                  │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  当前系统负载: " << Random_load << "%                              │\n";
    std::cout << "│  预计排队等待时间: 约" << Random_wait_time << (Random_wait_time < 10 ? " " : "")
              << "分钟                     │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    fast_clear();
    head();
}

void SchedulingStrategies()
{
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                 调度策略介绍                    │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  本系统采用以下几种调度策略:                   │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  1. 先来先服务 (FCFS)                           │\n";
    std::cout << "│     按照任务提交时间顺序依次分配资源,确保公平  │\n";
    std::cout << "│     性,但可能导致大型任务阻塞后续小型任务      │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  2. 资源压力优先 (RPF)                          │\n";
    std::cout << "│     优先分配给资源需求较小的任务,提高系统吞吐  │\n";
    std::cout << "│     量,适合处理大量小型计算任务的场景          │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  3. 用户定义优先级 (UDP)                        │\n";
    std::cout << "│     根据用户指定的任务重要度进行优先级排序,    │\n";
    std::cout << "│     重要任务优先获取资源,适用于紧急任务处理    │\n";
    std::cout << "│                                                 │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                任务调度状态                     │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  1. Pending (待处理)                            │\n";
    std::cout << "│     任务已提交但尚未分配计算资源,处于等待队列  │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  2. Running (运行中)                            │\n";
    std::cout << "│     任务已获得所需资源并正在执行计算过程        │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  3. Completed (已完成)                          │\n";
    std::cout << "│     任务已成功完成全部计算,结果可供查询        │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  4. Failed (任务出错)                           │\n";
    std::cout << "│     任务执行过程中遇到错误,未能正常完成        │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    fast_clear();
    head();
}

void __user_register_satic()
{
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                 注册须知                        │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  尊敬的用户，在您注册前，请阅读以下须知：       │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  1. 本项目仅作模拟操作，并非真实算力调度项目    │\n";
    std::cout << "│     所有展示的数据和功能均为演示用途            │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  2. 本项目完全依靠本地计算实行，并且基于MIT     │\n";
    std::cout << "│     协议完全开源供学习借鉴使用                  │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  3. 在注册时请使用ASCII字符设置用户名与密码，   │\n";
    std::cout << "│     避免文件读写异常                            │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  4. 本项目作者为imicola                         │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  5. 本项目已经发布至github                      │\n";
    std::cout << "│                                                 │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                 隐私声明                        │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  · 所有用户数据仅存储在本地                     │\n";
    std::cout << "│  · 不会收集或上传任何个人信息                   │\n";
    std::cout << "│  · 用户数据将以明文形式保存，请勿使用常用密码   │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    std::cout << "\n是否继续注册? (y/n): ";
}

void user__interface()
{
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                  用户控制面板                   │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  1. 算力使用计划                                │\n";
    std::cout << "│     查看和管理您的计算任务执行计划              │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  2. 计划编辑                                    │\n";
    std::cout << "│     创建新任务或修改现有计算任务参数            │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  3. 用户使用算力情况                            │\n";
    std::cout << "│     查看您的算力使用统计和剩余配额              │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  0. 退出登录                                    │\n";
    std::cout << "│                                                 │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│tips:由于是运行读入文件,创建完后请重新运行程序   │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    std::cout << "\n请选择操作 [0-3]: ";
}

void administrator_interface()
{
    std::cout << "\n\n";
    std::cout << "┌─────────────────────────────────────────────────┐\n";
    std::cout << "│                 管理员控制面板                  │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  1. 系统状态监控                                │\n";
    std::cout << "│     查看当前系统负载、资源分配和节点状态        │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  2. 所有用户算力任务提交                        │\n";
    std::cout << "│     审核和管理所有用户提交的计算任务            │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  3. 调整总算力                                  │\n";
    std::cout << "│     优化资源分配策略和调整可用计算资源          │\n";
    std::cout << "│                                                 │\n";
    std::cout << "│  0. 退出管理员模式                              │\n";
    std::cout << "│                                                 │\n";
    std::cout << "├─────────────────────────────────────────────────┤\n";
    std::cout << "│                                                 │\n";
    std::cout << "│警告: 管理员操作将直接影响所有用户的计算任务     │\n";
    std::cout << "│                                                 │\n";
    std::cout << "└─────────────────────────────────────────────────┘\n";
    std::cout << "\n请选择操作 [0-3]: ";
}