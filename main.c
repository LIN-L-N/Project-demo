#include "controller/controller.h"
#include <windows.h>

int main()
{
    // 设置控制台编码为UTF-8，支持中文显示
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    
    controller_main_menu();
    return 0;
}