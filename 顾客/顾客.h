using namespace std;
// 从文件加载菜单


// 获取有效数量
int getValidQuantity() {
    int quantity=int_input(MAX_MENU_ITEMS);
    return quantity;
}

// 选择菜单项
int selectMenuItems(MenuItem menu[], int itemCount, Order& order) {
    cout << "请选择菜品 (输入菜品编号和数量, 输入q退出): " << endl;
    while (true) {
        string input;
        cout << "菜品编号: ";
        cin >> input;

        if (input == "q") break;

        stringstream ss(input);
        int id;
        if (ss >> id && id > 0 && id <= itemCount&&menu[id-1].type%10==1) {
            cout << "数量: ";
            int quantity = getValidQuantity();

            string special_requests= getSpecialRequests(menu[id - 1].type);
            order.items[order.item_count++] = { menu[id - 1], quantity, special_requests };

            if (order.item_count >= MAX_MENU_ITEMS) {
                cout << "订单项已达上限, 无法添加更多菜品." << endl;
                break;
            }
        }
        else {
            cout << "无效的菜品编号, 请重新输入." << endl;
        }
    }
    return order.item_count;
}