#include"app.h"
#include "../service/AccountService.h"


int AccountLogin() {
    setColor(11);  // 淡蓝紫色
    printf("|这里要输入账号和密码呦～ \n");

    int account;
    char password[MAXSIZE];  // 替换原char* password（避免野指针）
    setColor(14); // 亮黄色
    // 1. 输入账号
    printf("请输入账号：");
    scanf("%ld", &account);

    // 2. 输入密码（处理缓冲区换行）
    getchar();  // 吸收账号输入后的换行
    printf("请输入密码：");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';  // 去掉换行符

	int status = Login(account, password);  // 调用实际的登录逻辑

    if (status == 1) {
        printf("管理员登录成功！\n");
    }
    else if (status == 0) {
        printf("用户登录成功！\n");
    }
    else {
        printf("账号或密码错误！\n");
    }
    return status;  // 函数是int类型，必须返回值
}


bool AccountRegister() {
    setColor(11);  // 淡蓝紫色
    printf("|  欢迎来到新用户的加入    \n");
    printf("|  这里请按提示规范输入呦～ \n");
    int account;
    char password[MAXSIZE];
	char phone[MAXSIZE];

    setColor(14); // 亮黄色
    printf("请输入要注册的账号：");
    scanf("%ld", &account);

    getchar();  // 吸收账号输入后的换行
    printf("请输入要注册的密码：");
    fgets(password, sizeof(password), stdin);    
    
    printf("请输入要注册的手机：");
    fgets(phone, sizeof(phone), stdin);

    password[strcspn(password, "\n")] = '\0';// 去掉换行符


	setColor(10);  // 亮绿色
    bool Success = false;
    int choice = 1;
    printf("输入0添加用户，输入1添加管理员\n");
	scanf_s("%d", &choice);
    if(choice == 0)
	    Success = Register(account, password, 0.00, phone, 0);  // 默认余额0，手机号占位，0用户||1管理员
    else
        Success = Register(account, password, 0.00, phone, 1);  // 默认余额0，手机号占位，0用户||1管理员

    return Success;
}