#include "admin_model.h"

// 从文件读取管理员信息
Admin admin_model_read(void)
{
    FILE* fp = fopen("./admin.dat", "r");
    Admin admin;
    
    if(fp != NULL) {
        fscanf(fp, "%s %s", admin.name, admin.password);
        fclose(fp);
    } else {
        // 默认管理员账号
        strcpy(admin.name, "admin");
        strcpy(admin.password, "admin123");
        admin_model_write(admin);
    }
    
    return admin;
}

// 将管理员信息写入文件
void admin_model_write(Admin admin)
{
    FILE* fp = fopen("./admin.dat", "w");
    if(fp != NULL) {
        fprintf(fp, "%s %s\n", admin.name, admin.password);
        fclose(fp);
    }
}

// 验证管理员登录
int admin_model_verify(Admin admin, const char* input_name, const char* input_pwd)
{
    return (strcmp(admin.name, input_name) == 0 && strcmp(admin.password, input_pwd) == 0);
}

// 修改管理员密码
void admin_model_modify_password(Admin* admin, const char* new_password)
{
    strcpy(admin->password, new_password);
    admin_model_write(*admin);
}