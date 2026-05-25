#include "view.h"

// 打印标题
void view_print_title(const char* title)
{
    printf("\n");
    printf("——————————————————————————————————\n");
    printf("| %-36s |\n", title);
    printf("——————————————————————————————————\n");
}

// 打印菜单
void view_print_menu(const char* title, const char** items, int count)
{
    view_print_title(title);
    for(int i = 0; i < count; i++) {
        printf("|%d、%-35s|\n", i + 1, items[i]);
        printf("——————————————————————————————————\n");
    }
}

// 获取整数输入
int view_get_int(const char* prompt)
{
    int value;
    int result;
    while(1) {
        printf("%s", prompt);
        result = scanf("%d", &value);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);  // 清空缓冲区
        if(result == 1) {
            break;
        }
        printf("输入无效，请输入整数：");
    }
    return value;
}

// 获取字符串输入
void view_get_string(const char* prompt, char* dest, int max_len)
{
    printf("%s", prompt);
    fgets(dest, max_len, stdin);
    // 移除换行符
    int len = strlen(dest);
    if(len > 0 && dest[len - 1] == '\n') {
        dest[len - 1] = '\0';
    }
}

// 打印成功消息
void view_print_success(const char* message)
{
    printf("✓ %s\n", message);
}

// 打印错误消息
void view_print_error(const char* message)
{
    printf("✗ %s\n", message);
}

// 打印普通信息
void view_print_info(const char* message)
{
    printf("%s\n", message);
}

// 暂停等待
void view_pause(void)
{
    printf("按任意键继续...\n");
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);  // 先清空缓冲区
    getchar();  // 等待用户输入一个字符
}