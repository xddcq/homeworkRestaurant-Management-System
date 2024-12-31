#pragma once
namespace administrator
{
	using namespace std;
	void test()
	{
		while (1) {
			cout << "请选择你需要调试的模块" << endl;
			cout << "1、厨师模块" << endl;
			cout << "2、服务员模块" << endl;
			cout << "3、顾客模块" << endl;
			cout << "4、老板模块" << endl;
			cout << "5、收营员模块" << endl;
			cout << "0:返回上一级"<<endl;
			int n = ::int_input(5);
			system("cls");
			switch (n)
			{
			case 1:cook::cook(); break;
			case 2:server::server(); break;
			case 3:costomer::customer(); break;
			case 4: ; break;
			case 5: cashier::cashier(); break;
			case 0:return;
			default: break;
			}
			system("cls");
		}
	}
}