#include"tou.h"


// 搜索图书功能
void UserSearch() {
	char keyword[MAXSIZE];
	setColor(11); // 淡蓝紫
	printf("图书搜索小助手            \n");

	setColor(14);  // 亮黄色
	printf("请选择搜索维度：\n");
	printf("  1. 书名\n  2. 作者\n  3. 类型\n");
	setColor(10); // 亮绿色
	printf("请输入数字（1/2/3）：");
	resetColor();

	int number = 0;
	scanf("%d", &number);
	getchar(); // 吸收换行符

	// 功能逻辑框架
	switch (number) {
	case 1: {
		setColor(13); // 粉色
		printf("请输入要搜索的书名：");
		resetColor();
		fgets(keyword, sizeof(keyword), stdin);
		keyword[strcspn(keyword, "\n")] = '\0';
		// 按书名搜索的逻辑框架
		setColor(9); // 亮蓝色
		printf("\n正在搜索书名包含「%s」的图书...\n", keyword);
		// 此处可对接实际的图书数据查询逻辑
		printf("搜索完成！可在此处展示匹配的图书列表～\n");
		resetColor();
		break;
	}
	case 2: {
		setColor(13); // 粉色
		printf("请输入要搜索的作者：");
		resetColor();
		fgets(keyword, sizeof(keyword), stdin);
		keyword[strcspn(keyword, "\n")] = '\0';
		// 按作者搜索的逻辑框架
		setColor(9); // 亮蓝色
		printf("\n正在搜索作者为「%s」的图书...\n", keyword);
		// 此处可对接实际的图书数据查询逻辑
		printf("搜索完成！可在此处展示匹配的图书列表～\n");
		resetColor();
		break;
	}
	case 3: {
		setColor(13); // 粉色
		printf("请输入要搜索的类型：");
		resetColor();
		fgets(keyword, sizeof(keyword), stdin);
		keyword[strcspn(keyword, "\n")] = '\0';
		// 按类型搜索的逻辑框架
		setColor(9); // 亮蓝色
		printf("\n正在搜索类型为「%s」的图书...\n", keyword);
		// 此处可对接实际的图书数据查询逻辑
		printf("搜索完成！可在此处展示匹配的图书列表～\n");
		resetColor();
		break;
	}
	default:
		setColor(12); // 红色
		printf("无效的搜索选项！请选择1、2或3～\n");
		resetColor();
		return;
	}
}

// 借阅图书功能
void UserBorrow() {
	setColor(11); // 淡蓝紫
	printf("图书借阅小窗口        \n");

	setColor(14);  // 亮黄色
	printf("提示：输入图书编号借阅，输入0退出借阅～\n");
	setColor(13); // 粉色
	printf("请输入要借阅的图书编号：");
	resetColor();

	int book_id = 0;
	scanf("%d", &book_id);

	// 功能逻辑框架
	if (book_id == 0) {
		setColor(9); // 亮蓝色
		printf("已退出借阅流程～\n");
		resetColor();
		return;
	}
	// 借阅逻辑框架
	setColor(9); // 亮蓝色
	printf("\n正在处理图书编号%d的借阅请求...\n", book_id);
	// 此处可对接实际的借阅校验逻辑（如是否可借、库存等）




	printf("借阅申请提交成功！可在此处补充借阅结果～\n");
	resetColor();
}

// 归还图书功能
void UserReturn() {
	// 美化标题
	setColor(11); // 淡蓝紫
	printf("图书归还小驿站            \n");

	setColor(14);  // 亮黄色
	printf("你当前借阅的书籍列表：\n");
	setColor(10); // 亮绿色
	printf("提示：输入图书编号借阅，输入0退出还书～\n");
	resetColor();

	// 显示借阅列表的逻辑框架
	printf("  （可在此处循环展示用户借阅的图书编号/名称）\n");




	// 归还逻辑框架
	setColor(13); // 粉色
	printf("\n请输入要归还的图书编号：");
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
	// 此处可对接实际的归还校验逻辑


	printf("归还申请提交成功！可在此处补充归还结果～\n");
	resetColor();
}

// 购买图书功能
void UserBuy() {
	setColor(11); // 淡蓝紫
	printf("图书购买小窗口           \n");

	setColor(14);  // 亮黄色
	printf("提示：输入图书编号购买，输入0退出购买～\n");

	int number = 0;
	scanf("%d", &number);
	if (number == 0) {
		setColor(9); // 亮蓝色
		printf("已退出购买流程～\n");
		resetColor();
		return;
	}
	// 购买逻辑框架

}

// 充值余额功能
void Userrecharge() {
	setColor(11); // 淡蓝紫
	printf("充值小窗口             \n");

	int number = 0;
	setColor(14);  // 亮黄色
	printf("提示：输入充值金额，输入0退出充值～\n");
	scanf("%d", &number);


	if (number == 0) {
		setColor(9); // 亮蓝色
		printf("已退出充值流程～\n");
		resetColor();
		return;
	}
	// 充值逻辑框架

	setColor(10); // 亮绿色


}

// 用户菜单选择处理
void UserMenu(int number) {
	switch (number) {
	case 1:
		UserSearch();
		break;
	case 2:
		UserBorrow();
		break;
	case 3:
		UserReturn();
		break;
	case 4:
		UserBuy();
		break;
	case 5:
		Userrecharge();
		break;
	default:
		setColor(12); // 红色
		printf("无效的选项！请选择0~5～\n");
		resetColor();
	}
}


// 用户界面主函数
void User() {
	int number = 0;
	while (1) {
		setColor(7);
		printf("您的余额是：");
		//功能

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
		UserMenu(number);
	}
}

