#pragma once
#define max_int 0x7fffffff
using namespace std;
int loadMenuFromFile(const string& filename, MenuItem menu[]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开菜单文件" << endl;
        return 0;
    }
    size_t itemCount;
    file >> itemCount;
    file.ignore(); // 忽略换行符
    string line;
    size_t loadedItems = 0;
    for (size_t i = 0; i < itemCount && i < MAX_MENU_ITEMS; ++i) {
        MenuItem item;

        getline(file, line);
        item.id = stoi(line);

        getline(file, item.name);

        getline(file, line);
        item.price = stod(line);

        getline(file, line);
        item.type = stoi(line);

        menu[loadedItems++] = item;
    }
    file.close();
    return itemCount;
}
string showmenutype(int n)
{
    if (n == 101 || n == 201)
        return"正餐";
    else if (n == 301)
        return "小吃或零食";
    else
        return "已售罄";
}
// 显示菜单
void showMenu(MenuItem menu[], int itemCount) 
{
    cout << "当前菜单:" << endl;
    cout <<left<<setw(10) <<"编号" <<setw(30)<< "名称"<<setw(20) << "价格" << setw(20)<< "种类"<<endl;
    separator(80);
    cout << endl;
    for (int i = 0; i < itemCount; ++i) {
        cout <<left<< setw(10) << menu[i].id
            << setw(30) << menu[i].name
            << setw(20)<< menu[i].price <<setw(20)<<showmenutype(menu[i].type) << endl;
    }
}
bool cmd1(MenuItem a, MenuItem b)
{
    return a.id < b.id;
}
void changemunu(const string& filename) {
    MenuItem menu[MAX_MENU_ITEMS];
    int loadedItems = loadMenuFromFile(filename, menu);
    if (loadedItems == 0) {
        cerr << "菜单加载失败！" << endl;
        return;
    }
    bubbleSort(menu, menu + loadedItems-1, cmd1);
    showMenu(menu, loadedItems);

    cout << "请输入你想要改为售罄/未售罄的编号: ";
    int n = int_input(loadedItems) - 1;

    // 切换菜品的售罄状态
    if (menu[n].type %10== 1) {
        menu[n].type += 1; // 未售罄 -> 售罄
        cout << "已将 " << menu[n].name << " 改为 售罄。" << endl;
    }
    else if (menu[n].type%10 == 2) {
        menu[n].type -= 1; // 售罄 -> 未售罄
        cout << "已将 " << menu[n].name << " 改为 未售罄。" << endl;
    }
    else {
        cerr << "错误: 菜品状态非法！" << endl;
        return;
    }

    // 写回文件
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "无法写入文件: " << filename << endl;
        return;
    }

    file << loadedItems << endl;
    for (int i = 0; i < loadedItems; i++) {
        file<<menu[i].id+1<<endl;
        file << menu[i].name << endl;
        file << menu[i].price << endl;
        file << menu[i].type << endl;
    }
}
namespace sys
{
    using namespace std;
struct MenuItem {
    int id;
    string name;
    int price;
    int status;
};

const int MAX_ITEMS = 500;
MenuItem menu[MAX_ITEMS];
int itemCount = 0;

// 读取菜单
void loadMenu(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    file >> itemCount;
    file.ignore(); // 忽略换行符

    for (int i = 0; i < itemCount; ++i) {
        file >> menu[i].id;
        file.ignore(); // 忽略换行符
        getline(file, menu[i].name);
        file >> menu[i].price;
        file >> menu[i].status;
        file.ignore(); // 忽略换行符
    }

    file.close();
}

// 保存菜单
void saveMenu(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    file << itemCount << endl;
    for (int i = 0; i < itemCount; ++i) {
        file << menu[i].id << endl;
        file << menu[i].name << endl;
        file << menu[i].price << endl;
        file << menu[i].status << endl;
    }

    file.close();
}

// 显示菜单
void displayMenu() {
    cout << "\n当前菜单:\n";
    for (int i = 0; i < itemCount; ++i) {
        cout << "编号: " << menu[i].id
            << ", 名称: " << menu[i].name
            << ", 价格: " << menu[i].price
            << ", 状态: " << menu[i].status << endl;
    }
}
    // 添加菜品
    void addMenuItem() {
        if (itemCount >= MAX_ITEMS) {
            cout << "菜单已满，无法添加更多菜品。\n";
            return;
        }

        MenuItem newItem;
        cout << "请输入新菜品信息:\n";
        cout << "编号: ";
        cin >> newItem.id;
        cin.ignore();
        cout << "名称: ";
        getline(cin, newItem.name);
        cout << "价格: ";
        cin >> newItem.price;
        cout << "状态 (例如: 101, 201): ";
        cin >> newItem.status;

        menu[itemCount++] = newItem;
        cout << "菜品添加成功!\n";
    }

    // 删除菜品
    void deleteMenuItem() {
        int idToDelete;
        cout << "请输入要删除的菜品编号: ";
        cin >> idToDelete;

        int index = -1;
        for (int i = 0; i < itemCount; ++i) {
            if (menu[i].id == idToDelete) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "未找到指定编号的菜品。\n";
            return;
        }

        for (int i = index; i < itemCount - 1; ++i) {
            menu[i] = menu[i + 1];
        }

        --itemCount;
        cout << "菜品删除成功!\n";
    }

    int change_menu() {
        string filename = "数据存储/menu.txt";
        loadMenu(filename);

        int choice;
        do {
            cout << "\n菜单管理系统\n";
            cout << "1. 显示菜单\n";
            cout << "2. 添加菜品\n";
            cout << "3. 删除菜品\n";
            cout << "4. 保存并退出\n";
            cout << "请输入你的选择: ";
            cin >> choice;

            switch (choice) {
            case 1:
                displayMenu();
                break;
            case 2:
                addMenuItem();
                break;
            case 3:
                deleteMenuItem();
                break;
            case 4:
                saveMenu(filename);
                cout << "更改已保存，正在退出...\n";
                break;
            default:
                cout << "无效选择，请重试。\n";
            }
        } while (choice != 4);

        return 0;
    }
}
