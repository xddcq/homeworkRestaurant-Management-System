#pragma once
int max_table;
bool cmd1(const Table& a, const Table& b) {
    return a.capacity < b.capacity;
}
int loadTablesFromFile(const string& filename, Table tables[], int maxTables) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "�޷���λ���ļ�" << endl;
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
        cerr << "�޷�����λ���ļ�" << endl;
        return;
    }

    file << tableCount << endl;
    for (int i = 0; i < tableCount; ++i) {
        file << tables[i].id << " " << tables[i].capacity << " " << tables[i].status << endl;
    }

    file.close();
}

int assignTable(int customerCount, Table tables[], int tableCount, Order& order) {
    int selectedTableId = -1; // ���ڴ洢ѡ�������ID

    // ������������������
    bubbleSort(tables, tables + tableCount, cmd1);

    // ���ҵ�һ���������ڵ��ڹ˿�������״̬Ϊ���õ�����
    for (int i = 0; i < tableCount; ++i) {
        if (tables[i].status == 1 && tables[i].capacity >= customerCount) {
            selectedTableId = tables[i].id; // ��¼����ID
            tables[i].status = 2;           // �������Ϊ��ռ��
            break;
        }
    }

    // ����ҵ����ʵ����ӣ�����������
    if (selectedTableId != -1) {
        order.assigned_tables = selectedTableId; // ���������ID
        order.table_count = 1;                  // ��ʾֻ������һ������
        //cout << "���������ӱ��: " << selectedTableId << endl;
        return selectedTableId;
    }
    else {
        // ���û���ҵ����ʵ����ӣ���ʾ����
        cerr << "�޷�����˿���������λ�������Ժ����ԡ�" << endl;
    }
}

void printAssignedTables(const Order& order) {
    cout << "����Ĳ������: ";
    for (int i = 0; i < order.table_count; ++i) {
        cout << order.assigned_tables << "�� ";
    }
    cout << endl;
}
int select_table()
{
    const int MAX_TABLES = 100; // �����������
    Table tables[MAX_TABLES];
    int tableCount = loadTablesFromFile("���ݴ洢/λ��.txt", tables, MAX_TABLES);
    if (tableCount == 0) {
        cout << "�޷�����λ����Ϣ" << endl;
        exit(0);
    }

    Order order;
    order.item_count = 0;

    // ѯ�ʹ˿�����
    int customerCount;
    cout << "������˿�����: ";
    customerCount=int_input(1000,1);

    // �������
    int table=assignTable(customerCount, tables, tableCount, order);

    // ��ʾ������
    printAssignedTables(order);

    // ������º������״̬
    saveTablesToFile("���ݴ洢/λ��.txt", tables, tableCount);
    return table;
}