using namespace std;
// ���ļ����ز˵�


// ��ȡ��Ч����
int getValidQuantity() {
    int quantity=int_input(MAX_MENU_ITEMS);
    return quantity;
}

// ѡ��˵���
int selectMenuItems(MenuItem menu[], int itemCount, Order& order) {
    cout << "��ѡ���Ʒ (�����Ʒ��ź�����, ����q�˳�): " << endl;
    while (true) {
        string input;
        cout << "��Ʒ���: ";
        cin >> input;

        if (input == "q") break;

        stringstream ss(input);
        int id;
        if (ss >> id && id > 0 && id <= itemCount&&menu[id-1].type%10==1) {
            cout << "����: ";
            int quantity = getValidQuantity();

            string special_requests= getSpecialRequests(menu[id - 1].type);
            order.items[order.item_count++] = { menu[id - 1], quantity, special_requests };

            if (order.item_count >= MAX_MENU_ITEMS) {
                cout << "�������Ѵ�����, �޷���Ӹ����Ʒ." << endl;
                break;
            }
        }
        else {
            cout << "��Ч�Ĳ�Ʒ���, ����������." << endl;
        }
    }
    return order.item_count;
}