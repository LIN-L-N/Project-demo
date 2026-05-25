#pragma once
#include "../public.h"

// 学生数据类型
typedef struct Student {
    char name[MAX_NAME];       // 学生姓名
    char password[MAX_PWD];    // 登录密码
    char id[MAX_ID];           // 学号
    char gender;               // 性别
    Date birth;                // 出生日期
    float math;                // 数学成绩
    float chinese;             // 语文成绩
    float english;             // 英语成绩
    struct Student* next;      // 指向下一个节点的指针
} Student;

// 学生链表操作函数

// 创建空链表（带头节点）
// 返回值：返回创建的头节点指针
Student* student_model_create_empty_list(void);

// 销毁整个链表
// 参数：head - 指向链表头指针的指针
void student_model_destroy_list(Student** head);

// 创建新节点
// 参数：name - 姓名，password - 密码，id - 学号，gender - 性别，birth - 出生日期，
//       math - 数学成绩，chinese - 语文成绩，english - 英语成绩
// 返回值：返回创建的新节点指针
Student* student_model_create_node(const char* name, const char* password, const char* id,
                                   char gender, Date birth, float math, float chinese, float english);

// 销毁单个节点
// 参数：node - 要销毁的节点指针
void student_model_destroy_node(Student* node);

// 添加学生（学号不能重复）
// 参数：head - 链表头指针，name - 姓名，password - 密码，id - 学号，gender - 性别，birth - 出生日期，
//       math - 数学成绩，chinese - 语文成绩，english - 英语成绩
// 返回值：成功返回0，学号重复返回-2，失败返回-1
int student_model_add(Student** head, const char* name, const char* password, const char* id,
                      char gender, Date birth, float math, float chinese, float english);

// 删除学生（按学号）
// 参数：head - 链表头指针，id - 要删除的学号
// 返回值：成功返回0，未找到返回-2，失败返回-1
int student_model_delete_by_id(Student** head, const char* id);

// 查找学生（按学号）
// 参数：head - 链表头指针，id - 要查找的学号
// 返回值：找到返回学生节点指针，未找到返回NULL
Student* student_model_find_by_id(Student* head, const char* id);

// 查找学生（按姓名和密码，用于登录验证）
// 参数：head - 链表头指针，name - 姓名，password - 密码
// 返回值：找到返回学生节点指针，未找到返回NULL
Student* student_model_find_by_name_pwd(Student* head, const char* name, const char* password);

// 修改学生信息
// 参数：head - 链表头指针，id - 要修改的学号，new_name - 新姓名，new_gender - 新性别，
//       new_birth - 新出生日期，new_math - 新数学成绩，new_chinese - 新语文成绩，new_english - 新英语成绩
// 返回值：成功返回0，失败返回-1
int student_model_modify(Student* head, const char* id, const char* new_name, char new_gender,
                         Date new_birth, float new_math, float new_chinese, float new_english);

// 显示所有学生信息
// 参数：head - 链表头指针
void student_model_display_all(Student* head);

// 按学号升序排序
// 参数：head - 链表头指针
void student_model_sort_by_id(Student* head);

// 按总分降序排序
// 参数：head - 链表头指针
void student_model_sort_by_total(Student* head);

// 保存学生链表到文件
// 参数：head - 链表头指针
void student_model_save_to_file(Student* head);

// 从文件加载学生链表
// 返回值：返回加载后的链表头指针
Student* student_model_load_from_file(void);