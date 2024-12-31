#pragma once
namespace sys
{
	using namespace std;
	void password(string name)
	{
		cout << "请输入" << name << "的密码"<<endl;
		for (int i = 4; i >= 0; i--)
		{
			string input;
			cin >> input;
			if (checkPassword(name,input))
				return;
			if(i>0)
			cout << "密码错误,还有" << i << "次机会";
		}
		cout << "密码输入次数过多，老弟，程序已被强制退出，请联系管理员重置密码";
		exit(0);
	}
}
namespace sys {
    // 检查密码是否正确
    bool checkPassword(const string& username, const string& inputPassword) {
        string filepath = "数据存储/账号/" + username + ".txt";
        ifstream file(filepath);

        if (!file.is_open()) {
            cerr << "无法打开文件: " << filepath << endl;
            return false;
        }

        string storedPassword;
        getline(file, storedPassword);
        file.close();

        return inputPassword == storedPassword;
    }

    // 修改密码
    bool changePassword(const string& username, const string& newPassword) {
        string filepath = "数据存储/账号/" + username + ".txt";
        ofstream file(filepath, ofstream::out | ofstream::trunc);

        if (!file.is_open()) {
            cerr << "无法打开文件: " << filepath << endl;
            return false;
        }

        file << newPassword;
        file.close();
        return true;
    }
    void cpass1(const string& username)//管理员端
    {
        string in;
        cout << "请输入新密码";
        cin >> in;
        changePassword(username, in);
        return;
    }
    void cpass2(const string& username)
    {
        void password(string username);
        string in;
        cout << "请输入新密码";
        cin >> in;
        changePassword(username, in);
        return;
    }
}