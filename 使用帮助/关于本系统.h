#pragma once
namespace about
{
	void about()
	{
		while(true)
		{
			cout << "1����л" << endl;
			cout << "2��ʹ�ð���" << endl;
			cout << "3����������" << endl;
			cout << "4�����" << endl;
			cout << "0��������һ��" << endl;
			int n = ::int_input(4);
			system("cls");
			switch (n)
			{
			case 0:return;
			case 1: ::readFileByLine("ʹ�ð���/��л.txt"); break;
			case 2: ::readFileByLine("ʹ�ð���/ʹ�ð���.txt"); break;
			case 3: ::readFileByLine("ʹ�ð���/��������.txt"); break;
			case 4: ::readFileByLine("ʹ�ð���/���.txt"); break;
			}
			��ͣ;
			����;
		}
	}
}
