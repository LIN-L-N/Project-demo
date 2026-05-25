#pragma once
#include "../public.h"

// 界面输入输出函数

// 打印标题（带边框）
// 参数：title - 标题文本
void view_print_title(const char* title);

// 打印菜单
// 参数：title - 菜单标题，items - 菜单项数组，count - 菜单项数量
void view_print_menu(const char* title, const char** items, int count);

// 获取整数输入
// 参数：prompt - 提示文本
// 返回值：用户输入的整数
int view_get_int(const char* prompt);

// 获取字符串输入
// 参数：prompt - 提示文本，dest - 目标字符串，max_len - 最大长度
void view_get_string(const char* prompt, char* dest, int max_len);

// 打印成功消息（带✓标记）
// 参数：message - 消息文本
void view_print_success(const char* message);

// 打印错误消息（带✗标记）
// 参数：message - 消息文本
void view_print_error(const char* message);

// 打印普通信息
// 参数：message - 消息文本
void view_print_info(const char* message);

// 暂停等待（按任意键继续）
void view_pause(void);