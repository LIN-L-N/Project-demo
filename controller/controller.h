#pragma once

#include "../model/admin_model.h"
#include "../model/teacher_model.h"
#include "../model/student_model.h"

// 控制器入口函数

// 主菜单（系统入口，显示管理员/教师/学生登录选项）
void controller_main_menu(void);

// 管理员相关函数
void controller_admin_login(void);
void controller_admin_menu(Admin* admin);
void controller_admin_modify_password(Admin* admin);
void controller_admin_add_teacher(Teacher* teacher_list);
void controller_admin_view_teachers(Teacher* teacher_list);
void controller_admin_delete_teacher(Teacher* teacher_list);
void controller_admin_modify_teacher(Teacher* teacher_list);

// 教师相关函数
void controller_teacher_login(void);
void controller_teacher_menu(Teacher* current_teacher, Student* student_list);
void controller_teacher_modify_password(Teacher* teacher);
void controller_teacher_view_self(Teacher* teacher);
void controller_teacher_add_student(Student* student_list);
void controller_teacher_delete_student(Student* student_list);
void controller_teacher_view_student(Student* student_list);
void controller_teacher_modify_student(Student* student_list);
void controller_teacher_view_students_by_id(Student* student_list);
void controller_teacher_view_students_by_total(Student* student_list);

// 学生相关函数
void controller_student_login(void);
void controller_student_menu(Student* current_student);
void controller_student_modify_password(Student* student);
void controller_student_view_self(Student* student);