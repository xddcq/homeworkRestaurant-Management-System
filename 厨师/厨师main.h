#pragma once
#include"厨师.h"
namespace cook
{
	using namespace std;
	void cook()
	{
		sys::password("厨师");
		while(true)
		{
			cout << "请选择你要需要的功能" << endl;
			cout << "1：出菜" << endl;
			cout << "2：修改菜品状态（修改是否售罄）" << endl;
			cout << "3:修改密码" << endl;
			cout << "0：返回上一级" << endl;
			int n = int_input(3);
			switch (n)
			{
			case 1:cooker_cook(); break;
			case 2:changemunu("数据存储/menu.txt"); break;
			case 3:sys::cpass2("厨师");
			case 0:return;
			default: break;
			}
		}
	}
}