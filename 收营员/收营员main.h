#pragma once
#include"��ӪԱ����СƱ.h"
namespace cashier
{
	
	void cashier()
	{
		sys::password("��ӪԱ");
		while(1){
			cout << "��ѡ������Ҫ�Ĺ���" << endl;
			cout << "1���������㲢����СƱ" << endl;
			cout << "2��������Ӳ�Ʒ" << endl;
			cout << "3������ɾ����Ʒ" << endl;
			cout << "4���޸Ĳ�Ʒ״̬���Ƿ�������" << endl;
			cout << "5��ͳ��СƱ����" << endl;
			cout << "6���޸Ĳ���״̬"<<endl;
			cout << "7���޸�����" << endl;
			cout << "0���˳�����" << endl;

			int n = ::int_input(7);
			switch (n)
			{
			case 1:cashier_recipet(); break;
			case 2:server::serveradd(); break;
			case 3:server::serverDelete(); break;
			case 4: ::changemunu("���ݴ洢/menu.txt"); break;
			case 5: sys::analyzeReceipts("���ݴ洢/СƱ�洢/"); break;
			case 6:sys::manageTables(); break;
			case 7:sys::cpass2("��ӪԱ"); break;
			case 0:return;
			default: break;
			}
			system("cls");
		}
	}
}