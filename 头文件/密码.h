#pragma once
namespace sys
{
	using namespace std;
	void password(string name)
	{
		cout << "������" << name << "������"<<endl;
		for (int i = 4; i >= 0; i--)
		{
			string input;
			cin >> input;
			if (checkPassword(name,input))
				return;
			if(i>0)
			cout << "�������,����" << i << "�λ���";
		}
		cout << "��������������࣬�ϵܣ������ѱ�ǿ���˳�������ϵ����Ա��������";
		exit(0);
	}
}
namespace sys {
    // ��������Ƿ���ȷ
    bool checkPassword(const string& username, const string& inputPassword) {
        string filepath = "���ݴ洢/�˺�/" + username + ".txt";
        ifstream file(filepath);

        if (!file.is_open()) {
            cerr << "�޷����ļ�: " << filepath << endl;
            return false;
        }

        string storedPassword;
        getline(file, storedPassword);
        file.close();

        return inputPassword == storedPassword;
    }

    // �޸�����
    bool changePassword(const string& username, const string& newPassword) {
        string filepath = "���ݴ洢/�˺�/" + username + ".txt";
        ofstream file(filepath, ofstream::out | ofstream::trunc);

        if (!file.is_open()) {
            cerr << "�޷����ļ�: " << filepath << endl;
            return false;
        }

        file << newPassword;
        file.close();
        return true;
    }
    void cpass1(const string& username)//����Ա��
    {
        string in;
        cout << "������������";
        cin >> in;
        changePassword(username, in);
        return;
    }
    void cpass2(const string& username)
    {
        void password(string username);
        string in;
        cout << "������������";
        cin >> in;
        changePassword(username, in);
        return;
    }
}