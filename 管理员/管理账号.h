#pragma once
#include"���Թ���ģ��.h"
namespace administrator
{
	using namespace std;
	void admin()
	{
		sys::password("����Ա");
		while (1) {
			cout << "��ѡ������Ҫ�޸ĵ�����" << endl;
			cout << "1���޸ĳ�ʦ����" << endl;
			cout << "2���޸��ϰ�����" << endl;
			cout << "3���޸ķ���Ա����" << endl;
			cout << "4���޸Ĺ���Ա����" << endl;
			cout << "5���޸���ӪԱ����" << endl;
			int n = ::int_input(5);
			switch (n)
			{
			case 1:sys::cpass1("��ʦ"); break;
			case 2:sys::cpass1("�ϰ�"); break;
			case 3:sys::cpass1("����Ա"); break;
			case 4:sys::cpass1("����Ա"); break;
			case 5:sys::cpass1("��ӪԱ"); break;
			case 0:return;
			default: break;
			}
			system("cls");
		}
	}
}
