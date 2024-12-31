#pragma once
namespace sys
{
    using namespace std;

    // 去除字符串中的所有空格
    string removeSpaces(const string& str) {
        string result = str;
        result.erase(remove(result.begin(), result.end(), ' '), result.end());
        return result;
    }

    // 处理单个文件内容
    void processFile(const string& filename, DishStats dishStatistics[], int& dishCount, double& totalRevenue) {
        ifstream receiptFile(filename);
        if (!receiptFile.is_open()) {
            //cerr << "无法打开文件: " << filename << endl;
            return;
        }

        string line;
        while (getline(receiptFile, line)) {
            // 处理菜品数据行
            if (line.find("菜品名") != string::npos) {
                // 跳过表头和分隔线
                getline(receiptFile, line); // 跳过表头
                getline(receiptFile, line); // 跳过分隔线

                while (!line.empty() && line.find("餐位费") == string::npos && line.find("总价") == string::npos) {
                    istringstream ss(line);
                    string name, unitPriceStr, quantityStr, specialRequest, status;

                    // 解析每一行
                    ss >> name >> unitPriceStr >> quantityStr >> specialRequest >> status;

                    if (ss.fail()) {
                        //cerr << "行解析失败，跳过: " << line << endl;
                        break;
                    }

                    // 去掉空格
                    name = removeSpaces(name);
                    quantityStr = removeSpaces(quantityStr);
                    status = removeSpaces(status);

                    // 检查数量是否为数字
                    if (!all_of(quantityStr.begin(), quantityStr.end(), ::isdigit)) {
                        //cerr << "无效数量字段: " << quantityStr << endl;
                        break;
                    }

                    int quantity = stoi(quantityStr);

                    // 查找或添加菜品统计
                    bool found = false;
                    for (int i = 0; i < dishCount; ++i) {
                        if (dishStatistics[i].name == name) {
                            if (status == "已出菜") {
                                dishStatistics[i].completed_count += quantity;
                            }
                            else {
                                dishStatistics[i].pending_count += quantity;
                            }
                            found = true;
                            break;
                        }
                    }

                    // 如果菜品不存在，新增一条统计信息
                    if (!found) {
                        if (dishCount >= 500) {
                            cerr << "菜品统计数量超过限制，无法添加新菜品: " << name << endl;
                            break;
                        }
                        dishStatistics[dishCount++] = { name, (status == "已出菜" ? quantity : 0), (status != "已出菜" ? quantity : 0) };
                    }

                    // 读取下一行
                    if (!getline(receiptFile, line)) break;
                }
            }

            // 处理总价行
            if (line.find("总价:") != string::npos) {
                string totalPriceStr = line.substr(line.find(":") + 1);
                try {
                    totalRevenue += stod(totalPriceStr);
                }
                catch (const invalid_argument&) {
                    cerr << "无效总价字段: " << totalPriceStr << endl;
                }
            }
        }
        receiptFile.close();
    }

    // 主函数
    void analyzeReceipts(const string& folderPath) {
        DishStats dishStatistics[500] = {}; // 最大支持 500 种菜品
        int dishCount = 0;                  // 当前统计的菜品数量
        double totalRevenue = 0.0;          // 总收入
        int totalReceipts = 0;              // 小票总数

        // 遍历文件名 1.txt 到 500.txt
        for (int i = 1; i <= 500; ++i) {
            string filename = folderPath + "/" + to_string(i) + ".txt";
            ifstream testFile(filename);
            if (testFile.is_open()) {
                ++totalReceipts; // 成功打开文件
                processFile(filename, dishStatistics, dishCount, totalRevenue);
            }
        }

        // 输出统计结果
        cout << "================ 小票统计数据 ================\n";
        cout << "总小票数: " << totalReceipts << "\n";
        cout << "总收入: " << fixed << setprecision(2) << totalRevenue << " 元\n";
        cout << "---------------------------------------------\n";
        cout << left << setw(30) << "菜品名"
            << setw(15) << "完成数量"
            << setw(15) << "未完成数量" << "\n";
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
