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
        return"正餐";
    else
        return"饮料或小吃";
}
// 获取客户信息
void getUserDetails(Order& order) {
    cout << "请输入您的姓名: ";
    cin.ignore();
    getline(cin, order.customer_name);
    cout << "请输入联系方式 (如果不愿透露可直接按回车): ";
    getline(cin, order.contact_info);
    cout << "对订单有任何备注吗? (如特殊要求, 过敏信息等): ";
    getline(cin, order.remarks);
}

// 打印订单总结
void printOrderSummary(const Order& order) {
    cout << "订单总结:" << endl;
    cout << "姓名: " << order.customer_name << endl;
    cout << "联系方式: " << order.contact_info << endl;
    cout << "备注: " << order.remarks << endl;

    cout << left << setw(30) << "菜品名" << setw(10) << "单价" << setw(10) << "数量"
        << setw(20) << "特殊要求" <<setw(20)<<"种类" << endl;
    separator(80);

    for (int i = 0; i < order.item_count; ++i) {
        cout << left << setw(30) << order.items[i].item.name
            << setw(10) << order.items[i].item.price
            << setw(10) << order.items[i].quantity
            << setw(20) << order.items[i].special_requests 
            << setw(20)<<class_dishes(order.items[i].item.type)<<endl;
    }

    //cout << "------------------------------------------" << endl;
    cout << "总价: " << order.total_price << "元" << endl;
}
#pragma once//总价
// 获取客户信息
// 打印订单总结
void addMenuItem(Order& order, const MenuItem menu[],int itemCount) {
    cout << "请输入你要添加的菜品编号";
    int n=int_input(itemCount);
    int quantity;
    string special_requests;
    MenuItem menu_item = menu[n - 1];
    cout << "您选择的菜品是: " << menu_item.name << "，价格: " << menu_item.price << "元\n";
    cout << "请输入数量: ";
    cin >> quantity;
    cin.ignore(); // 清除换行符
    special_requests= getSpecialRequests(menu[n-1].type);
    
    OrderItem new_item = { menu_item, quantity, special_requests };
    order.items[order.item_count++]=new_item;

    cout << "菜品已添加到订单。\n";
}
void saveOrderToFile(const Order& order, int order_number) {
    string filename = "数据存储/订单数据/"+to_string(order_number) + ".txt";
    ofstream order_file(filename, ios::out); 
    if (!order_file.is_open()) {
        cerr << "无法创建订单文件" << endl;
        return;
    }

    // 写入订单信息
    order_file << "餐桌号: " << order.table_count << "\n";
    order_file << "姓名: " << order.customer_name << "\n";
    order_file << "联系方式: " << order.contact_info << "\n";
    order_file << "备注: " << order.remarks << "\n\n";

    order_file << left << setw(30) << "菜品名" << setw(10) << "单价" << setw(10) << "数量"
        << setw(20) << "特殊要求" << setw(20)<<"种类"<<setw(20)<<"状态" << "\n";
    //order_file << "----------------------------------------------\n";

    for (int i = 0; i < order.item_count;i++) {
        order_file << left << setw(30) << order.items[i].item.name
            << setw(10) << order.items[i].item.price
            << setw(10) << order.items[i].quantity
            << setw(20) << order.items[i].special_requests 
            <<setw(20)<<class_dishes(order.items[i].item.type)
            <<setw(20)<<"未完成"<<endl;
    }

    //order_file << "------------------------------------------\n";

    order_file.close();
    cout << "订单已保存到文件: " << filename << endl;
}