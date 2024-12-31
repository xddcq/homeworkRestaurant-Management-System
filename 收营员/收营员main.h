#pragma once
#include"收营员结算小票.h"
namespace cashier
{
	
	void cashier()
	{
		sys::password("收营员");
		while(1){
			cout << "请选择你需要的功能" << endl;
			cout << "1、订单结算并生成小票" << endl;
			cout << "2、订单添加菜品" << endl;
			cout << "3、订单删除菜品" << endl;
			cout << "4、修改菜品状态（是否售罄）" << endl;
			cout << "5、统计小票数据" << endl;
			cout << "6、修改餐桌状态"<<endl;
			cout << "7、修改密码" << endl;
			cout << "0、退出程序" << endl;

			int n = ::int_input(7);
			switch (n)
			{
			case 1:cashier_recipet(); break;
			case 2:server::serveradd(); break;
			case 3:server::serverDelete(); break;
			case 4: ::changemunu("数据存储/menu.txt"); break;
			case 5: sys::analyzeReceipts("数据存储/小票存储/"); break;
			case 6:sys::manageTables(); break;
			case 7:sys::cpass2("收营员"); break;
			case 0:return;
			default: break;
			}
			system("cls");
		}
	}
}