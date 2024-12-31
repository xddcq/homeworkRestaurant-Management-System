#pragma once
#include"调试功能模块.h"
namespace administrator
{
	using namespace std;
	void admin()
	{
		sys::password("管理员");
		while (1) {
			cout << "请选择你需要修改的密码" << endl;
			cout << "1、修改厨师密码" << endl;
			cout << "2、修改老板密码" << endl;
			cout << "3、修改服务员密码" << endl;
			cout << "4、修改管理员密码" << endl;
			cout << "5、修改收营员密码" << endl;
			int n = ::int_input(5);
			switch (n)
			{
			case 1:sys::cpass1("厨师"); break;
			case 2:sys::cpass1("老板"); break;
			case 3:sys::cpass1("服务员"); break;
			case 4:sys::cpass1("管理员"); break;
			case 5:sys::cpass1("收营员"); break;
			case 0:return;
			default: break;
			}
			system("cls");
		}
	}
}
