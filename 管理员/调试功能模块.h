#pragma once
namespace administrator
{
	using namespace std;
	void test()
	{
		while (1) {
			cout << "��ѡ������Ҫ���Ե�ģ��" << endl;
			cout << "1����ʦģ��" << endl;
			cout << "2������Աģ��" << endl;
			cout << "3���˿�ģ��" << endl;
			cout << "4���ϰ�ģ��" << endl;
			cout << "5����ӪԱģ��" << endl;
			cout << "0:������һ��"<<endl;
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