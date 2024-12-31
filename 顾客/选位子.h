#pragma once
int max_table;
bool cmd1(const Table& a, const Table& b) {
    return a.capacity < b.capacity;
}
int loadTablesFromFile(const string& filename, Table tables[], int maxTables) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开位子文件" << endl;
        return 0;
    }

    int tableCount;
    file >> tableCount;
    file.ignore(); // Ignore newline character

    for (int i = 0; i < tableCount && i < maxTables; ++i) {
        file >> tables[i].id >> tables[i].capacity >> tables[i].status;
    }

    file.close();
    return tableCount;
}

void saveTablesToFile(const string& filename, Table tables[], int tableCount) {
    ofstream file(filename);

    if (!file.is_open()) {
        cerr << "无法保存位子文件" << endl;
        return;
    }

    file << tableCount << endl;
    for (int i = 0; i < tableCount; ++i) {
        file << tables[i].id << " " << tables[i].capacity << " " << tables[i].status << endl;
    }

    file.close();
}

int assignTable(int customerCount, Table tables[], int tableCount, Order& order) {
    int selectedTableId = -1; // 用于存储选择的桌子ID

    // 按桌子容量升序排序
    bubbleSort(tables, tables + tableCount, cmd1);

    // 查找第一个容量大于等于顾客人数且状态为可用的桌子
    for (int i = 0; i < tableCount; ++i) {
        if (tables[i].status == 1 && tables[i].capacity >= customerCount) {
            selectedTableId = tables[i].id; // 记录桌子ID
            tables[i].status = 2;           // 标记桌子为已占用
            break;
        }
    }

    // 如果找到合适的桌子，则分配给订单
    if (selectedTableId != -1) {
        order.assigned_tables = selectedTableId; // 分配的桌子ID
        order.table_count = 1;                  // 表示只分配了一张桌子
        //cout << "分配了桌子编号: " << selectedTableId << endl;
        return selectedTableId;
    }
    else {
        // 如果没有找到合适的桌子，提示错误
        cerr << "无法满足顾客人数的座位需求，请稍后再试。" << endl;
    }
}

void printAssignedTables(const Order& order) {
    cout << "分配的餐桌编号: ";
    for (int i = 0; i < order.table_count; ++i) {
        cout << order.assigned_tables << "号 ";
    }
    cout << endl;
}
int select_table()
{
    const int MAX_TABLES = 100; // 最大桌子数量
    Table tables[MAX_TABLES];
    int tableCount = loadTablesFromFile("数据存储/位子.txt", tables, MAX_TABLES);
    if (tableCount == 0) {
        cout << "无法加载位子信息" << endl;
        exit(0);
    }

    Order order;
    order.item_count = 0;

    // 询问顾客人数
    int customerCount;
    cout << "请输入顾客人数: ";
    customerCount=int_input(1000,1);

    // 分配餐桌
    int table=assignTable(customerCount, tables, tableCount, order);

    // 显示分配结果
    printAssignedTables(order);

    // 保存更新后的桌子状态
    saveTablesToFile("数据存储/位子.txt", tables, tableCount);
    return table;
}