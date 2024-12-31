#pragma once
using namespace std;
void readFileByLine(string filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filePath << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}
//读取数字
int readNumberFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "无法打开文件：" << filename << endl;
        return -1; // 返回-1表示错误
    }

    int number;
    inputFile >> number;
    if (inputFile.fail()) {
        cerr << "文件中没有有效数字或读取失败。" << endl;
        return -1; // 返回-1表示错误
    }

    inputFile.close();
    return number;
}

// 修改文件中的数字
void writeNumberToFile(const string& filename, int newNumber) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "无法打开文件：" << filename << endl;
        return;
    }
    outputFile << newNumber;
    if (outputFile.fail()) {
        cerr << "写入文件失败。" << endl;
    }
    outputFile.close();
}