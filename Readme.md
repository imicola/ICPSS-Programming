# 智能算力调度系统 (ICPSS)
## 项目介绍
智能算力调度系统(ICPSS)是一个用于模拟优化计算资源分配的平台。本项目作为大一程序设计课程的大作业，旨在通过实践C++编程，实现一个具有基本功能的算力资源调度系统模拟界面。

## 功能概述
目前已实现的功能：

- 系统主界面展示
- 用户注册功能（包含密码安全检查）
- 系统信息展示
算力资源信息展示（包含随机生成的负载和等待时间）
- 调度策略介绍  

待实现的功能：

- 用户登录
- 系统状态监控
- 算力任务提交
- 历史记录查询

项目结构

```file
.code_exe/       - 编译后的可执行文件
.execute/        - 功能实现源文件
  |- head.cpp    - 主菜单实现
  |- other.cpp   - 辅助功能函数
  |- static interface.cpp - 静态界面实现
  |- user_register.cpp    - 用户注册功能
.include/        - 头文件
  |- head.h      - 函数声明
code/            - 主程序入口
  |- main.cpp    - 程序主入口
.vscode/         - VSCode配置文件
```

技术特点

- 使用C++标准库实现基本功能
- 采用Windows API实现控制台界面交互
- 实现了密码输入保护（输入时显示*）
- 模拟了资源负载和等待时间的随机生成

如何运行

1. 确保您的系统已安装MinGW编译器
2. 使用VSCode打开项目文件夹
3. 在VSCode中按F5或使用"编译并执行"配置运行程序
调度策略

系统设计了三种调度策略：

1. 先来先服务 (FCFS)
2. 资源压力优先 (RPF)
3. 用户定义优先级 (UDP)

开发计划

<input disabled="" type="checkbox"> 完成用户登录功能

<input disabled="" type="checkbox"> 实现系统状态监控

<input disabled="" type="checkbox"> 开发算力任务提交功能

<input disabled="" type="checkbox"> 实现历史记录查询功能

<input disabled="" type="checkbox"> 添加数据持久化存储

<input disabled="" type="checkbox"> 优化用户界面体验

## 授权协议

本项目基于MIT协议开源

## 作者
imicola

## 注意事项
本项目仅作为学习和演示用途，所有展示的数据和功能均为模拟。用户数据以明文形式保存在本地，请勿使用常用密码。