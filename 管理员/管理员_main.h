#pragma once
#include"调试功能模块.h"
#include"管理账号.h"
namespace administrator
{
	using namespace std;
	void administrator()
	{
		sys::password("管理员");
		while (1) {
			cout << "请选择你需要的功能" << endl;
			cout << "1、订单生成小票" << endl;
			cout << "2、订单添加菜品" << endl;
			cout << "3、订单删除菜品" << endl;
			cout << "4、修改菜品状态（是否售罄）" << endl;
			cout << "5、统计小票数据" << endl;
			cout << "6、修改餐桌状态" << endl;
			cout << "7、修改菜单" << endl;
			cout << "8、展示建议" << endl;
			cout << "9、展示投诉" << endl;
			cout << "10、调试功能模块" << endl;
			cout << "11、设置餐位费" << endl;
			cout << "12、修改密码" << endl;
			cout << "0、返回上一级" << endl;

			int n = ::int_input(11);
			switch (n)
			{
			case 1:cashier::cashier_recipet(); break;
			case 2:server::serveradd(); break;
			case 3:server::serverDelete(); break;
			case 4: ::changemunu("数据存储/menu.txt"); break;
			case 5: sys::analyzeReceipts("数据存储/小票存储/"); break;
			case 6:sys::manageTables(); break;
			case 7:sys::change_menu(); break;
			case 8: ::readSuggestions(); break;
			case 9: ::readComplaints(); break;
			case 10:test(); break;
			case 11:set_feel(); break;
			case 12:admin(); break;
			case 0:return;
			default: break;
			}
			system("cls");
		}
	}
	void set_feel()
	{
		cout << "请输入你要设置的餐位费";
		int n = ::int_input();
		cout << "设置成功";
		::writeNumberToFile("数据存储/餐位费.txt",n);
	}
}
