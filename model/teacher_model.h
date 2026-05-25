#pragma once
#include "../public.h"

// 教师数据类型
typedef struct Teacher {
    char name[MAX_NAME];       // 教师姓名
    char password[MAX_PWD];    // 登录密码
    char id[MAX_ID];           // 工号
    char gender;               // 性别
    Date birth;                // 出生日期
    struct Teacher* next;      // 指向下一个节点的指针
} Teacher;

// 教师链表操作函数

// 创建空链表（带头节点）
// 返回值：返回创建的头节点指针
Teacher* teacher_model_create_empty_list(void);

// 销毁整个链表
// 参数：head - 指向链表头指针的指针
void teacher_model_destroy_list(Teacher** head);

// 创建新节点
// 参数：name - 姓名，password - 密码，id - 工号，gender - 性别，birth - 出生日期
// 返回值：返回创建的新节点指针
Teacher* teacher_model_create_node(const char* name, const char* password, const char* id,
                                   char gender, Date birth);

// 销毁单个节点
// 参数：node - 要销毁的节点指针
void teacher_model_destroy_node(Teacher* node);

// 添加教师（工号不能重复）
// 参数：head - 链表头指针，name - 姓名，password - 密码，id - 工号，gender - 性别，birth - 出生日期
// 返回值：成功返回0，工号重复返回-2，失败返回-1
int teacher_model_add(Teacher** head, const char* name, const char* password, const char* id,
                      char gender, Date birth);

// 删除教师（按工号）
// 参数：head - 链表头指针，id - 要删除的工号
// 返回值：成功返回0，未找到返回-2，失败返回-1
int teacher_model_delete_by_id(Teacher** head, const char* id);

// 查找教师（按工号）
// 参数：head - 链表头指针，id - 要查找的工号
// 返回值：找到返回教师节点指针，未找到返回NULL
Teacher* teacher_model_find_by_id(Teacher* head, const char* id);

// 查找教师（按姓名和密码，用于登录验证）
// 参数：head - 链表头指针，name - 姓名，password - 密码
// 返回值：找到返回教师节点指针，未找到返回NULL
Teacher* teacher_model_find_by_name_pwd(Teacher* head, const char* name, const char* password);

// 修改教师信息
// 参数：head - 链表头指针，id - 要修改的工号，new_name - 新姓名，new_password - 新密码，
//       new_gender - 新性别，new_birth - 新出生日期
// 返回值：成功返回0，失败返回-1
int teacher_model_modify(Teacher* head, const char* id, const char* new_name,
                         const char* new_password, char new_gender, Date new_birth);

// 显示所有教师信息
// 参数：head - 链表头指针
void teacher_model_display_all(Teacher* head);

// 保存教师链表到文件
// 参数：head - 链表头指针
void teacher_model_save_to_file(Teacher* head);

// 从文件加载教师链表
// 返回值：返回加载后的链表头指针
Teacher* teacher_model_load_from_file(void);