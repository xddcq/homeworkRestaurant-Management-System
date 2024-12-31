#pragma once
void saveFeedback() {
    int choice;
    string content;

    // 提示用户选择投诉或建议
    cout << "请选择要提交的内容:" << endl;
    cout << "1. 投诉" << endl;
    cout << "2. 建议" << endl;
    cout << "请输入选择 (1 或 2): ";
    cin >> choice;
    cin.ignore();  // 清除缓冲区的换行符

    // 提示用户输入内容
    cout << "请输入您的内容 (最多500个字符): ";
    getline(cin, content);

    ofstream file;

    // 根据用户选择将内容写入不同的文件
    if (choice == 1) {
        file.open("数据存储/投诉.txt", ios::app);  // 以追加模式打开投诉文件
        if (!file) {
            cout << "无法打开投诉文件！" << endl;
            return;
        }
        file << "投诉内容:\n" << content << "\n\n";
        cout << "您的投诉已提交，谢谢！" << endl;
    }
    else if (choice == 2) {
        file.open("数据存储/建议.txt", ios::app);  // 以追加模式打开建议文件
        if (!file) {
            cout << "无法打开建议文件！" << endl;
            return;
        }
        file << "建议内容:\n" << content << "\n\n";
        cout << "您的建议已提交，谢谢！" << endl;
    }
    else {
        cout << "无效的选择，请重新选择！" << endl;
        return;
    }

    file.close();  // 关闭文件
}
