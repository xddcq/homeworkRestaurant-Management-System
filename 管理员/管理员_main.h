#pragma once
#include"���Թ���ģ��.h"
#include"�����˺�.h"
namespace administrator
{
	using namespace std;
	void administrator()
	{
		sys::password("����Ա");
		while (1) {
			cout << "��ѡ������Ҫ�Ĺ���" << endl;
			cout << "1����������СƱ" << endl;
			cout << "2��������Ӳ�Ʒ" << endl;
			cout << "3������ɾ����Ʒ" << endl;
			cout << "4���޸Ĳ�Ʒ״̬���Ƿ�������" << endl;
			cout << "5��ͳ��СƱ����" << endl;
			cout << "6���޸Ĳ���״̬" << endl;
			cout << "7���޸Ĳ˵�" << endl;
			cout << "8��չʾ����" << endl;
			cout << "9��չʾͶ��" << endl;
			cout << "10�����Թ���ģ��" << endl;
			cout << "11�����ò�λ��" << endl;
			cout << "12���޸�����" << endl;
			cout << "0��������һ��" << endl;

			int n = ::int_input(11);
			switch (n)
			{
			case 1:cashier::cashier_recipet(); break;
			case 2:server::serveradd(); break;
			case 3:server::serverDelete(); break;
			case 4: ::changemunu("���ݴ洢/menu.txt"); break;
			case 5: sys::analyzeReceipts("���ݴ洢/СƱ�洢/"); break;
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
		cout << "��������Ҫ���õĲ�λ��";
		int n = ::int_input();
		cout << "���óɹ�";
		::writeNumberToFile("���ݴ洢/��λ��.txt",n);
	}
}
