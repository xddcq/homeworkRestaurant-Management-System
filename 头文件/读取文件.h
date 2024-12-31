#pragma once
using namespace std;
void readFileByLine(string filePath) {
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "�޷����ļ�: " << filePath << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}
//��ȡ����
int readNumberFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "�޷����ļ���" << filename << endl;
        return -1; // ����-1��ʾ����
    }

    int number;
    inputFile >> number;
    if (inputFile.fail()) {
        cerr << "�ļ���û����Ч���ֻ��ȡʧ�ܡ�" << endl;
        return -1; // ����-1��ʾ����
    }

    inputFile.close();
    return number;
}

// �޸��ļ��е�����
void writeNumberToFile(const string& filename, int newNumber) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "�޷����ļ���" << filename << endl;
        return;
    }
    outputFile << newNumber;
    if (outputFile.fail()) {
        cerr << "д���ļ�ʧ�ܡ�" << endl;
    }
    outputFile.close();
}