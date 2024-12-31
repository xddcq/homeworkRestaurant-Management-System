#pragma once
namespace sys
{
    using namespace std;

    // ȥ���ַ����е����пո�
    string removeSpaces(const string& str) {
        string result = str;
        result.erase(remove(result.begin(), result.end(), ' '), result.end());
        return result;
    }

    // �������ļ�����
    void processFile(const string& filename, DishStats dishStatistics[], int& dishCount, double& totalRevenue) {
        ifstream receiptFile(filename);
        if (!receiptFile.is_open()) {
            //cerr << "�޷����ļ�: " << filename << endl;
            return;
        }

        string line;
        while (getline(receiptFile, line)) {
            // �����Ʒ������
            if (line.find("��Ʒ��") != string::npos) {
                // ������ͷ�ͷָ���
                getline(receiptFile, line); // ������ͷ
                getline(receiptFile, line); // �����ָ���

                while (!line.empty() && line.find("��λ��") == string::npos && line.find("�ܼ�") == string::npos) {
                    istringstream ss(line);
                    string name, unitPriceStr, quantityStr, specialRequest, status;

                    // ����ÿһ��
                    ss >> name >> unitPriceStr >> quantityStr >> specialRequest >> status;

                    if (ss.fail()) {
                        //cerr << "�н���ʧ�ܣ�����: " << line << endl;
                        break;
                    }

                    // ȥ���ո�
                    name = removeSpaces(name);
                    quantityStr = removeSpaces(quantityStr);
                    status = removeSpaces(status);

                    // ��������Ƿ�Ϊ����
                    if (!all_of(quantityStr.begin(), quantityStr.end(), ::isdigit)) {
                        //cerr << "��Ч�����ֶ�: " << quantityStr << endl;
                        break;
                    }

                    int quantity = stoi(quantityStr);

                    // ���һ���Ӳ�Ʒͳ��
                    bool found = false;
                    for (int i = 0; i < dishCount; ++i) {
                        if (dishStatistics[i].name == name) {
                            if (status == "�ѳ���") {
                                dishStatistics[i].completed_count += quantity;
                            }
                            else {
                                dishStatistics[i].pending_count += quantity;
                            }
                            found = true;
                            break;
                        }
                    }

                    // �����Ʒ�����ڣ�����һ��ͳ����Ϣ
                    if (!found) {
                        if (dishCount >= 500) {
                            cerr << "��Ʒͳ�������������ƣ��޷�����²�Ʒ: " << name << endl;
                            break;
                        }
                        dishStatistics[dishCount++] = { name, (status == "�ѳ���" ? quantity : 0), (status != "�ѳ���" ? quantity : 0) };
                    }

                    // ��ȡ��һ��
                    if (!getline(receiptFile, line)) break;
                }
            }

            // �����ܼ���
            if (line.find("�ܼ�:") != string::npos) {
                string totalPriceStr = line.substr(line.find(":") + 1);
                try {
                    totalRevenue += stod(totalPriceStr);
                }
                catch (const invalid_argument&) {
                    cerr << "��Ч�ܼ��ֶ�: " << totalPriceStr << endl;
                }
            }
        }
        receiptFile.close();
    }

    // ������
    void analyzeReceipts(const string& folderPath) {
        DishStats dishStatistics[500] = {}; // ���֧�� 500 �ֲ�Ʒ
        int dishCount = 0;                  // ��ǰͳ�ƵĲ�Ʒ����
        double totalRevenue = 0.0;          // ������
        int totalReceipts = 0;              // СƱ����

        // �����ļ��� 1.txt �� 500.txt
        for (int i = 1; i <= 500; ++i) {
            string filename = folderPath + "/" + to_string(i) + ".txt";
            ifstream testFile(filename);
            if (testFile.is_open()) {
                ++totalReceipts; // �ɹ����ļ�
                processFile(filename, dishStatistics, dishCount, totalRevenue);
            }
        }

        // ���ͳ�ƽ��
        cout << "================ СƱͳ������ ================\n";
        cout << "��СƱ��: " << totalReceipts << "\n";
        cout << "������: " << fixed << setprecision(2) << totalRevenue << " Ԫ\n";
        cout << "---------------------------------------------\n";
        cout << left << setw(30) << "��Ʒ��"
            << setw(15) << "�������"
            << setw(15) << "δ�������" << "\n";
        cout << "---------------------------------------------\n";

        for (int i = 0; i < dishCount; ++i) {
            cout << left << setw(30) << dishStatistics[i].name
                << setw(15) << dishStatistics[i].completed_count
                << setw(15) << dishStatistics[i].pending_count << "\n";
        }
        cout << "=============================================\n";
        system("pause");
    }

}
