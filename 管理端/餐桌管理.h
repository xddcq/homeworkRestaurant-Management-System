namespace sys
{
    using namespace std;

    const int MAX_TABLES = 100;

    struct Table {
        int table_number;
        int customer_count;
        int status; // 1: ����, 2: ����
    };

    // ��ȡ������Ϣ�ļ�
    bool readTableInfo(const string& filepath, Table tables[], int& table_count) {
        ifstream file(filepath);
        if (!file.is_open()) {
            cerr << "�޷����ļ�: " << filepath << endl;
            return false;
        }

        string line;
        if (getline(file, line)) {
            table_count = stoi(line); // ��ȡ��������
            if (table_count > MAX_TABLES) {
                cerr << "���������������ֵ (" << MAX_TABLES << ")��\n";
                return false;
            }
        }
        else {
            cerr << "�ļ���ʽ����: �޷���ȡ����������" << endl;
            return false;
        }

        int index = 0;
        while (getline(file, line) && index < table_count) {
            stringstream ss(line);
            ss >> tables[index].table_number >> tables[index].customer_count >> tables[index].status;
            ++index;
        }

        file.close();
        return true;
    }

    // ��ʾ���в���״̬
    void displayTableStatus(const Table tables[], int table_count) {
        cout << "================ ����״̬ ================\n";
        cout << left << setw(10) << "����" << setw(15) << "�Ͳ�����" << setw(10) << "״̬" << "\n";
        cout << "------------------------------------------\n";

        for (int i = 0; i < table_count; ++i) {
            cout << left << setw(10) << tables[i].table_number
                << setw(15) << tables[i].customer_count
                << (tables[i].status == 1 ? "����" : "����") << "\n";
        }

        cout << "==========================================\n";
    }

    // �޸�ָ��������״̬
    void modifyTableStatus(Table tables[], int table_count, int table_number, int new_status) {
        for (int i = 0; i < table_count; ++i) {
            if (tables[i].table_number == table_number) {
                tables[i].status = new_status;
                cout << "���� " << table_number << " ��״̬���޸�Ϊ "
                    << (new_status == 1 ? "����" : "����") << "��\n";
                return;
            }
        }
        cerr << "δ�ҵ����� " << table_number << "��\n";
    }

    // �����޸����в�����״̬
    void batchModifyTableStatus(Table tables[], int table_count, int new_status) {
        for (int i = 0; i < table_count; ++i) {
            tables[i].status = new_status;
        }
        cout << "���в�����״̬���޸�Ϊ "
            << (new_status == 1 ? "����" : "����") << "��\n";
    }

    // ���������Ϣ���ļ�
    bool saveTableInfo(const string& filepath, const Table tables[], int table_count) {
        ofstream file(filepath);
        if (!file.is_open()) {
            cerr << "�޷������ļ�: " << filepath << endl;
            return false;
        }

        file << table_count << "\n"; // д���������
        for (int i = 0; i < table_count; ++i) {
            file << tables[i].table_number << " " << tables[i].customer_count << " " << tables[i].status << "\n";
        }

        file.close();
        return true;
    }

    // ��������������
    void manageTables() {
        string filepath = "���ݴ洢/λ��.txt";
        Table tables[MAX_TABLES];
        int table_count = 0;

        // ��ȡ������Ϣ
        if (!readTableInfo(filepath, tables, table_count)) {
            return;
        }

        int choice;
        do {
            cout << "\n======== ��������ϵͳ ========\n";
            cout << "1. ��ʾ���в���״̬\n";
            cout << "2. �޸�ָ������״̬\n";
            cout << "3. �����޸����в���״̬\n";
            cout << "4. ���沢�˳�\n";
            cout << "������ѡ��: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayTableStatus(tables, table_count);
                break;
            case 2: {
                int table_number, new_status;
                cout << "����������: ";
                cin >> table_number;
                cout << "��������״̬ (1: ����, 2: ����): ";
                cin >> new_status;
                if (new_status == 1 || new_status == 2) {
                    modifyTableStatus(tables, table_count, table_number, new_status);
                }
                else {
                    cerr << "��Ч״̬��\n";
                }
                break;
            }
            case 3: {
                int new_status;
                cout << "��������״̬ (1: ����, 2: ����): ";
                cin >> new_status;
                if (new_status == 1 || new_status == 2) {
                    batchModifyTableStatus(tables, table_count, new_status);
                }
                else {
                    cerr << "��Ч״̬��\n";
                }
                break;
            }
            case 4:
                if (saveTableInfo(filepath, tables, table_count)) {
                    cout << "������Ϣ�ѱ��档\n";
                }
                break;
            default:
                cerr << "��Чѡ�\n";
                break;
            }
        } while (choice != 4);
    }
}
