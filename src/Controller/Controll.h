#pragma once
#include"app.h"
#include"User.h"
#include"Manager.h"

void Controller() {
	int choice = 1;
	while (choice) {
		setColor(14); // 亮黄色
		printf("欢迎使用图书管理系统！\n");
		printf("请选择操作：\n");
		printf("1. 登录账号\n");
		printf("2. 注册账号\n");
		int choice;
		scanf_s("%d", &choice);
		if (choice == 1) {
			int role;
			role=AccountLogin();
			if(role==0){
				User();
			}
			else if(role==1){
				Manager();
			}
			else
				printf("登录失败！请检查账号和密码是否正确。\n");
		}
		else if (choice == 2) {
			if(AccountRegister())
				printf("注册成功！\n");
			else
				printf("注册失败！请检查输入信息是否有效或账号是否已存在。\n");
		}
		else {
			printf("无效的选择！\n");
			return;
		}
	}
};
