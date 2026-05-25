#include "student_model.h"

// 创建空表
Student* student_model_create_empty_list(void)
{
    Student* head = (Student*)malloc(sizeof(Student));
    if(head != NULL) {
        head->next = NULL;
    }
    return head;
}

// 销毁整个链表
void student_model_destroy_list(Student** head)
{
    if(head == NULL || *head == NULL) return;
    
    Student* p = *head;
    Student* next;
    while(p != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
    *head = NULL;
}

// 创建一个新节点
Student* student_model_create_node(const char* name, const char* password, const char* id, 
                                   char gender, Date birth, float math, float chinese, float english)
{
    Student* node = (Student*)malloc(sizeof(Student));
    if(node == NULL) return NULL;
    
    strcpy(node->name, name);
    strcpy(node->password, password);
    strcpy(node->id, id);
    node->gender = gender;
    node->birth = birth;
    node->math = math;
    node->chinese = chinese;
    node->english = english;
    node->next = NULL;
    
    return node;
}

// 销毁一个指定节点
void student_model_destroy_node(Student* node)
{
    if(node != NULL) {
        free(node);
    }
}

// 增加学生
int student_model_add(Student** head, const char* name, const char* password, const char* id, 
                      char gender, Date birth, float math, float chinese, float english)
{
    if(head == NULL || *head == NULL) return -1;
    
    // 检查学号是否重复
    if(student_model_find_by_id(*head, id) != NULL) {
        return -2; // 学号重复
    }
    
    Student* new_node = student_model_create_node(name, password, id, gender, birth, math, chinese, english);
    if(new_node == NULL) return -1;
    
    // 头插法
    new_node->next = (*head)->next;
    (*head)->next = new_node;
    
    return 0;
}

// 删除学生（按学号）
int student_model_delete_by_id(Student** head, const char* id)
{
    if(head == NULL || *head == NULL || (*head)->next == NULL) return -1;
    
    Student* p = (*head)->next;
    Student* prev = *head;
    
    while(p != NULL) {
        if(strcmp(p->id, id) == 0) {
            prev->next = p->next;
            free(p);
            return 0;
        }
        prev = p;
        p = p->next;
    }
    
    return -2; // 未找到
}

// 查找学生（按学号）
Student* student_model_find_by_id(Student* head, const char* id)
{
    if(head == NULL) return NULL;
    
    Student* p = head->next;
    while(p != NULL) {
        if(strcmp(p->id, id) == 0) {
            return p;
        }
        p = p->next;
    }
    
    return NULL;
}

// 查找学生（按姓名和密码）
Student* student_model_find_by_name_pwd(Student* head, const char* name, const char* password)
{
    if(head == NULL) return NULL;
    
    Student* p = head->next;
    while(p != NULL) {
        if(strcmp(p->name, name) == 0 && strcmp(p->password, password) == 0) {
            return p;
        }
        p = p->next;
    }
    
    return NULL;
}

// 修改学生信息
int student_model_modify(Student* head, const char* id, const char* new_name, char new_gender, 
                         Date new_birth, float new_math, float new_chinese, float new_english)
{
    Student* student = student_model_find_by_id(head, id);
    if(student == NULL) return -1;
    
    if(new_name != NULL) strcpy(student->name, new_name);
    student->gender = new_gender;
    student->birth = new_birth;
    student->math = new_math;
    student->chinese = new_chinese;
    student->english = new_english;
    
    return 0;
}

// 显示所有学生
void student_model_display_all(Student* head)
{
    if(head == NULL || head->next == NULL) {
        printf("暂无学生信息\n");
        return;
    }
    
    Student* p = head->next;
    while(p != NULL) {
        printf("学号:%s\t姓名:%s\t性别:%c\t数学:%.2f\t语文:%.2f\t英语:%.2f\t总分:%.2f\n",
               p->id, p->name, p->gender, 
               p->math, p->chinese, p->english,
               p->math + p->chinese + p->english);
        p = p->next;
    }
}

// 按学号升序排序
void student_model_sort_by_id(Student* head)
{
    if(head == NULL || head->next == NULL || head->next->next == NULL) return;
    
    Student *p, *tail = NULL;
    while(head->next != tail) {
        p = head->next;
        while(p->next != tail) {
            if(strcmp(p->id, p->next->id) > 0) {
                // 交换数据
                char name[MAX_NAME], password[MAX_PWD], id[MAX_ID];
                char gender;
                Date birth;
                float math, chinese, english;
                
                strcpy(name, p->name); strcpy(p->name, p->next->name); strcpy(p->next->name, name);
                strcpy(password, p->password); strcpy(p->password, p->next->password); strcpy(p->next->password, password);
                strcpy(id, p->id); strcpy(p->id, p->next->id); strcpy(p->next->id, id);
                gender = p->gender; p->gender = p->next->gender; p->next->gender = gender;
                birth = p->birth; p->birth = p->next->birth; p->next->birth = birth;
                math = p->math; p->math = p->next->math; p->next->math = math;
                chinese = p->chinese; p->chinese = p->next->chinese; p->next->chinese = chinese;
                english = p->english; p->english = p->next->english; p->next->english = english;
            }
            p = p->next;
        }
        tail = p;
    }
}

// 按总分降序排序
void student_model_sort_by_total(Student* head)
{
    if(head == NULL || head->next == NULL || head->next->next == NULL) return;
    
    Student *p, *tail = NULL;
    while(head->next != tail) {
        p = head->next;
        while(p->next != tail) {
            float total1 = p->math + p->chinese + p->english;
            float total2 = p->next->math + p->next->chinese + p->next->english;
            if(total1 < total2) {
                // 交换数据
                char name[MAX_NAME], password[MAX_PWD], id[MAX_ID];
                char gender;
                Date birth;
                float math, chinese, english;
                
                strcpy(name, p->name); strcpy(p->name, p->next->name); strcpy(p->next->name, name);
                strcpy(password, p->password); strcpy(p->password, p->next->password); strcpy(p->next->password, password);
                strcpy(id, p->id); strcpy(p->id, p->next->id); strcpy(p->next->id, id);
                gender = p->gender; p->gender = p->next->gender; p->next->gender = gender;
                birth = p->birth; p->birth = p->next->birth; p->next->birth = birth;
                math = p->math; p->math = p->next->math; p->next->math = math;
                chinese = p->chinese; p->chinese = p->next->chinese; p->next->chinese = chinese;
                english = p->english; p->english = p->next->english; p->next->english = english;
            }
            p = p->next;
        }
        tail = p;
    }
}

// 保存到文件
void student_model_save_to_file(Student* head)
{
    FILE* fp = fopen("./student.dat", "w");
    if(fp == NULL) return;
    
    Student* p = head->next;
    while(p != NULL) {
        fprintf(fp, "%s %s %s %c %d %d %d %.2f %.2f %.2f\n",
                p->name, p->password, p->id, 
                p->gender, 
                p->birth.year, p->birth.month, p->birth.day,
                p->math, p->chinese, p->english);
        p = p->next;
    }
    
    fclose(fp);
}

// 从文件加载
Student* student_model_load_from_file(void)
{
    Student* head = student_model_create_empty_list();
    if(head == NULL) return NULL;
    
    FILE* fp = fopen("./student.dat", "r");
    if(fp == NULL) return head;
    
    char name[MAX_NAME], password[MAX_PWD], id[MAX_ID];
    char gender;
    Date birth;
    float math, chinese, english;
    
    while(fscanf(fp, "%s %s %s %c %d %d %d %f %f %f", 
                 name, password, id, &gender, 
                 &birth.year, &birth.month, &birth.day,
                 &math, &chinese, &english) != EOF) {
        student_model_add(&head, name, password, id, gender, birth, math, chinese, english);
    }
    
    fclose(fp);
    return head;
}