#pragma once
#include"��ʦ.h"
namespace cook
{
	using namespace std;
	void cook()
	{
		sys::password("��ʦ");
		while(true)
		{
			cout << "��ѡ����Ҫ��Ҫ�Ĺ���" << endl;
			cout << "1������" << endl;
			cout << "2���޸Ĳ�Ʒ״̬���޸��Ƿ�������" << endl;
			cout << "3:�޸�����" << endl;
			cout << "0��������һ��" << endl;
			int n = int_input(3);
			switch (n)
			{
			case 1:cooker_cook(); break;
			case 2:changemunu("���ݴ洢/menu.txt"); break;
			case 3:sys::cpass2("��ʦ");
			case 0:return;
			default: break;
			}
		}
	}
}