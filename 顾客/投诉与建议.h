#pragma once
void saveFeedback() {
    int choice;
    string content;

    // ��ʾ�û�ѡ��Ͷ�߻���
    cout << "��ѡ��Ҫ�ύ������:" << endl;
    cout << "1. Ͷ��" << endl;
    cout << "2. ����" << endl;
    cout << "������ѡ�� (1 �� 2): ";
    cin >> choice;
    cin.ignore();  // ����������Ļ��з�

    // ��ʾ�û���������
    cout << "�������������� (���500���ַ�): ";
    getline(cin, content);

    ofstream file;

    // �����û�ѡ������д�벻ͬ���ļ�
    if (choice == 1) {
        file.open("���ݴ洢/Ͷ��.txt", ios::app);  // ��׷��ģʽ��Ͷ���ļ�
        if (!file) {
            cout << "�޷���Ͷ���ļ���" << endl;
            return;
        }
        file << "Ͷ������:\n" << content << "\n\n";
        cout << "����Ͷ�����ύ��лл��" << endl;
    }
    else if (choice == 2) {
        file.open("���ݴ洢/����.txt", ios::app);  // ��׷��ģʽ�򿪽����ļ�
        if (!file) {
            cout << "�޷��򿪽����ļ���" << endl;
            return;
        }
        file << "��������:\n" << content << "\n\n";
        cout << "���Ľ������ύ��лл��" << endl;
    }
    else {
        cout << "��Ч��ѡ��������ѡ��" << endl;
        return;
    }

    file.close();  // �ر��ļ�
}
