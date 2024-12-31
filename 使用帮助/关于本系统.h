#pragma once
namespace about
{
	void about()
	{
		while(true)
		{
			cout << "1：致谢" << endl;
			cout << "2：使用帮助" << endl;
			cout << "3：制作名单" << endl;
			cout << "4：后记" << endl;
			cout << "0：返回上一级" << endl;
			int n = ::int_input(4);
			system("cls");
			switch (n)
			{
			case 0:return;
			case 1: ::readFileByLine("使用帮助/致谢.txt"); break;
			case 2: ::readFileByLine("使用帮助/使用帮助.txt"); break;
			case 3: ::readFileByLine("使用帮助/制作名单.txt"); break;
			case 4: ::readFileByLine("使用帮助/后记.txt"); break;
			}
			暂停;
			清屏;
		}
	}
}
