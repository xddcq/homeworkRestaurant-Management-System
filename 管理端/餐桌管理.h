namespace sys
{
    using namespace std;

    const int MAX_TABLES = 100;

    struct Table {
        int table_number;
        int customer_count;
        int status; // 1: 无人, 2: 有人
    };

    // 读取餐桌信息文件
    bool readTableInfo(const string& filepath, Table tables[], int& table_count) {
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filepath << endl;
            return false;
        }

        string line;
        if (getline(file, line)) {
            table_count = stoi(line); // 读取餐桌总数
            if (table_count > MAX_TABLES) {
                cerr << "餐桌数量超过最大值 (" << MAX_TABLES << ")！\n";
                return false;
            }
        }
        else {
            cerr << "文件格式错误: 无法读取餐桌总数。" << endl;
            return false;
        }

        int index = 0;
        while (getline(file, line) && index < table_count) {
            stringstream ss(line);
            ss >> tables[index].table_number >> tables[index].customer_count >> tables[index].status;
            ++index;
        }

        file.close();
        return true;
    }

    // 显示所有餐桌状态
    void displayTableStatus(const Table tables[], int table_count) {
        cout << "================ 餐桌状态 ================\n";
        cout << left << setw(10) << "桌号" << setw(15) << "就餐人数" << setw(10) << "状态" << "\n";
        cout << "------------------------------------------\n";

        for (int i = 0; i < table_count; ++i) {
            cout << left << setw(10) << tables[i].table_number
                << setw(15) << tables[i].customer_count
                << (tables[i].status == 1 ? "无人" : "有人") << "\n";
        }

        cout << "==========================================\n";
    }

    // 修改指定餐桌的状态
    void modifyTableStatus(Table tables[], int table_count, int table_number, int new_status) {
        for (int i = 0; i < table_count; ++i) {
            if (tables[i].table_number == table_number) {
                tables[i].status = new_status;
                cout << "桌号 " << table_number << " 的状态已修改为 "
                    << (new_status == 1 ? "无人" : "有人") << "。\n";
                return;
            }
        }
        cerr << "未找到桌号 " << table_number << "！\n";
    }

    // 批量修改所有餐桌的状态
    void batchModifyTableStatus(Table tables[], int table_count, int new_status) {
        for (int i = 0; i < table_count; ++i) {
            tables[i].status = new_status;
        }
        cout << "所有餐桌的状态已修改为 "
            << (new_status == 1 ? "无人" : "有人") << "。\n";
    }

    // 保存餐桌信息回文件
    bool saveTableInfo(const string& filepath, const Table tables[], int table_count) {
        ofstream file(filepath);
        if (!file.is_open()) {
            cerr << "无法保存文件: " << filepath << endl;
            return false;
        }

        file << table_count << "\n"; // 写入餐桌总数
        for (int i = 0; i < table_count; ++i) {
            file << tables[i].table_number << " " << tables[i].customer_count << " " << tables[i].status << "\n";
        }

        file.close();
        return true;
    }

    // 餐桌管理主函数
    void manageTables() {
        string filepath = "数据存储/位子.txt";
        Table tables[MAX_TABLES];
        int table_count = 0;

        // 读取餐桌信息
        if (!readTableInfo(filepath, tables, table_count)) {
            return;
        }

        int choice;
        do {
            cout << "\n======== 餐桌管理系统 ========\n";
            cout << "1. 显示所有餐桌状态\n";
            cout << "2. 修改指定餐桌状态\n";
            cout << "3. 批量修改所有餐桌状态\n";
            cout << "4. 保存并退出\n";
            cout << "请输入选项: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayTableStatus(tables, table_count);
                break;
            case 2: {
                int table_number, new_status;
                cout << "请输入桌号: ";
                cin >> table_number;
                cout << "请输入新状态 (1: 无人, 2: 有人): ";
                cin >> new_status;
                if (new_status == 1 || new_status == 2) {
                    modifyTableStatus(tables, table_count, table_number, new_status);
                }
                else {
                    cerr << "无效状态！\n";
                }
                break;
            }
            case 3: {
                int new_status;
                cout << "请输入新状态 (1: 无人, 2: 有人): ";
                cin >> new_status;
                if (new_status == 1 || new_status == 2) {
                    batchModifyTableStatus(tables, table_count, new_status);
                }
                else {
                    cerr << "无效状态！\n";
                }
                break;
            }
            case 4:
                if (saveTableInfo(filepath, tables, table_count)) {
                    cout << "餐桌信息已保存。\n";
                }
                break;
            default:
                cerr << "无效选项！\n";
                break;
            }
        } while (choice != 4);
    }
}
