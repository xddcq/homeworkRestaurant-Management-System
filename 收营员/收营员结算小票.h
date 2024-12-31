#pragma once
namespace cashier
{
#define MAX_item 500
    // ��ȡ�����ļ�����ȡ��Ʒ��Ϣ
    int readWaiterFile(const string& filepath, cashier::Dish dishes[], int& start_index, int& customer_count) {
        ifstream file(filepath);

        if (!file.is_open()|| file.tellg() == 0) {
            cerr << "�޷����ļ�: " << filepath << endl;
            return -1;
        }

        string line, table_number;
        while (getline(file, line)) {
            // ��ȡ������
            if (line.find("������:") != string::npos) {
                table_number = line.substr(line.find(":") + 1);
                table_number.erase(remove(table_number.begin(), table_number.end(), ' '), table_number.end());
            }
            // ��ȡ�˿�����
            else if (line.find("����:") != string::npos) {
                customer_count = stoi(line.substr(line.find(":") + 1));
            }

            // ���Ҳ�Ʒ��ͷ
            if (line.find("��Ʒ��") != string::npos) {
                // ������ͷ�кͷָ���
                getline(file, line);
                while (getline(file, line) && !line.empty()) {
                    stringstream ss(line);
                    string name, special_requests, type, status;
                    double price;
                    int quantity;

                    // ���̶���Ƚ�������
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

                    // �����Ʒ״̬�� "�����"����洢������
                    if (status == "�����" && start_index < MAX_item) {
                        dishes[start_index++] = { name, table_number, price, quantity, special_requests, type, status };
                    }
                }
            }
        }

        file.close();
        return 0;
    }
    // ����ļ�����
    void clearFileContent(const string& filepath) {
        ofstream file(filepath, ofstream::out | ofstream::trunc);
        if (!file.is_open()) {
            cerr << "�޷�����ļ�: " << filepath << endl;
        }
        file.close();
    }

    // ���ļ���ȡ��λ��
    double readSeatingFee(const string& filepath) {
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "�޷��򿪲�λ���ļ�: " << filepath << endl;
            return 0.0;
        }

        double seating_fee = 0.0;
        file >> seating_fee;
        file.close();
        return seating_fee;
    }

    // Ԥ��СƱ
    void previewReceipt(const Dish dishes[], int count, int customer_count, double seating_fee) {
        double total_price = 0.0;

        // �����ܼۣ�������״̬Ϊ "�����" �Ĳ�Ʒ
        for (int i = 0; i < count; ++i) {
            if (dishes[i].status == "�����") {
                total_price += dishes[i].price * dishes[i].quantity;
            }
        }

        // ����ܼ۲���500Ԫ�����Ӳ�λ��
        if (total_price < 500) {
            total_price += customer_count * seating_fee;
        }

        // ���СƱ���ݵ�����̨
        cout << "================ СƱԤ�� ================\n";
        cout << "������: " << (count > 0 ? dishes[0].table_number : "δ֪") << "\n\n";
        cout << left << setw(30) << "��Ʒ��" << setw(10) << "����" << setw(10) << "����" << setw(20) << "����Ҫ��" << setw(10) << "״̬" << "\n";
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
            cout << "��λ��: " << fixed << setprecision(2) << customer_count * seating_fee << " Ԫ\n";
        }
        cout << "�ܼ�: " << fixed << setprecision(2) << total_price << " Ԫ\n";
        cout << "=============================================\n";
    }

    // ����СƱ��д���ļ�
    void generateReceipt(const string& outputPath, const Dish dishes[], int count, int customer_count, const string& payment_method, double cash, double seating_fee) {
        ofstream receipt(outputPath);

        if (!receipt.is_open()) {
            cerr << "�޷�����СƱ�ļ�: " << outputPath << endl;
            return;
        }

        double total_price = 0.0;

        // �����ܼۣ�������״̬Ϊ "�����" �Ĳ�Ʒ
        for (int i = 0; i < count; ++i) {
            if (dishes[i].status == "�����") {
                total_price += dishes[i].price * dishes[i].quantity;
            }
        }

        // ����ܼ۲���500Ԫ�����Ӳ�λ��
        double seating_fee_total = 0.0;
        if (total_price < 500) {
            seating_fee_total = customer_count * seating_fee;
            total_price += seating_fee_total;
        }

        double total_due = total_price;
        double change = 0.0;

        // ������ֽ�֧������������
        if (payment_method == "�ֽ�") {
            while (cash < total_due) {
                cerr << "�ֽ�����֧���ܶ����������" << endl;
                cin >> cash;
            }
            change = cash - total_due;
        }

        // ���СƱ����
        receipt << "================ СƱ ================\n";
        receipt << "������: " << (count > 0 ? dishes[0].table_number : "δ֪") << "\n";
        receipt << "֧����ʽ: " << payment_method << "\n";
        if (payment_method == "�ֽ�") {
            receipt << "ʵ�ս��: " << fixed << setprecision(2) << cash << " Ԫ\n";
            receipt << "������: " << fixed << setprecision(2) << change << " Ԫ\n";
        }
        receipt << "\n";

        receipt << left << setw(30) << "��Ʒ��" << setw(10) << "����" << setw(10) << "����" << setw(20) << "����Ҫ��" << setw(10) << "״̬" << "\n";
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
            receipt << "��λ��: " << fixed << setprecision(2) << seating_fee_total << " Ԫ\n";
        }
        receipt << "�ܼ�: " << fixed << setprecision(2) << total_due << " Ԫ\n";
        receipt << "=============================================\n";

        receipt.close();
    }

    // �����������
    void cashier_recipet() {
        string inputDir = "���ݴ洢/��������/";
        string outputDir = "���ݴ洢/СƱ�洢/";
        string feeFile = "���ݴ洢/��λ��.txt";

        double seating_fee = readSeatingFee(feeFile);
        if (seating_fee <= 0) {
            cerr << "��λ���ļ�������Ч������ȡ����" << endl;
            return;
        }

        ::readallfile();
        cout << "������Ҫ����Ķ������: ";
        string orderNumber;
        cin >> orderNumber;

        string inputFile = inputDir + orderNumber + ".txt";

        // ��鶩���ļ��Ƿ����
        ifstream checkFile(inputFile);
        if (!checkFile.is_open()) {
            cerr << "�����ļ� " << inputFile << " �����ڣ�" << endl;
            return;
        }
        checkFile.close();

        Dish dishes[MAX_item];
        int dish_count = 0;
        int customer_count = 0; // �˿�����

        // ��ȡ�����ļ�
        if (readWaiterFile(inputFile, dishes, dish_count, customer_count) == 0) {
            // չʾСƱԤ��
            previewReceipt(dishes, dish_count, customer_count, seating_fee);

            // ȷ���Ƿ�����СƱ
            cout << "�Ƿ�ȷ������СƱ��(���� Y ȷ�ϣ�������ȡ��): ";
            string userInput;
            cin >> userInput;

            if (userInput != "Y" && userInput != "y") {
                cout << "������ȡ����" << endl;
                return;
            }

            // ѡ��֧����ʽ
            string payment_method;
            double cash_amount = 0.0;

            cout << "��ѡ��֧����ʽ (1: �ֽ�, 2: ֧����, 3: ΢��, 4: ���ÿ�): ";
            int payment_choice;
            cin >> payment_choice;

            switch (payment_choice) {
            case 1:
                payment_method = "�ֽ�";
                cout << "�������ֽ�֧�����: ";
                cin >> cash_amount;
                break;
            case 2:
                payment_method = "֧����";
                break;
            case 3:
                payment_method = "΢��";
                break;
            case 4:
                payment_method = "���ÿ�";
                break;
            default:
                cerr << "��Ч��֧����ʽ��������ȡ����" << endl;
                return;
            }

            string outputFile = outputDir + orderNumber + ".txt";

            // ����СƱ
            generateReceipt(outputFile, dishes, dish_count, customer_count, payment_method, cash_amount, seating_fee);

            // ��ն����ļ�
            clearFileContent(inputFile);

            cout << "���� " << orderNumber << " ������СƱ: " << outputFile << endl;
        }
        else {
            cout << "û����Ҫ����Ĳ�Ʒ���򶩵�Ϊ�գ�" << endl;
        }
    }
}






