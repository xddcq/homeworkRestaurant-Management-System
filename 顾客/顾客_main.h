namespace costomer
{
	using namespace std;
#include"特殊需求.h"
#include"小票.h"
#include"顾客.h"
#include"选位子.h"
#include"投诉与建议.h"

	int updateSerialNumber(const string& filename) //当前到哪里了
	{
		int serial_number = 1; // 默认值

		// 打开文件读取当前的序号
		ifstream input_file(filename);
		if (input_file.is_open()) {
			input_file >> serial_number; // 读取文件中的序号
			input_file.close();
		}
		else {
			//cout << "文件不存在，将创建新文件。" << endl;
		}

		// 将序号加一
		// 以覆盖模式写入文件
		ofstream output_file(filename, ios::out);
		if (output_file.is_open()) {
			output_file << serial_number + 1;
			output_file.close();
		}
		else {
			cerr << "无法打开文件进行写入。" << endl;
		}
		return serial_number;
	}
	int customer() {
		int table = select_table();//分配位子模块
		bool is_break = 1;
		while (is_break)
		{
			cout << "1:点菜\n"
				"2:投诉与建议\n"
				"0:返回上级"<<endl;

			int n = int_input(2);

			switch (n)
			{
			case 1:is_break = 0; break;
			case 2:saveFeedback(); break;
			case 0:return 0;
			}//投诉与建议模块
		}
		int number = updateSerialNumber("数据存储/订单数据/序号.txt");
		MenuItem menu[MAX_MENU_ITEMS];
		int itemCount = loadMenuFromFile("数据存储/menu.txt", menu);
		Order order;
		getUserDetails(order);


		order.table_count = table;
		//int n=customer_order(menu,*order, itemCount);
		if (itemCount == 0) {
			cout << "菜单为空或加载失败" << endl;
			exit(0);
			return 0;
		}


		order.item_count = 0;

		cout << "欢迎来到餐厅点餐系统!" << endl;

		showMenu(menu, itemCount);
		int fn = selectMenuItems(menu, itemCount, order);
		calculateTotal(order);

		printOrderSummary(order);
		saveOrderToFile(order, number);
		while (1) {
			cout <<
				"1:添加菜品\n"
				"2:投诉与建议\n"
				"0:返回上级\n";
			int n = int_input(2);
			switch (n)
			{
			case 1:addMenuItem(order, menu, itemCount); saveOrderToFile(order, number);  break;
			case 2:saveFeedback(); break;
			case 0:; return 0;
			}
		}
		return 0;
	}
	int book_customer() {
		int table = select_table();//分配位子模块
		bool is_break = 1;
		while (is_break)
		{
			cout << "您可以在本系统预定餐位并点餐" << endl;
			cout << "1:点菜\n"
				"2:投诉与建议\n"
				"0:不点餐" << endl;

			int n = int_input(2);

			switch (n)
			{
			case 1:is_break = 0; break;
			case 2:saveFeedback(); break;
			case 0:return 0;
			}//投诉与建议模块
		}
		int number = updateSerialNumber("数据存储/订单数据/序号.txt");
		MenuItem menu[MAX_MENU_ITEMS];
		int itemCount = loadMenuFromFile("数据存储/menu.txt", menu);
		Order order;
		getUserDetails(order);


		order.table_count = table;
		//int n=customer_order(menu,*order, itemCount);
		if (itemCount == 0) {
			cout << "菜单为空或加载失败" << endl;
			exit(0);
			return 0;
		}
		order.item_count = 0;

		cout << "欢迎来到餐厅点餐系统!" << endl;

		showMenu(menu, itemCount);
		int fn = selectMenuItems(menu, itemCount, order);
		calculateTotal(order);

		printOrderSummary(order);
		saveOrderToFile(order, number);
		cout << "您的预定餐位已经记录，您仍然可以在到达后添加菜品";
		暂停;
		return 0;
	}
	void book_customer_arrival() {

		cout << "请输入你的订单号";
		int in = ::int_input(0x7fffffff,0);
		::MenuItem menu[MAX_MENU_ITEMS];
		int itemCount = loadMenuFromFile("数据存储/menu.txt", menu);
		showMenu(menu, itemCount);	
		int menu_num = ::loadMenuFromFile("数据存储/menu.txt", menu);
		string filename = "数据存储/订单数据/" + to_string(in) + ".txt";
		server::serverAddDishesToOrder(filename, menu, menu_num);
		暂停;
		return ;
	}
}