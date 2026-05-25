#include "controller.h"
#include "../view/view.h"

// 主菜单
void controller_main_menu(void)
{
    const char* menu_items[] = {
        "管理员登录",
        "教师登录", 
        "学生登录",
        "退出系统"
    };
    
    int choice;
    while(1) {
        view_print_menu("欢迎进入教务管理系统", menu_items, 4);
        choice = view_get_int("请输入您的选择：");
        
        switch(choice) {
            case 1: controller_admin_login(); break;
            case 2: controller_teacher_login(); break;
            case 3: controller_student_login(); break;
            case 4: view_print_info("感谢使用！"); return;
            default: view_print_error("无效请重新输入！");
        }
    }
}

// 管理员登录
void controller_admin_login(void)
{
    Admin admin = admin_model_read();
    char name[MAX_NAME], password[MAX_PWD];
    int try_count = 0;
    
    while(try_count < 3) {
        view_print_title("管理员登录");
        view_get_string("请输入用户名：", name, MAX_NAME);
        view_get_string("请输入密码：", password, MAX_PWD);
        
        if(admin_model_verify(admin, name, password)) {
            view_print_success("登录成功！");
            controller_admin_menu(&admin);
            return;
        } else {
            try_count++;
            view_print_error("用户名或密码错误！");
            view_print_info("剩余尝试次数：");
            printf("%d\n", 3 - try_count);
        }
    }
    view_print_error("连续3次登录失败,退出管理员界面!");
}

// 管理员菜单
void controller_admin_menu(Admin* admin)
{
    const char* menu_items[] = {
        "修改自身登录密码",
        "添加新教师",
        "查看所有教师",
        "删除教师",
        "修改教师信息",
        "返回",
    };
    
    Teacher* teacher_list = teacher_model_load_from_file();
    int choice;
    
    while(1) {
        view_print_menu("管理员功能菜单", menu_items, 6);
        choice = view_get_int("请输入您的选择：");
        
        switch(choice) {
            case 1: controller_admin_modify_password(admin); break;
            case 2: controller_admin_add_teacher(teacher_list); break;
            case 3: controller_admin_view_teachers(teacher_list); break;
            case 4: controller_admin_delete_teacher(teacher_list); break;
            case 5: controller_admin_modify_teacher(teacher_list); break;
            case 6: 
                teacher_model_save_to_file(teacher_list);
                teacher_model_destroy_list(&teacher_list);
                view_print_success("数据已保存！");
                return;
            default: view_print_error("无效选项，请重新输入！");
        }
    }
}

// 管理员修改密码
void controller_admin_modify_password(Admin* admin)
{
    char old_pwd[MAX_PWD], new_pwd[MAX_PWD], confirm_pwd[MAX_PWD];
    
    view_get_string("请输入原密码：", old_pwd, MAX_PWD);
    if(strcmp(admin->password, old_pwd) != 0) {
        view_print_error("原密码错误！");
        return;
    }
    
    view_get_string("请输入新密码：", new_pwd, MAX_PWD);
    view_get_string("请确认新密码：", confirm_pwd, MAX_PWD);
    
    if(strcmp(new_pwd, confirm_pwd) != 0) {
        view_print_error("两次输入的密码不一致！");
        return;
    }
    
    admin_model_modify_password(admin, new_pwd);
    view_print_success("密码修改成功！");
}

// 管理员添加教师
void controller_admin_add_teacher(Teacher* teacher_list)
{
    char name[MAX_NAME], password[MAX_PWD], id[MAX_ID];
    char gender;
    Date birth;
    
    view_get_string("请输入教师姓名：", name, MAX_NAME);
    view_get_string("请输入教师密码：", password, MAX_PWD);
    view_get_string("请输入教师工号：", id, MAX_ID);
    gender = view_get_int("请输入性别（男:1/女:0):") == 1 ? 'M' : 'F';
    birth.year = view_get_int("请输入出生年份：");
    birth.month = view_get_int("请输入出生月份：");
    birth.day = view_get_int("请输入出生日期：");
    
    int result = teacher_model_add(&teacher_list, name, password, id, gender, birth);
    if(result == 0) {
        view_print_success("添加教师成功！");
    } else if(result == -2) {
        view_print_error("工号重复！");
    } else {
        view_print_error("添加教师失败！");
    }
}

// 管理员查看教师
void controller_admin_view_teachers(Teacher* teacher_list)
{
    view_print_title("所有教师信息");
    teacher_model_display_all(teacher_list);
    view_pause();
}

// 管理员删除教师
void controller_admin_delete_teacher(Teacher* teacher_list)
{
    char id[MAX_ID];
    view_get_string("请输入要删除的教师工号：", id, MAX_ID);
    
    int result = teacher_model_delete_by_id(&teacher_list, id);
    if(result == 0) {
        view_print_success("删除成功！");
    } else if(result == -2) {
        view_print_error("未找到该教师！");
    } else {
        view_print_error("删除失败！");
    }
}

// 管理员修改教师信息
void controller_admin_modify_teacher(Teacher* teacher_list)
{
    char id[MAX_ID], name[MAX_NAME], password[MAX_PWD];
    char gender;
    Date birth;
    
    view_get_string("请输入要修改的教师工号：", id, MAX_ID);
    
    Teacher* teacher = teacher_model_find_by_id(teacher_list, id);
    if(teacher == NULL) {
        view_print_error("未找到该教师！");
        return;
    }
    
    view_get_string("请输入新姓名：", name, MAX_NAME);
    view_get_string("请输入新密码：", password, MAX_PWD);
    gender = view_get_int("请输入新性别（男:1/女:0): ") == 1 ? 'M' : 'F';
    birth.year = view_get_int("请输入新出生年份：");
    birth.month = view_get_int("请输入新出生月份：");
    birth.day = view_get_int("请输入新出生日期：");
    
    int result = teacher_model_modify(teacher_list, id, name, password, gender, birth);
    if(result == 0) {
        view_print_success("修改成功！");
    } else {
        view_print_error("修改失败！");
    }
}

// 教师登录
void controller_teacher_login(void)
{
    Teacher* teacher_list = teacher_model_load_from_file();
    Student* student_list = student_model_load_from_file();
    
    char name[MAX_NAME], password[MAX_PWD];
    int try_count = 0;
    Teacher* current_teacher = NULL;
    
    while(try_count < 3) {
        view_print_title("教师登录");
        view_get_string("请输入用户名：", name, MAX_NAME);
        view_get_string("请输入密码：", password, MAX_PWD);
        
        current_teacher = teacher_model_find_by_name_pwd(teacher_list, name, password);
        if(current_teacher != NULL) {
            view_print_success("登录成功！");
            controller_teacher_menu(current_teacher, student_list);
            break;
        } else {
            try_count++;
            view_print_error("用户名或密码错误！");
            view_print_info("剩余尝试次数：");
            printf("%d\n", 3 - try_count);
        }
    }
    
    if(try_count >= 3) {
        view_print_error("连续3次登录失败,退出教师界面!");
    }
    
    teacher_model_save_to_file(teacher_list);
    student_model_save_to_file(student_list);
    teacher_model_destroy_list(&teacher_list);
    student_model_destroy_list(&student_list);
}

// 教师菜单
void controller_teacher_menu(Teacher* current_teacher, Student* student_list)
{
    const char* menu_items[] = {
        "修改自身登录密码",
        "查阅自身信息",
        "添加新学生",
        "删除学生",
        "查阅指定学生信息",
        "修改学生信息",
        "按学号查看所有学生",
        "按总分查看所有学生",
        "返回",
    };
    
    int choice;
    while(1) {
        view_print_menu("教师功能菜单", menu_items, 9);
        choice = view_get_int("请输入您的选择：");
        
        switch(choice) {
            case 1: controller_teacher_modify_password(current_teacher); break;
            case 2: controller_teacher_view_self(current_teacher); break;
            case 3: controller_teacher_add_student(student_list); break;
            case 4: controller_teacher_delete_student(student_list); break;
            case 5: controller_teacher_view_student(student_list); break;
            case 6: controller_teacher_modify_student(student_list); break;
            case 7: controller_teacher_view_students_by_id(student_list); break;
            case 8: controller_teacher_view_students_by_total(student_list); break;
            case 9: return;
            default: view_print_error("无效选项，请重新输入！");
        }
    }
}

// 教师修改密码
void controller_teacher_modify_password(Teacher* teacher)
{
    char old_pwd[MAX_PWD], new_pwd[MAX_PWD], confirm_pwd[MAX_PWD];
    
    view_get_string("请输入原密码：", old_pwd, MAX_PWD);
    if(strcmp(teacher->password, old_pwd) != 0) {
        view_print_error("原密码错误！");
        return;
    }
    
    view_get_string("请输入新密码：", new_pwd, MAX_PWD);
    view_get_string("请确认新密码：", confirm_pwd, MAX_PWD);
    
    if(strcmp(new_pwd, confirm_pwd) != 0) {
        view_print_error("两次输入的密码不一致！");
        return;
    }
    
    strcpy(teacher->password, new_pwd);
    view_print_success("密码修改成功！");
}

// 教师查看自身信息
void controller_teacher_view_self(Teacher* teacher)
{
    view_print_title("教师信息");
    printf("Name: %s\n", teacher->name);
    printf("ID: %s\n", teacher->id);
    printf("Gender: %c\n", teacher->gender);
    printf("Birth: %d-%d-%d\n", 
           teacher->birth.year, teacher->birth.month, teacher->birth.day);
    view_pause();
}

// 教师添加学生
void controller_teacher_add_student(Student* student_list)
{
    char name[MAX_NAME], password[MAX_PWD], id[MAX_ID];
    char gender;
    Date birth;
    float math, chinese, english;
    
    view_get_string("请输入学生姓名：", name, MAX_NAME);
    view_get_string("请输入学生密码：", password, MAX_PWD);
    view_get_string("请输入学生学号：", id, MAX_ID);
    gender = view_get_int("请输入性别（男:1/女:0):") == 1 ? 'M' : 'F';
    birth.year = view_get_int("请输入出生年份：");
    birth.month = view_get_int("请输入出生月份：");
    birth.day = view_get_int("请输入出生日期：");
    math = (float)view_get_int("请输入数学成绩：");
    chinese = (float)view_get_int("请输入语文成绩：");
    english = (float)view_get_int("请输入英语成绩：");
    
    int result = student_model_add(&student_list, name, password, id, gender, birth, math, chinese, english);
    if(result == 0) {
        view_print_success("添加学生成功！");
    } else if(result == -2) {
        view_print_error("学号重复！");
    } else {
        view_print_error("添加学生失败！");
    }
}

// 教师删除学生
void controller_teacher_delete_student(Student* student_list)
{
    char id[MAX_ID];
    view_get_string("请输入要删除的学生学号：", id, MAX_ID);
    
    int result = student_model_delete_by_id(&student_list, id);
    if(result == 0) {
        view_print_success("删除成功！");
    } else if(result == -2) {
        view_print_error("未找到该学生！");
    } else {
        view_print_error("删除失败！");
    }
}

// 教师查看指定学生
void controller_teacher_view_student(Student* student_list)
{
    char id[MAX_ID];
    view_get_string("请输入要查询的学生学号：", id, MAX_ID);
    
    Student* student = student_model_find_by_id(student_list, id);
    if(student == NULL) {
        view_print_error("未找到该学生！");
        return;
    }
    
    view_print_title("学生信息");
    printf("姓名：%s\n", student->name);
    printf("学号：%s\n", student->id);
    printf("性别：%c\n", student->gender);
    printf("出生日期：%d-%d-%d\n", 
           student->birth.year, student->birth.month, student->birth.day);
    printf("数学：%.2f\n", student->math);
    printf("语文：%.2f\n", student->chinese);
    printf("英语：%.2f\n", student->english);
    printf("总分：%.2f\n", student->math + student->chinese + student->english);
    view_pause();
}

// 教师修改学生信息
void controller_teacher_modify_student(Student* student_list)
{
    char id[MAX_ID], name[MAX_NAME];
    char gender;
    Date birth;
    float math, chinese, english;
    
    view_get_string("请输入要修改的学生学号：", id, MAX_ID);
    
    Student* student = student_model_find_by_id(student_list, id);
    if(student == NULL) {
        view_print_error("未找到该学生！");
        return;
    }
    
    view_get_string("请输入新姓名：", name, MAX_NAME);
    gender = view_get_int("请输入新性别（男:1/女:0):") == 1 ? 'M' : 'F';
    birth.year = view_get_int("请输入新出生年份：");
    birth.month = view_get_int("请输入新出生月份：");
    birth.day = view_get_int("请输入新出生日期：");
    math = (float)view_get_int("请输入新数学成绩：");
    chinese = (float)view_get_int("请输入新语文成绩：");
    english = (float)view_get_int("请输入新英语成绩：");
    
    int result = student_model_modify(student_list, id, name, gender, birth, math, chinese, english);
    if(result == 0) {
        view_print_success("修改成功！");
    } else {
        view_print_error("修改失败！");
    }
}

// 教师按学号查看学生
void controller_teacher_view_students_by_id(Student* student_list)
{
    view_print_title("按学号排序学生信息");
    student_model_sort_by_id(student_list);
    student_model_display_all(student_list);
    view_pause();
}

// 教师按总分查看学生
void controller_teacher_view_students_by_total(Student* student_list)
{
    view_print_title("按总分排序学生信息");
    student_model_sort_by_total(student_list);
    student_model_display_all(student_list);
    view_pause();
}

// 学生登录
void controller_student_login(void)
{
    Student* student_list = student_model_load_from_file();
    
    char name[MAX_NAME], password[MAX_PWD];
    int try_count = 0;
    Student* current_student = NULL;
    
    while(try_count < 3) {
        view_print_title("学生登录");
        view_get_string("请输入用户名：", name, MAX_NAME);
        view_get_string("请输入密码：", password, MAX_PWD);
        
        current_student = student_model_find_by_name_pwd(student_list, name, password);
        if(current_student != NULL) {
            view_print_success("登录成功！");
            controller_student_menu(current_student);
            break;
        } else {
            try_count++;
            view_print_error("用户名或密码错误！");
            view_print_info("剩余尝试次数：");
            printf("%d\n", 3 - try_count);
        }
    }
    
    if(try_count >= 3) {
        view_print_error("连续3次登录失败，退出学生界面！");
    }
    
    student_model_save_to_file(student_list);
    student_model_destroy_list(&student_list);
}

// 学生菜单
void controller_student_menu(Student* current_student)
{
    const char* menu_items[] = {
        "修改自身登录密码",
        "查阅自身信息",
        "返回上一层"
    };
    
    int choice;
    while(1) {
        view_print_menu("学生功能菜单", menu_items, 3);
        choice = view_get_int("请输入您的选择：");
        
        switch(choice) {
            case 1: controller_student_modify_password(current_student); break;
            case 2: controller_student_view_self(current_student); break;
            case 3: return;
            default: view_print_error("无效选项，请重新输入！");
        }
    }
}

// 学生修改密码
void controller_student_modify_password(Student* student)
{
    char old_pwd[MAX_PWD], new_pwd[MAX_PWD], confirm_pwd[MAX_PWD];
    
    view_get_string("请输入原密码：", old_pwd, MAX_PWD);
    if(strcmp(student->password, old_pwd) != 0) {
        view_print_error("原密码错误！");
        return;
    }
    
    view_get_string("请输入新密码：", new_pwd, MAX_PWD);
    view_get_string("请确认新密码：", confirm_pwd, MAX_PWD);
    
    if(strcmp(new_pwd, confirm_pwd) != 0) {
        view_print_error("两次输入的密码不一致！");
        return;
    }
    
    strcpy(student->password, new_pwd);
    view_print_success("密码修改成功！");
}

// 学生查看自身信息
void controller_student_view_self(Student* student)
{
    view_print_title("学生信息");
    printf("姓名：%s\n", student->name);
    printf("学号：%s\n", student->id);
    printf("性别：%c\n", student->gender);
    printf("出生日期：%d-%d-%d\n", 
           student->birth.year, student->birth.month, student->birth.day);
    printf("数学：%.2f\n", student->math);
    printf("语文：%.2f\n", student->chinese);
    printf("英语：%.2f\n", student->english);
    printf("总分：%.2f\n", student->math + student->chinese + student->english);
    view_pause();
}