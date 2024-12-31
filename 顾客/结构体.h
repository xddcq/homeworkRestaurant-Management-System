#pragma once

#define MAX_MENU_ITEMS 100
#define MAX_NUMBER 100
using namespace std;
// �˵���ṹ��
struct MenuItem {
    int id;             // �˵�����
    string name;        // �˵�������
    double price;       // �˵���۸�
    int type;           // �˵�������
};

// ������ṹ��
struct OrderItem {
    MenuItem item;      // �˵�����Ϣ
    int quantity;       // ����
    string special_requests; // ����Ҫ��
};

// �����ṹ��
struct Order {
    string customer_name;            // �˿�����
    string contact_info;             // �˿���ϵ��ʽ
    string remarks;                  // ������ע
    int assigned_tables; // ��������ӱ������
    int table_count;                 // �������������
    OrderItem items[MAX_MENU_ITEMS]; // ���������Ĳ�Ʒ��
    int item_count;                  // �����еĲ�Ʒ����
    double total_price;              // �����ܼ�
};
struct Table {
    int id;        // ���ӵı��
    int capacity;  // ���ӵ����������������ɶ����ˣ�
    int status;    // ����״̬��1 ��ʾ���ã�2 ��ʾ��ռ��
};

