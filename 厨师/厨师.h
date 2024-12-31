#include"厨师结构体.h"   
namespace cook
{
    using namespace std;
    
    // 菜品信息结构体

    // 从文件读取订单数据
    int readOrderFile(const string& filepath, const string& order_number, cook::Dish dishes[], int start_index) {
        ifstream file(filepath);

        if (!file.is_open()) {
           // cerr << "无法打开文件: " << filepath << endl;//有些文件打不开是正常的
            return start_index;
        }

        string line, table_number;
        while (getline(file, line)) {
            if (line.find("桌号:") != string::npos) {
                table_number = line.substr(line.find(":") + 1); // 提取桌号
            }

            // 读取菜品表头之后的内容
            if (line.find("菜品名") != string::npos) {
                while (getline(file, line) && !line.empty()) {
                    stringstream ss(line);
                    string name, price, quantity, special_requests, type, status;

                    // 按固定宽度读取各列
                    ss >> setw(30) >> name >> setw(10) >> price >> setw(10) >> quantity
                        >> setw(20) >> special_requests >> setw(10) >> type >> setw(10) >> status;

                    // 如果种类是正餐，则保存菜品信息
                    if (type == "正餐" && start_index < 500) {
                        dishes[start_index++] = { name, table_number, order_number, special_requests, type, status };
                    }
                }
            }
        }

        file.close();
        return start_index;
    }

    // 更新订单状态
    void updateOrderStatus(const string& filepath, const cook::Dish& dish) {
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filepath << endl;
            return;
        }

        stringstream buffer;
        string line;
        bool updated = false;

        while (getline(file, line)) {
            if (line.find(dish.name) != string::npos &&
                line.find(dish.status) != string::npos &&
                line.find("未完成") != string::npos) {
                line.replace(line.find("未完成"), 9, "已出菜");
                updated = true;
            }
            buffer << line << "\n";
        }

        file.close();

        if (updated) {
            ofstream output_file(filepath, ios::trunc);
            output_file << buffer.str();
            output_file.close();
            cout << "状态已更新为“已出菜”：订单编号 " << dish.order_number << "，桌号 " << dish.table_number
                << "，菜品名 " << dish.name << endl;
        }
        else {
            cout << "未找到需要更新的菜品记录。" << endl;
        }
    }

    int cooker_cook() {
        string folder_path = "数据存储/订单数据";
        string serial_file = folder_path + "/序号.txt";

        // 读取序号文件，确定订单总数
        ifstream serial_input(serial_file);
        if (!serial_input.is_open()) {
            cerr << "无法读取序号文件: " << serial_file << endl;//有些文件打不开是正常的
            return 1;
        }

        int total_orders;
        serial_input >> total_orders;
        total_orders--;
        if (total_orders == 0)
        {
            cout << "暂时没有订单";
            return 0;
        }
        serial_input.close();

        cook::Dish dishes[500]; // 固定大小数组
        int dish_count = 0;

        // 遍历所有订单文件
        for (int i = 1; i <= total_orders && dish_count < 500; ++i) {
            string order_file = folder_path + "/" + to_string(i) + ".txt";
            dish_count = readOrderFile(order_file, to_string(i), dishes, dish_count);
        }

        // 输出所有正餐菜品
        cout << left << setw(5) << "序号" << setw(10) << "订单编号" << setw(10) << "桌号"
            << setw(30) << "菜品名" << setw(20) << "特殊要求" << setw(10) << "状态" << endl;
        cout << string(85, '-') << endl;

        for (int i = 0; i < dish_count; ++i) {
            cout << left << setw(5) << (i + 1) << setw(10) << dishes[i].order_number
                << setw(10) << dishes[i].table_number << setw(30) << dishes[i].name
                << setw(20) << dishes[i].special_requests << setw(10) << dishes[i].status << endl;
        }

        // 修改菜品状态
        int dish_index;
        cout << "\n请输入要更新状态的菜品序号（输入 0 结束程序）: ";
        while (cin >> dish_index && dish_index != 0) {
            if (dish_index < 1 || dish_index > dish_count) {
                cout << "无效的序号，请重新输入。" << endl;
            }
            else {
                Dish& selected_dish = dishes[dish_index - 1];
                if (selected_dish.status == "未完成") {
                    string filepath = folder_path + "/" + selected_dish.order_number + ".txt";
                    updateOrderStatus(filepath, selected_dish);
                    selected_dish.status = "已出菜"; // 更新内存中的状态
                }
                else {
                    cout << "该菜品已出菜，无法重复更新状态。" << endl;
                }
            }
            cout << "\n请输入要更新状态的菜品序号（输入 0 结束程序）: ";
        }

        return 0;
    }
}