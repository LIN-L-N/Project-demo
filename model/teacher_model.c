#include "teacher_model.h"

// 创建空表
Teacher* teacher_model_create_empty_list(void)
{
    Teacher* head = (Teacher*)malloc(sizeof(Teacher));
    if(head != NULL) {
        head->next = NULL;
    }
    return head;
}

// 销毁整个链表
void teacher_model_destroy_list(Teacher** head)
{
    if(head == NULL || *head == NULL) return;
    
    Teacher* p = *head;
    Teacher* next;
    while(p != NULL) {
        next = p->next;
        free(p);
        p = next;
    }
    *head = NULL;
}

// 创建一个新节点
Teacher* teacher_model_create_node(const char* name, const char* password, const char* id, 
                                   char gender, Date birth)
{
    Teacher* node = (Teacher*)malloc(sizeof(Teacher));
    if(node == NULL) return NULL;
    
    strcpy(node->name, name);
    strcpy(node->password, password);
    strcpy(node->id, id);
    node->gender = gender;
    node->birth = birth;
    node->next = NULL;
    
    return node;
}

// 销毁一个指定节点
void teacher_model_destroy_node(Teacher* node)
{
    if(node != NULL) {
        free(node);
    }
}

// 增加教师
int teacher_model_add(Teacher** head, const char* name, const char* password, const char* id, 
                      char gender, Date birth)
{
    if(head == NULL || *head == NULL) return -1;
    
    // 检查工号是否重复
    if(teacher_model_find_by_id(*head, id) != NULL) {
        return -2; // 工号重复
    }
    
    Teacher* new_node = teacher_model_create_node(name, password, id, gender, birth);
    if(new_node == NULL) return -1;
    
    // 头插法
    new_node->next = (*head)->next;
    (*head)->next = new_node;
    
    return 0;
}

// 删除教师（按工号）
int teacher_model_delete_by_id(Teacher** head, const char* id)
{
    if(head == NULL || *head == NULL || (*head)->next == NULL) return -1;
    
    Teacher* p = *head;
    Teacher* prev = *head;
    
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

// 查找教师（按工号）
Teacher* teacher_model_find_by_id(Teacher* head, const char* id)
{
    if(head == NULL) return NULL;
    
    Teacher* p = head->next;
    while(p != NULL) {
        if(strcmp(p->id, id) == 0) {
            return p;
        }
        p = p->next;
    }
    
    return NULL;
}

// 查找教师（按姓名和密码）
Teacher* teacher_model_find_by_name_pwd(Teacher* head, const char* name, const char* password)
{
    if(head == NULL) return NULL;
    
    Teacher* p = head->next;
    while(p != NULL) {
        if(strcmp(p->name, name) == 0 && strcmp(p->password, password) == 0) {
            return p;
        }
        p = p->next;
    }
    
    return NULL;
}

// 修改教师信息
int teacher_model_modify(Teacher* head, const char* id, const char* new_name, 
                         const char* new_password, char new_gender, Date new_birth)
{
    Teacher* teacher = teacher_model_find_by_id(head, id);
    if(teacher == NULL) return -1;
    
    if(new_name != NULL) strcpy(teacher->name, new_name);
    if(new_password != NULL) strcpy(teacher->password, new_password);
    teacher->gender = new_gender;
    teacher->birth = new_birth;
    
    return 0;
}

// 显示所有教师
void teacher_model_display_all(Teacher* head)
{
    if(head == NULL || head->next == NULL) {
        printf("暂无教师信息\n");
        return;
    }
    
    Teacher* p = head->next;
    while(p != NULL) {
        printf("工号:%s\t姓名:%s\t性别:%c\t生日:%d-%d-%d\n",
               p->id, p->name, p->gender, 
               p->birth.year, p->birth.month, p->birth.day);
        p = p->next;
    }
}

// 保存到文件
void teacher_model_save_to_file(Teacher* head)
{
    FILE* fp = fopen("./teacher.dat", "w");
    if(fp == NULL) return;
    
    Teacher* p = head->next;
    while(p != NULL) {
        fprintf(fp, "%s %s %s %c %d %d %d\n",
                p->name, p->password, p->id, 
                p->gender, 
                p->birth.year, p->birth.month, p->birth.day);
        p = p->next;
    }
    
    fclose(fp);
}

// 从文件加载
Teacher* teacher_model_load_from_file(void)
{
    Teacher* head = teacher_model_create_empty_list();
    if(head == NULL) return NULL;
    
    FILE* fp = fopen("./teacher.dat", "r");
    if(fp == NULL) return head;
    
    char name[MAX_NAME], password[MAX_PWD], id[MAX_ID];
    char gender;
    Date birth;
    
    while(fscanf(fp, "%s %s %s %c %d %d %d", 
                 name, password, id, &gender, 
                 &birth.year, &birth.month, &birth.day) != EOF) {
        teacher_model_add(&head, name, password, id, gender, birth);
    }
    
    fclose(fp);
    return head;
}