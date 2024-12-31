#pragma once
namespace server
{
    void serverAddDishesToOrder(const string& order_file, const MenuItem menu[], int menu_size) {
        // 打开订单文件
        fstream file(order_file, ios::in | ios::out);
        if (!file.is_open()) {
            cout << "无法打开订单文件: " << order_file << endl;
            return;
        }

        // 读取订单内容并显示
        string line;
        cout << "当前订单内容:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }

        // 添加菜品
        int item_number;
        cout << "\n请输入要添加的菜品编号: ";
        cin >> item_number;
        if (item_number < 1 || item_number > menu_size) {
            cout << "无效的菜品编号。" << endl;
            return;
        }

        const MenuItem& selected_item = menu[item_number - 1];
        cout << "已选择菜品: " << selected_item.name << "，价格: " << selected_item.price << " 元\n";

        int quantity;
        string special_requests = "";
        cout << "请输入数量: ";
        cin >> quantity;
        cin.ignore(); // 清除输入缓冲区中的换行符

        special_requests = costomer::getSpecialRequests(menu[item_number - 1].type);
        // 定位文件末尾并写入新菜品
        file.clear(); // 清除文件流状态
        file.seekp(0, ios::end);

        file << left << setw(30) << selected_item.name
            << setw(10) << selected_item.price
            << setw(10) << quantity
            << setw(20) << special_requests
            << setw(20) << costomer::class_dishes(selected_item.type)
            << setw(20) << "未完成" << endl;

        cout << "菜品已成功添加到订单。" << endl;

        file.close();
    }
    void serveradd()
    {
        displayAvailableOrders();
        ifstream ss("数据存储/订单数据/序号.txt");
        int n_max;
        ss >> n_max;
        ss.close();
        ::MenuItem menu[MAX_MENU_ITEMS];
        int menu_num = ::loadMenuFromFile("数据存储/menu.txt", menu);
        showMenu(menu, menu_num);
        while (1)
        {
            cout << "请输入你想要添加的订单,按0退出";
            int in = ::int_input(n_max, 0);
            if (in == 0)
                return;
            string filename = "数据存储/订单数据/" + to_string(in) + ".txt";
            serverAddDishesToOrder(filename, menu, menu_num);
        }
    }
    void serverDeleteDishFromOrder(const string& order_file) {
        // 打开订单文件
        ifstream file(order_file);
        if (!file.is_open()) {
            cout << "无法打开订单文件: " << order_file << endl;
            return;
        }

        // 读取订单内容并保存到数组
        string lines[150];
        int line_count = 0;
        string line;
        cout << "当前订单内容:" << endl;
        while (getline(file, line) && line_count < 150) {
            lines[line_count++] = line;
            cout << line << endl;
        }
        ::separator(80);
        file.close();
        cout << endl << endl;
        // 查找菜品部分的起始行
        int dish_start = -1;
        for (int i = 0; i < line_count; ++i) {
            if (lines[i].find("菜品名") != string::npos) {
                dish_start = i + 1;
                break;
            }
        }

        if (dish_start == -1 || dish_start >= line_count) {
            //    cerr << "订单中未找到菜品部分。" << endl;
            return;
        }

        // 显示菜品列表
        cout << "\n菜品列表:" << endl;
        for (int i = dish_start; i < line_count; ++i) {
            cout << i - dish_start + 1 << ". " << lines[i] << endl;
        }

        // 选择要删除的菜品
        int dish_number;
        cout << "\n请输入要删除的菜品序号 (输入0退出): ";
        cin >> dish_number;

        if (dish_number <= 0 || dish_start + dish_number - 1 >= line_count) {
            cout << "无效的菜品序号。" << endl;
            return;
        }

        // 删除指定菜品
        for (int i = dish_start + dish_number - 1; i < line_count - 1; ++i) {
            lines[i] = lines[i + 1];
        }
        --line_count;
        cout << "菜品已成功删除。" << endl;

        // 写回文件
        ofstream outfile(order_file, ios::trunc);
        if (!outfile.is_open()) {
            cout << "无法写入订单文件: " << order_file << endl;
            return;
        }

        for (int i = 0; i < line_count; ++i) {
            outfile << lines[i] << endl;
        }

        outfile.close();
    }

    void serverDelete() {
        displayAvailableOrders();
        ifstream ss("数据存储/订单数据/序号.txt");
        int n_max;
        ss >> n_max;
        ss.close();

        while (1) {
            cout << "请输入你想要删除菜品的订单编号, 按0退出: ";
            int in = ::int_input(n_max, 0);
            if (in == 0)
                return;

            string filename = "数据存储/订单数据/" + to_string(in) + ".txt";
            serverDeleteDishFromOrder(filename);
        }
    }
    void displayAvailableOrders(const std::string& order_directory) {
        using namespace std;

        // 打开序号文件获取最大订单号
        ifstream seq_file(order_directory + "/序号.txt");
        if (!seq_file.is_open()) {
            cerr << "无法打开序号文件: " << order_directory + "/序号.txt" << endl;
            return;
        }

        int max_order_number;
        seq_file >> max_order_number;
        seq_file.close();

        if (max_order_number <= 0) {
            cout << "当前没有可用的订单。" << endl;
            return;
        }

        cout << left << setw(15) << "订单编号" << setw(15) << "餐桌号" << setw(20) << "姓名" << endl;
        cout << string(50, '-') << endl;

        for (int i = 1; i <= max_order_number; ++i) {
            string file = order_directory + "/" + to_string(i) + ".txt";
            ifstream infile(file);
            if (!infile.is_open()) {
                continue; // 跳过不存在的文件
            }

            string line, table_number = "未知", name = "未知";

            // 读取餐桌号和姓名信息
            while (getline(infile, line)) {
                if (line.find("餐桌号:") != string::npos) {
                    table_number = line.substr(line.find(":") + 1);
                    table_number.erase(0, table_number.find_first_not_of(" "));
                }
                else if (line.find("姓名:") != string::npos) {
                    name = line.substr(line.find(":") + 1);
                    name.erase(0, name.find_first_not_of(" "));
                    break;
                }
            }

            infile.close();

            cout << left << setw(15) << i
                << setw(15) << table_number
                << setw(20) << name << endl;
        }
    }
}
 