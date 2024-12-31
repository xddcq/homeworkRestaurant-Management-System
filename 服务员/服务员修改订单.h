#pragma once
namespace server
{
    void serverAddDishesToOrder(const string& order_file, const MenuItem menu[], int menu_size) {
        // �򿪶����ļ�
        fstream file(order_file, ios::in | ios::out);
        if (!file.is_open()) {
            cout << "�޷��򿪶����ļ�: " << order_file << endl;
            return;
        }

        // ��ȡ�������ݲ���ʾ
        string line;
        cout << "��ǰ��������:" << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }

        // ��Ӳ�Ʒ
        int item_number;
        cout << "\n������Ҫ��ӵĲ�Ʒ���: ";
        cin >> item_number;
        if (item_number < 1 || item_number > menu_size) {
            cout << "��Ч�Ĳ�Ʒ��š�" << endl;
            return;
        }

        const MenuItem& selected_item = menu[item_number - 1];
        cout << "��ѡ���Ʒ: " << selected_item.name << "���۸�: " << selected_item.price << " Ԫ\n";

        int quantity;
        string special_requests = "";
        cout << "����������: ";
        cin >> quantity;
        cin.ignore(); // ������뻺�����еĻ��з�

        special_requests = costomer::getSpecialRequests(menu[item_number - 1].type);
        // ��λ�ļ�ĩβ��д���²�Ʒ
        file.clear(); // ����ļ���״̬
        file.seekp(0, ios::end);

        file << left << setw(30) << selected_item.name
            << setw(10) << selected_item.price
            << setw(10) << quantity
            << setw(20) << special_requests
            << setw(20) << costomer::class_dishes(selected_item.type)
            << setw(20) << "δ���" << endl;

        cout << "��Ʒ�ѳɹ���ӵ�������" << endl;

        file.close();
    }
    void serveradd()
    {
        displayAvailableOrders();
        ifstream ss("���ݴ洢/��������/���.txt");
        int n_max;
        ss >> n_max;
        ss.close();
        ::MenuItem menu[MAX_MENU_ITEMS];
        int menu_num = ::loadMenuFromFile("���ݴ洢/menu.txt", menu);
        showMenu(menu, menu_num);
        while (1)
        {
            cout << "����������Ҫ��ӵĶ���,��0�˳�";
            int in = ::int_input(n_max, 0);
            if (in == 0)
                return;
            string filename = "���ݴ洢/��������/" + to_string(in) + ".txt";
            serverAddDishesToOrder(filename, menu, menu_num);
        }
    }
    void serverDeleteDishFromOrder(const string& order_file) {
        // �򿪶����ļ�
        ifstream file(order_file);
        if (!file.is_open()) {
            cout << "�޷��򿪶����ļ�: " << order_file << endl;
            return;
        }

        // ��ȡ�������ݲ����浽����
        string lines[150];
        int line_count = 0;
        string line;
        cout << "��ǰ��������:" << endl;
        while (getline(file, line) && line_count < 150) {
            lines[line_count++] = line;
            cout << line << endl;
        }
        ::separator(80);
        file.close();
        cout << endl << endl;
        // ���Ҳ�Ʒ���ֵ���ʼ��
        int dish_start = -1;
        for (int i = 0; i < line_count; ++i) {
            if (lines[i].find("��Ʒ��") != string::npos) {
                dish_start = i + 1;
                break;
            }
        }

        if (dish_start == -1 || dish_start >= line_count) {
            //    cerr << "������δ�ҵ���Ʒ���֡�" << endl;
            return;
        }

        // ��ʾ��Ʒ�б�
        cout << "\n��Ʒ�б�:" << endl;
        for (int i = dish_start; i < line_count; ++i) {
            cout << i - dish_start + 1 << ". " << lines[i] << endl;
        }

        // ѡ��Ҫɾ���Ĳ�Ʒ
        int dish_number;
        cout << "\n������Ҫɾ���Ĳ�Ʒ��� (����0�˳�): ";
        cin >> dish_number;

        if (dish_number <= 0 || dish_start + dish_number - 1 >= line_count) {
            cout << "��Ч�Ĳ�Ʒ��š�" << endl;
            return;
        }

        // ɾ��ָ����Ʒ
        for (int i = dish_start + dish_number - 1; i < line_count - 1; ++i) {
            lines[i] = lines[i + 1];
        }
        --line_count;
        cout << "��Ʒ�ѳɹ�ɾ����" << endl;

        // д���ļ�
        ofstream outfile(order_file, ios::trunc);
        if (!outfile.is_open()) {
            cout << "�޷�д�붩���ļ�: " << order_file << endl;
            return;
        }

        for (int i = 0; i < line_count; ++i) {
            outfile << lines[i] << endl;
        }

        outfile.close();
    }

    void serverDelete() {
        displayAvailableOrders();
        ifstream ss("���ݴ洢/��������/���.txt");
        int n_max;
        ss >> n_max;
        ss.close();

        while (1) {
            cout << "����������Ҫɾ����Ʒ�Ķ������, ��0�˳�: ";
            int in = ::int_input(n_max, 0);
            if (in == 0)
                return;

            string filename = "���ݴ洢/��������/" + to_string(in) + ".txt";
            serverDeleteDishFromOrder(filename);
        }
    }
    void displayAvailableOrders(const std::string& order_directory) {
        using namespace std;

        // ������ļ���ȡ��󶩵���
        ifstream seq_file(order_directory + "/���.txt");
        if (!seq_file.is_open()) {
            cerr << "�޷�������ļ�: " << order_directory + "/���.txt" << endl;
            return;
        }

        int max_order_number;
        seq_file >> max_order_number;
        seq_file.close();

        if (max_order_number <= 0) {
            cout << "��ǰû�п��õĶ�����" << endl;
            return;
        }

        cout << left << setw(15) << "�������" << setw(15) << "������" << setw(20) << "����" << endl;
        cout << string(50, '-') << endl;

        for (int i = 1; i <= max_order_number; ++i) {
            string file = order_directory + "/" + to_string(i) + ".txt";
            ifstream infile(file);
            if (!infile.is_open()) {
                continue; // ���������ڵ��ļ�
            }

            string line, table_number = "δ֪", name = "δ֪";

            // ��ȡ�����ź�������Ϣ
            while (getline(infile, line)) {
                if (line.find("������:") != string::npos) {
                    table_number = line.substr(line.find(":") + 1);
                    table_number.erase(0, table_number.find_first_not_of(" "));
                }
                else if (line.find("����:") != string::npos) {
                    name = line.substr(line.find(":") + 1);
                    name.erase(0, name.find_first_not_of(" "));
                    break;
                }
            }

            infile.close();

            cout << left << setw(15) << i
                << setw(15) << table_number
                << setw(20) << name << endl;
        }
    }
}
 