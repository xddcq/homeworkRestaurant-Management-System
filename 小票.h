#pragma once
void calculateTotal(Order& order) {
    order.total_price = 0.0;
    for (int i = 0; i < order.item_count; ++i) {
        order.total_price += order.items[i].item.price * order.items[i].quantity;
    }
}
string class_dishes(int n)
{
    if (n == 101 || n == 201)
        return"����";
    else
        return"���ϻ�С��";
}
// ��ȡ�ͻ���Ϣ
void getUserDetails(Order& order) {
    cout << "��������������: ";
    cin.ignore();
    getline(cin, order.customer_name);
    cout << "��������ϵ��ʽ (�����Ը͸¶��ֱ�Ӱ��س�): ";
    getline(cin, order.contact_info);
    cout << "�Զ������κα�ע��? (������Ҫ��, ������Ϣ��): ";
    getline(cin, order.remarks);
}

// ��ӡ�����ܽ�
void printOrderSummary(const Order& order) {
    cout << "�����ܽ�:" << endl;
    cout << "����: " << order.customer_name << endl;
    cout << "��ϵ��ʽ: " << order.contact_info << endl;
    cout << "��ע: " << order.remarks << endl;

    cout << left << setw(30) << "��Ʒ��" << setw(10) << "����" << setw(10) << "����"
        << setw(20) << "����Ҫ��" <<setw(20)<<"����" << endl;
    separator(80);

    for (int i = 0; i < order.item_count; ++i) {
        cout << left << setw(30) << order.items[i].item.name
            << setw(10) << order.items[i].item.price
            << setw(10) << order.items[i].quantity
            << setw(20) << order.items[i].special_requests 
            << setw(20)<<class_dishes(order.items[i].item.type)<<endl;
    }

    //cout << "------------------------------------------" << endl;
    cout << "�ܼ�: " << order.total_price << "Ԫ" << endl;
}
#pragma once//�ܼ�
// ��ȡ�ͻ���Ϣ
// ��ӡ�����ܽ�
void addMenuItem(Order& order, const MenuItem menu[],int itemCount) {
    cout << "��������Ҫ��ӵĲ�Ʒ���";
    int n=int_input(itemCount);
    int quantity;
    string special_requests;
    MenuItem menu_item = menu[n - 1];
    cout << "��ѡ��Ĳ�Ʒ��: " << menu_item.name << "���۸�: " << menu_item.price << "Ԫ\n";
    cout << "����������: ";
    cin >> quantity;
    cin.ignore(); // ������з�
    special_requests= getSpecialRequests(menu[n-1].type);
    
    OrderItem new_item = { menu_item, quantity, special_requests };
    order.items[order.item_count++]=new_item;

    cout << "��Ʒ����ӵ�������\n";
}
void saveOrderToFile(const Order& order, int order_number) {
    string filename = "���ݴ洢/��������/"+to_string(order_number) + ".txt";
    ofstream order_file(filename, ios::out); 
    if (!order_file.is_open()) {
        cerr << "�޷����������ļ�" << endl;
        return;
    }

    // д�붩����Ϣ
    order_file << "������: " << order.table_count << "\n";
    order_file << "����: " << order.customer_name << "\n";
    order_file << "��ϵ��ʽ: " << order.contact_info << "\n";
    order_file << "��ע: " << order.remarks << "\n\n";

    order_file << left << setw(30) << "��Ʒ��" << setw(10) << "����" << setw(10) << "����"
        << setw(20) << "����Ҫ��" << setw(20)<<"����"<<setw(20)<<"״̬" << "\n";
    //order_file << "----------------------------------------------\n";

    for (int i = 0; i < order.item_count;i++) {
        order_file << left << setw(30) << order.items[i].item.name
            << setw(10) << order.items[i].item.price
            << setw(10) << order.items[i].quantity
            << setw(20) << order.items[i].special_requests 
            <<setw(20)<<class_dishes(order.items[i].item.type)
            <<setw(20)<<"δ���"<<endl;
    }

    //order_file << "------------------------------------------\n";

    order_file.close();
    cout << "�����ѱ��浽�ļ�: " << filename << endl;
}