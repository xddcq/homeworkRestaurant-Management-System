#include"��ʦ�ṹ��.h"   
namespace cook
{
    using namespace std;
    
    // ��Ʒ��Ϣ�ṹ��

    // ���ļ���ȡ��������
    int readOrderFile(const string& filepath, const string& order_number, cook::Dish dishes[], int start_index) {
        ifstream file(filepath);

        if (!file.is_open()) {
           // cerr << "�޷����ļ�: " << filepath << endl;//��Щ�ļ��򲻿���������
            return start_index;
        }

        string line, table_number;
        while (getline(file, line)) {
            if (line.find("����:") != string::npos) {
                table_number = line.substr(line.find(":") + 1); // ��ȡ����
            }

            // ��ȡ��Ʒ��ͷ֮�������
            if (line.find("��Ʒ��") != string::npos) {
                while (getline(file, line) && !line.empty()) {
                    stringstream ss(line);
                    string name, price, quantity, special_requests, type, status;

                    // ���̶���ȶ�ȡ����
                    ss >> setw(30) >> name >> setw(10) >> price >> setw(10) >> quantity
                        >> setw(20) >> special_requests >> setw(10) >> type >> setw(10) >> status;

                    // ������������ͣ��򱣴��Ʒ��Ϣ
                    if (type == "����" && start_index < 500) {
                        dishes[start_index++] = { name, table_number, order_number, special_requests, type, status };
                    }
                }
            }
        }

        file.close();
        return start_index;
    }

    // ���¶���״̬
    void updateOrderStatus(const string& filepath, const cook::Dish& dish) {
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "�޷����ļ�: " << filepath << endl;
            return;
        }

        stringstream buffer;
        string line;
        bool updated = false;

        while (getline(file, line)) {
            if (line.find(dish.name) != string::npos &&
                line.find(dish.status) != string::npos &&
                line.find("δ���") != string::npos) {
                line.replace(line.find("δ���"), 9, "�ѳ���");
                updated = true;
            }
            buffer << line << "\n";
        }

        file.close();

        if (updated) {
            ofstream output_file(filepath, ios::trunc);
            output_file << buffer.str();
            output_file.close();
            cout << "״̬�Ѹ���Ϊ���ѳ��ˡ���������� " << dish.order_number << "������ " << dish.table_number
                << "����Ʒ�� " << dish.name << endl;
        }
        else {
            cout << "δ�ҵ���Ҫ���µĲ�Ʒ��¼��" << endl;
        }
    }

    int cooker_cook() {
        string folder_path = "���ݴ洢/��������";
        string serial_file = folder_path + "/���.txt";

        // ��ȡ����ļ���ȷ����������
        ifstream serial_input(serial_file);
        if (!serial_input.is_open()) {
            cerr << "�޷���ȡ����ļ�: " << serial_file << endl;//��Щ�ļ��򲻿���������
            return 1;
        }

        int total_orders;
        serial_input >> total_orders;
        total_orders--;
        if (total_orders == 0)
        {
            cout << "��ʱû�ж���";
            return 0;
        }
        serial_input.close();

        cook::Dish dishes[500]; // �̶���С����
        int dish_count = 0;

        // �������ж����ļ�
        for (int i = 1; i <= total_orders && dish_count < 500; ++i) {
            string order_file = folder_path + "/" + to_string(i) + ".txt";
            dish_count = readOrderFile(order_file, to_string(i), dishes, dish_count);
        }

        // ����������Ͳ�Ʒ
        cout << left << setw(5) << "���" << setw(10) << "�������" << setw(10) << "����"
            << setw(30) << "��Ʒ��" << setw(20) << "����Ҫ��" << setw(10) << "״̬" << endl;
        cout << string(85, '-') << endl;

        for (int i = 0; i < dish_count; ++i) {
            cout << left << setw(5) << (i + 1) << setw(10) << dishes[i].order_number
                << setw(10) << dishes[i].table_number << setw(30) << dishes[i].name
                << setw(20) << dishes[i].special_requests << setw(10) << dishes[i].status << endl;
        }

        // �޸Ĳ�Ʒ״̬
        int dish_index;
        cout << "\n������Ҫ����״̬�Ĳ�Ʒ��ţ����� 0 ��������: ";
        while (cin >> dish_index && dish_index != 0) {
            if (dish_index < 1 || dish_index > dish_count) {
                cout << "��Ч����ţ����������롣" << endl;
            }
            else {
                Dish& selected_dish = dishes[dish_index - 1];
                if (selected_dish.status == "δ���") {
                    string filepath = folder_path + "/" + selected_dish.order_number + ".txt";
                    updateOrderStatus(filepath, selected_dish);
                    selected_dish.status = "�ѳ���"; // �����ڴ��е�״̬
                }
                else {
                    cout << "�ò�Ʒ�ѳ��ˣ��޷��ظ�����״̬��" << endl;
                }
            }
            cout << "\n������Ҫ����״̬�Ĳ�Ʒ��ţ����� 0 ��������: ";
        }

        return 0;
    }
}