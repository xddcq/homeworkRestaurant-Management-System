#pragma once
namespace cashier
{
#define MAX_item 500
    // 读取订单文件并提取菜品信息
    int readWaiterFile(const string& filepath, cashier::Dish dishes[], int& start_index, int& customer_count) {
        ifstream file(filepath);

        if (!file.is_open()|| file.tellg() == 0) {
            cerr << "无法打开文件: " << filepath << endl;
            return -1;
        }

        string line, table_number;
        while (getline(file, line)) {
            // 提取餐桌号
            if (line.find("餐桌号:") != string::npos) {
                table_number = line.substr(line.find(":") + 1);
                table_number.erase(remove(table_number.begin(), table_number.end(), ' '), table_number.end());
            }
            // 提取顾客人数
            else if (line.find("姓名:") != string::npos) {
                customer_count = stoi(line.substr(line.find(":") + 1));
            }

            // 查找菜品表头
            if (line.find("菜品名") != string::npos) {
                // 跳过表头行和分隔线
                getline(file, line);
                while (getline(file, line) && !line.empty()) {
                    stringstream ss(line);
                    string name, special_requests, type, status;
                    double price;
                    int quantity;

                    // 按固定宽度解析各列
                    name = line.substr(0, 30);
                    name.erase(remove(name.begin(), name.end(), ' '), name.end());

                    string price_str = line.substr(30, 10);
                    price = stod(price_str);

                    string quantity_str = line.substr(40, 10);
                    quantity = stoi(quantity_str);

                    special_requests = line.substr(50, 20);
                    special_requests.erase(remove(special_requests.begin(), special_requests.end(), ' '), special_requests.end());

                    type = line.substr(70, 20);
                    type.erase(remove(type.begin(), type.end(), ' '), type.end());

                    status = line.substr(90, 10);
                    status.erase(remove(status.begin(), status.end(), ' '), status.end());

                    // 如果菜品状态是 "已完成"，则存储到数组
                    if (status == "已完成" && start_index < MAX_item) {
                        dishes[start_index++] = { name, table_number, price, quantity, special_requests, type, status };
                    }
                }
            }
        }

        file.close();
        return 0;
    }
    // 清空文件内容
    void clearFileContent(const string& filepath) {
        ofstream file(filepath, ofstream::out | ofstream::trunc);
        if (!file.is_open()) {
            cerr << "无法清空文件: " << filepath << endl;
        }
        file.close();
    }

    // 从文件读取餐位费
    double readSeatingFee(const string& filepath) {
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "无法打开餐位费文件: " << filepath << endl;
            return 0.0;
        }

        double seating_fee = 0.0;
        file >> seating_fee;
        file.close();
        return seating_fee;
    }

    // 预览小票
    void previewReceipt(const Dish dishes[], int count, int customer_count, double seating_fee) {
        double total_price = 0.0;

        // 计算总价，仅计算状态为 "已完成" 的菜品
        for (int i = 0; i < count; ++i) {
            if (dishes[i].status == "已完成") {
                total_price += dishes[i].price * dishes[i].quantity;
            }
        }

        // 如果总价不足500元，增加餐位费
        if (total_price < 500) {
            total_price += customer_count * seating_fee;
        }

        // 输出小票内容到控制台
        cout << "================ 小票预览 ================\n";
        cout << "餐桌号: " << (count > 0 ? dishes[0].table_number : "未知") << "\n\n";
        cout << left << setw(30) << "菜品名" << setw(10) << "单价" << setw(10) << "数量" << setw(20) << "特殊要求" << setw(10) << "状态" << "\n";
        cout << "---------------------------------------------\n";

        for (int i = 0; i < count; ++i) {
            cout << left << setw(30) << dishes[i].name
                << setw(10) << fixed << setprecision(2) << dishes[i].price
                << setw(10) << dishes[i].quantity
                << setw(20) << dishes[i].special_requests
                << setw(10) << dishes[i].status << "\n";
        }

        cout << "---------------------------------------------\n";
        if (total_price < 500) {
            cout << "餐位费: " << fixed << setprecision(2) << customer_count * seating_fee << " 元\n";
        }
        cout << "总价: " << fixed << setprecision(2) << total_price << " 元\n";
        cout << "=============================================\n";
    }

    // 生成小票并写入文件
    void generateReceipt(const string& outputPath, const Dish dishes[], int count, int customer_count, const string& payment_method, double cash, double seating_fee) {
        ofstream receipt(outputPath);

        if (!receipt.is_open()) {
            cerr << "无法生成小票文件: " << outputPath << endl;
            return;
        }

        double total_price = 0.0;

        // 计算总价，仅计算状态为 "已完成" 的菜品
        for (int i = 0; i < count; ++i) {
            if (dishes[i].status == "已完成") {
                total_price += dishes[i].price * dishes[i].quantity;
            }
        }

        // 如果总价不足500元，增加餐位费
        double seating_fee_total = 0.0;
        if (total_price < 500) {
            seating_fee_total = customer_count * seating_fee;
            total_price += seating_fee_total;
        }

        double total_due = total_price;
        double change = 0.0;

        // 如果是现金支付，计算找零
        if (payment_method == "现金") {
            while (cash < total_due) {
                cerr << "现金不足以支付总额！请重新输入" << endl;
                cin >> cash;
            }
            change = cash - total_due;
        }

        // 输出小票内容
        receipt << "================ 小票 ================\n";
        receipt << "餐桌号: " << (count > 0 ? dishes[0].table_number : "未知") << "\n";
        receipt << "支付方式: " << payment_method << "\n";
        if (payment_method == "现金") {
            receipt << "实收金额: " << fixed << setprecision(2) << cash << " 元\n";
            receipt << "找零金额: " << fixed << setprecision(2) << change << " 元\n";
        }
        receipt << "\n";

        receipt << left << setw(30) << "菜品名" << setw(10) << "单价" << setw(10) << "数量" << setw(20) << "特殊要求" << setw(10) << "状态" << "\n";
        receipt << "---------------------------------------------\n";

        for (int i = 0; i < count; ++i) {
            receipt << left << setw(30) << dishes[i].name
                << setw(10) << fixed << setprecision(2) << dishes[i].price
                << setw(10) << dishes[i].quantity
                << setw(20) << dishes[i].special_requests
                << setw(10) << dishes[i].status << "\n";
        }

        receipt << "---------------------------------------------\n";
        if (seating_fee_total > 0) {
            receipt << "餐位费: " << fixed << setprecision(2) << seating_fee_total << " 元\n";
        }
        receipt << "总价: " << fixed << setprecision(2) << total_due << " 元\n";
        receipt << "=============================================\n";

        receipt.close();
    }

    // 收银功能入口
    void cashier_recipet() {
        string inputDir = "数据存储/订单数据/";
        string outputDir = "数据存储/小票存储/";
        string feeFile = "数据存储/餐位费.txt";

        double seating_fee = readSeatingFee(feeFile);
        if (seating_fee <= 0) {
            cerr << "餐位费文件内容无效，操作取消。" << endl;
            return;
        }

        ::readallfile();
        cout << "请输入要处理的订单编号: ";
        string orderNumber;
        cin >> orderNumber;

        string inputFile = inputDir + orderNumber + ".txt";

        // 检查订单文件是否存在
        ifstream checkFile(inputFile);
        if (!checkFile.is_open()) {
            cerr << "订单文件 " << inputFile << " 不存在！" << endl;
            return;
        }
        checkFile.close();

        Dish dishes[MAX_item];
        int dish_count = 0;
        int customer_count = 0; // 顾客人数

        // 读取订单文件
        if (readWaiterFile(inputFile, dishes, dish_count, customer_count) == 0) {
            // 展示小票预览
            previewReceipt(dishes, dish_count, customer_count, seating_fee);

            // 确认是否生成小票
            cout << "是否确认生成小票？(输入 Y 确认，其他键取消): ";
            string userInput;
            cin >> userInput;

            if (userInput != "Y" && userInput != "y") {
                cout << "操作已取消。" << endl;
                return;
            }

            // 选择支付方式
            string payment_method;
            double cash_amount = 0.0;

            cout << "请选择支付方式 (1: 现金, 2: 支付宝, 3: 微信, 4: 信用卡): ";
            int payment_choice;
            cin >> payment_choice;

            switch (payment_choice) {
            case 1:
                payment_method = "现金";
                cout << "请输入现金支付金额: ";
                cin >> cash_amount;
                break;
            case 2:
                payment_method = "支付宝";
                break;
            case 3:
                payment_method = "微信";
                break;
            case 4:
                payment_method = "信用卡";
                break;
            default:
                cerr << "无效的支付方式！操作已取消。" << endl;
                return;
            }

            string outputFile = outputDir + orderNumber + ".txt";

            // 生成小票
            generateReceipt(outputFile, dishes, dish_count, customer_count, payment_method, cash_amount, seating_fee);

            // 清空订单文件
            clearFileContent(inputFile);

            cout << "订单 " << orderNumber << " 已生成小票: " << outputFile << endl;
        }
        else {
            cout << "没有需要处理的菜品，或订单为空！" << endl;
        }
    }
}






