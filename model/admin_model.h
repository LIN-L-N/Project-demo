#pragma once
#include "../public.h"

// 管理员数据类型
typedef struct {
    char name[MAX_NAME];      // 管理员用户名
    char password[MAX_PWD];    // 管理员密码
} Admin;

// 管理员相关操作函数

// 从文件读取管理员信息
// 返回值：读取到的管理员结构体
Admin admin_model_read(void);

// 将管理员信息写入文件
// 参数：admin - 要写入的管理员结构体
void admin_model_write(Admin admin);

// 验证管理员登录信息
// 参数：admin - 管理员信息，input_name - 输入的用户名，input_pwd - 输入的密码
// 返回值：验证成功返回1，失败返回0
int admin_model_verify(Admin admin, const char* input_name, const char* input_pwd);

// 修改管理员密码
// 参数：admin - 管理员指针，new_password - 新密码
void admin_model_modify_password(Admin* admin, const char* new_password);