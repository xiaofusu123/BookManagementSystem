#include"tou.h"
#include"../service/BookService.h"
#include"../service/BorrowRecordService.h"
#include"../service/AccountService.h"
#include"../service/BillService.h"

void SearchBy(int i) {
	char keyword[MAXSIZE];
	char null[MAXSIZE] = "";
	resetColor();
	fgets(keyword, sizeof(keyword), stdin);
	keyword[strcspn(keyword, "\n")] = '\0';
	resetColor();
	if (i == 1)
		Search_Book(null, keyword, null);
	else if (i == 2)
		Search_Book(null, null, keyword);
	else
		Search_Book(keyword, null, null);
	resetColor();
}

// 搜索图书功能
void UserSearch() {
	setColor(11); // 淡蓝紫
	printf("图书搜索小助手 \n");

	setColor(14);  // 亮黄色
	printf("请选择搜索维度：\n");
	printf("   1. 书名\n  2. 作者\n   3. 类型\n  4.所有书籍\n");
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
		SearchBy(1);
		break;
	}
	case 2: {
		setColor(13); // 粉色
		printf("请输入要搜索的作者：");
		SearchBy(2);
		break;
	}
	case 3: {
		setColor(13); // 粉色
		printf("请输入要搜索的类型：");
		SearchBy(3);
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


// 借阅图书功能
void UserBorrow(int account) {
	setColor(11); // 淡蓝紫
	printf("图书借阅小窗口        \n");
	setColor(14);  // 亮黄色
	printf("提示：输入图书编号，输入0退出借阅～\n");
	setColor(13); // 粉色
	printf("请输入要借阅的图书编号：");
	resetColor();

	int book_id;
	scanf("%d", &book_id);
	getchar(); // 吸收换行符

	// 功能逻辑框架
	if (book_id==0 ){
		setColor(9); // 亮蓝色
		printf("已退出借阅流程～\n");
		resetColor();
		return;
	}

	// 借阅逻辑框架
	setColor(9); // 亮蓝色
	printf("\n正在处理图书编号%d的借阅请求...\n", book_id);
	bool success = Create_Borrow_Book(account,book_id);
	if (success) {
		printf("借阅申请提交成功！\n");
		borrowrecord_t* empty = (borrowrecord_t*)malloc(sizeof(borrowrecord_t));
		empty = Search_BrrowBookAll(account);
		int i = 0;
		while (empty[i].record_id > 0) {
			printf("借阅记录编号：%d\t账号：%d\t图书编号：%d\t借阅日期：%s\t归还截止日期：%s\t借阅状态：%d\n\n",
				empty[i].record_id, empty[i].account_id, empty[i].book_id, empty[i].borrow_date, empty[i].deadline, empty[i].status);
			i++;
		}
		free(empty);
	}
	resetColor();
}

// 归还图书功能
void UserReturn(int account) {
	// 美化标题
	setColor(11); // 淡蓝紫
	printf("图书归还小驿站            \n");

	setColor(14);  // 亮黄色
	printf("你当前借阅的书籍列表：\n");
	setColor(10); // 亮绿色
	printf("提示：输入图书编号借阅，输入0退出还书～\n");
	resetColor();

	borrowrecord_t* empty = (borrowrecord_t*)malloc(sizeof(borrowrecord_t));
	empty = Search_BrrowBookAll(account);
	int i = 0;
	if(empty){
		while (empty[i].record_id>0) {
			printf("借阅记录编号：%d\t账号：%d\t图书编号：%d\t借阅日期：%s\t归还截止日期：%s\t借阅状态：%d\n\n",
				empty[i].record_id, empty[i].account_id, empty[i].book_id, empty[i].borrow_date, empty[i].deadline, empty[i].status);
			i++;
		}
			free(empty);
	}


	// 归还逻辑框架
	setColor(13); // 粉色
	printf("\n请输入要归还的记录编号：");
	resetColor();
	int return_id = 0;
	scanf("%d", &return_id);
	if (return_id == 0) {
		setColor(9); // 亮蓝色
		printf("已退出还书流程～\n");
		resetColor();
		return;
	}
	setColor(9); // 亮蓝色
	printf("\n正在处理图书编号%d的归还请求...\n", return_id);
	bool success = ReturnBook(return_id);

	printf("归还申请提交成功！可在此处补充归还结果～\n");
	resetColor();
}

// 购买图书功能
void UserBuy(int account) {
	setColor(11); // 淡蓝紫
	printf("图书购买小窗口           \n");

	setColor(14);  // 亮黄色
	printf("提示：输入图书编号购买，输入0退出购买～\n");

	int number = 0;
	scanf("%d", &number);
	getchar(); // 吸收换行符
	if (number == 0) {
		setColor(9); // 亮蓝色
		printf("已退出购买流程～\n");
		resetColor();
		return;
	}

	printf("提示：输入图书数量购买，输入0退出购买～\n");

	int num = 0;
	scanf("%d", &num);
	getchar(); // 吸收换行符
	if (number == 0) {
		setColor(9); // 亮蓝色
		printf("已退出购买流程～\n");
		resetColor();
		return;
	}


	bool success = Create_Bill(account,number,num);

	if (success) {
		setColor(10); // 亮绿色
		printf("购买成功!\n");
	}
	else {
		setColor(12); // 红色
		printf("购买失败！请确定图书编号是否存在或数量超出～\n");
	}

}

// 充值余额功能
void Userrecharge(int account) {
	setColor(11); // 淡蓝紫
	printf("充值小窗口             \n");

	float number = 0;
	setColor(14);  // 亮黄色
	printf("提示：输入充值金额，输入0退出充值～\n");
	scanf("%f", &number);

	if (number <= 0.00f) {
		setColor(9); // 亮蓝色
		printf("已退出充值流程～\n");
		resetColor();
		return;
	}
	bool success = Recharge(account, number);
	if (success) {
		setColor(10); // 亮绿色
		printf("充值成功！您的账户已增加 %.2f 元～\n", number);
	}
	else {
		setColor(12); // 红色
		printf("充值失败！请检查账户信息或网络连接～\n");
	}

}

// 用户菜单选择处理
void UserMenu(int number,int account) {
	switch (number) {
	case 1:
		UserSearch();
		break;
	case 2:
		UserBorrow(account);
		break;
	case 3:
		UserReturn(account);
		break;
	case 4:
		UserBuy(account);
		break;
	case 5:
		Userrecharge(account);
		break;
	default:
		setColor(12); // 红色
		printf("无效的选项！请选择0~5～\n");
		resetColor();
	}
}

// 用户界面主函数
void User(int account) {
	int number = 0;
	while (1) {
		setColor(7);
		printf("您的余额是：%.2f\n", Check_Balance(account));

		// 可爱的用户界面标题（字符画+彩色）
		setColor(11);  // 淡蓝紫色
		printf("欢迎来到用户图书小天地   \n");
		printf("这里可以轻松管理图书哦～ \n");

		// 功能菜单（彩色+可爱符号）
		setColor(10);  // 亮绿色
		printf("【你的专属图书功能】\n");
		setColor(14);  // 亮黄色
		printf("  1. 查询图书  -> 看看有什么有趣的书～\n");
		printf("  2. 借阅图书  -> 把喜欢的书抱回家～\n");
		printf("  3. 归还图书  -> 记得把书送回来哦～\n");
		printf("  4. 购买书籍  -> 余额要多余书籍价格～ \n");
		printf("  5. 充值余额  -> 充值余额可购买书籍～ \n");
		printf("  0. 退出系统  -> 退出系统，欢迎下次再来～\n\n");

		// 选择提示（温柔语气）
		setColor(13);  // 粉色
		printf("请输入数字选择功能（0/1/2/3/4/5）：");
		setColor(7);   // 恢复默认白色
		scanf("%d", &number);
		if (number == 0)
			return;
		system("cls");
		UserMenu(number,account);
	}
}

