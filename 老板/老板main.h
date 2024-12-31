#pragma once
namespace boss
{
	using namespace std;
	void boss()
	{
		sys::password("老板");
		while (1) {
			cout << "请选择你需要的功能" << endl;
			cout << "1、订单生成小票" << endl;
			cout << "2、订单添加菜品" << endl;
			cout << "3、订单删除菜品" << endl;
			cout << "4、修改菜品状态（是否售罄）" << endl;
			cout << "5、统计数据" << endl;
			cout << "6、修改餐桌状态" << endl;
			cout << "7、修改菜单" << endl;
			cout << "8、展示建议" << endl;
			cout << "9、展示投诉" << endl;
			cout << "10、修改密码" << endl;
			cout << "0、返回上一级" << endl;

			int n = ::int_input(10);
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
			case 10: sys::cpass2("老板"); break;
			case 0:return;
			default: break;
			}
			system("cls");
		}
	}
}