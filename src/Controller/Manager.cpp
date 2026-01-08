#include"Manager.h"
#include"../service/BookService.h"


void Manager() {
    int choice = 0;
    // 循环显示管理员界面，直到退出
    while (1) {
        system("cls");
        // 可爱的管理员界面标题
        setColor(11);  // 淡蓝紫色
        printf("这里可以轻松管理图书哦～ \n");
        // 功能菜单（彩色+可爱符号）
        setColor(10);  // 亮绿色
        printf("【管理员专属图书功能】\n");
        setColor(14);  // 亮黄色
        printf("  1. 查询图书  -> 查看图书信息\n");
        printf("  2. 添加图书  -> 增加新书到库存\n");
        printf("  3. 删除图书  -> 移除不需要的书籍\n");
        printf("  4. 更新图书  -> 修改已有的图书信息\n");
        printf("  0. 退出管理  -> 返回上一级～\n\n");
        // 选择提示（温柔语气）
        setColor(13);  // 粉色
        printf("请输入数字选择功能（0/1/2/3/4）：");
        resetColor();

        // 读取用户选择
        scanf("%d", &choice);
        getchar();// 吸收换行符
        ManagerMenu(choice);
        if (choice == 0)
            return;

        // 功能执行完后，等待用户确认再返回主界面
        setColor(10);
        printf("按任意键返回管理员主界面...");
        resetColor();
        getchar(); // 等待输入
    }
}

void ManagerSearch() {
    setColor(11); // 淡蓝紫
    printf("图书搜索小助手 \n");

    setColor(14);  // 亮黄色
    printf("请选择搜索维度：\n");
    printf("   1. 书名\n  2. 作者\n   3. 类型\n    4.所有书籍\n  ");
    setColor(10); // 亮绿色
    printf("请输入数字（1/2/3/4）：");
    resetColor();

    int number = 0;
    scanf("%d", &number);
    getchar(); // 吸收换行符

    // 功能逻辑框架
    switch (number) {
    case 1: {
        setColor(13); // 粉色
        printf("请输入要搜索的书名：");
        SearchByKey(1);
        break;
    }
    case 2: {
        setColor(13); // 粉色
        printf("请输入要搜索的作者：");
        SearchByKey(2);
        break;
    }
    case 3: {
        setColor(13); // 粉色
        printf("请输入要搜索的类型："); 
        SearchByKey(3); 
        break; 
    }
    case 4:SearchAll(); break;
    default:
        setColor(12); // 红色
        printf("无效的搜索选项！请选择1、2或3～\n");
        resetColor();
        return;
    }
}

// 添加图书（完整交互界面）
void ManagerADD() {
    char book_name[MAXSIZE], author[MAXSIZE], type[MAXSIZE];
    int book_id = 0;
	float price = 0.0f;
	int total = 0;


    setColor(11); // 淡蓝紫
    printf("图书添加小助手\n");

    setColor(14); // 亮黄色
    printf("请输入新增图书的信息（按提示填写）～\n");
    setColor(10); // 亮绿色
    resetColor();

    // 输入图书编号
    setColor(13); // 粉色
    printf("图书编号：");
    resetColor();
    scanf("%d", &book_id);
    getchar(); // 吸收换行

    // 输入书名
    setColor(13);
    printf("图书名称：");
    resetColor();
    fgets(book_name, sizeof(book_name), stdin);
    book_name[strcspn(book_name, "\n")] = '\0';


    //输入价格
    setColor(13);
    printf("图书价格：");
    resetColor();
	scanf("%f", &price);
	getchar(); // 吸收换行


	//输入总量
	setColor(13);
	printf("图书总量：");
	resetColor();
	scanf("%d", &total);
	getchar(); // 吸收换行

    // 输入作者
    setColor(13);
    printf("作者姓名：");
    resetColor();
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = '\0';

    // 输入类型
    setColor(13);
    printf("图书类型：");
    resetColor();
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = '\0';


	//输入出版日期
	setColor(13);
	printf("出版日期：");
	resetColor();
	char publish_date[MAXSIZE];
	fgets(publish_date, sizeof(publish_date), stdin);
	publish_date[strcspn(publish_date, "\n")] = '\0';

    // 确认添加
    setColor(9); // 亮蓝色
    printf("你要添加的图书信息：\n");
    printf("   编号：%d\n   书名：%s\n   价格：%f\n   总量：%d\n   类型：%s\n   作者：%s\n   出版时间：%s\n", 
        book_id, book_name,price, total, type,author,publish_date);
    printf("是否确认添加？（输入y确认，其他取消）：");
    resetColor();

    char confirm = 'n';
    scanf(" %c", &confirm); // 空格吸收换行

    if (confirm == 'y' || confirm == 'Y') {
        setColor(9);
		bool success = Create_Book(book_id, book_name, price, total, 0, type, author, publish_date);// 调用添加服务
        if (success) {
            printf("\n编号 %d 的《%s》已在库中～\n", book_id, book_name);
            resetColor();
        }
        else
            printf("添加失败\n");
    }
    else {
        setColor(12);
        printf("\n已取消图书添加操作～\n");
        resetColor();
    }
}

// 删除图书（完整交互界面）
void ManagerRemove() {
    int book_id = 0;

    setColor(11); // 淡蓝紫
    printf("图书删除小助手 \n");

    setColor(14); // 亮黄色
    printf("警告：删除后图书信息将无法恢复～\n");
    setColor(10); // 亮绿色
    resetColor();

    // 输入要删除的图书编号
    setColor(13); // 粉色
    printf("请输入要删除的图书编号：");
    resetColor();
    scanf("%d", &book_id);

    // 确认删除
    setColor(9); // 亮蓝色
    printf("是否确认删除编号%d的图书？（输入y确认，其他取消）：", book_id);
    resetColor();

    char confirm = 'n';
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        setColor(9);
		Delete_Book(book_id); // 调用删除服务
        printf("\n图书删除成功！编号%d的图书已移出库存～\n", book_id);
        resetColor();
    }
    else {
        setColor(12);
        printf("\n已取消图书删除操作～\n");
        resetColor();
    }
}

// 更新图书（完整交互界面）
void ManagerUpdate() {
    char book_name[MAXSIZE], author[MAXSIZE], type[MAXSIZE];
    int book_id = 0;
    float price = 0.0f;
    int total = 0,borrow=0;

    setColor(11); // 淡蓝紫
    printf("图书更新小助手\n");

    // 输入图书编号
    setColor(13); // 粉色
    printf("图书编号：");
    resetColor();
    scanf("%d", &book_id);
    getchar(); // 吸收换行

    // 输入书名
    setColor(13);
    printf("图书名称：");
    resetColor();
    fgets(book_name, sizeof(book_name), stdin);
    book_name[strcspn(book_name, "\n")] = '\0';


    //输入价格
    setColor(13);
    printf("图书价格：");
    resetColor();
    scanf("%f", &price);
    getchar(); // 吸收换行


    //输入总量
    setColor(13);
    printf("图书总量：");
    resetColor();
    scanf("%d", &total);
    getchar(); // 吸收换行


    setColor(13);
    printf("图书借出数量：");
    resetColor();
    scanf("%d", &borrow);
    getchar(); // 吸收换行

    // 输入作者
    setColor(13);
    printf("作者姓名：");
    resetColor();
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = '\0';

    // 输入类型
    setColor(13);
    printf("图书类型：");
    resetColor();
    fgets(type, sizeof(type), stdin);
    type[strcspn(type, "\n")] = '\0';


    //输入出版日期
    setColor(13);
    printf("出版日期：");
    resetColor();
    char publish_date[MAXSIZE];
    fgets(publish_date, sizeof(publish_date), stdin);
    publish_date[strcspn(publish_date, "\n")] = '\0';

    setColor(9); // 亮蓝色
    printf("你修改后的图书信息：\n");
    printf("   编号：%d\n   书名：%s\n   价格：%f\n   总量：%d\n   借出数：%d\n   类型：%s\n   作者：%s\n   出版时间：%s\n",
        book_id, book_name, price, total, borrow,type, author, publish_date);
    printf("是否确认添加？（输入y确认，其他取消）：");
    resetColor();

    char confirm = 'n';
    scanf(" %c", &confirm); // 空格吸收换行

    if (confirm == 'y' || confirm == 'Y') {
        setColor(9);
        Revise_Book(book_id,book_name,price,total,borrow,type,author,publish_date); // 调用添加服务
        printf("\n图书更新成功！编号 %d 的《%s》已入库～\n", book_id, book_name);
        resetColor();
    }
    else {
        setColor(12);
        printf("\n已取消图书更新操作～\n");
        resetColor();
    }

    resetColor();
}

void ManagerMenu(int choice) {
    // 根据选择跳转对应功能
    switch (choice) {
    case 1:
        ManagerSearch(); // 调用查询功能
        break;
    case 2:
        ManagerADD(); // 调用添加功能
        break;
    case 3:
        ManagerRemove(); // 调用删除功能
        break;
    case 4:
        ManagerUpdate(); // 调用更新功能
        break;
    case 0:
        setColor(9); // 亮蓝色
        printf("\n已退出管理员界面，欢迎下次使用\n");
        resetColor();
        return; // 退出管理员界面
    default:
        setColor(12); // 红色
        printf("\n无效的选项！请输入0-4之间的数字\n");
        resetColor();
        break;
    }
}

void SearchByKey(int i) {
    char keyword[MAXSIZE];
	char null[MAXSIZE] = "";
    resetColor();
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0';
    resetColor(); // 亮蓝色
    if (i == 1)
        Search_Book(null, keyword, null);
	else if (i == 2)
        Search_Book(null,null,keyword);
    else
        Search_Book(keyword,null,null);

    resetColor();
}
