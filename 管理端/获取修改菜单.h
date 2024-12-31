#pragma once
#define max_int 0x7fffffff
using namespace std;
int loadMenuFromFile(const string& filename, MenuItem menu[]) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "�޷��򿪲˵��ļ�" << endl;
        return 0;
    }
    size_t itemCount;
    file >> itemCount;
    file.ignore(); // ���Ի��з�
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
        return"����";
    else if (n == 301)
        return "С�Ի���ʳ";
    else
        return "������";
}
// ��ʾ�˵�
void showMenu(MenuItem menu[], int itemCount) 
{
    cout << "��ǰ�˵�:" << endl;
    cout <<left<<setw(10) <<"���" <<setw(30)<< "����"<<setw(20) << "�۸�" << setw(20)<< "����"<<endl;
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
        cerr << "�˵�����ʧ�ܣ�" << endl;
        return;
    }
    bubbleSort(menu, menu + loadedItems-1, cmd1);
    showMenu(menu, loadedItems);

    cout << "����������Ҫ��Ϊ����/δ�����ı��: ";
    int n = int_input(loadedItems) - 1;

    // �л���Ʒ������״̬
    if (menu[n].type %10== 1) {
        menu[n].type += 1; // δ���� -> ����
        cout << "�ѽ� " << menu[n].name << " ��Ϊ ������" << endl;
    }
    else if (menu[n].type%10 == 2) {
        menu[n].type -= 1; // ���� -> δ����
        cout << "�ѽ� " << menu[n].name << " ��Ϊ δ������" << endl;
    }
    else {
        cerr << "����: ��Ʒ״̬�Ƿ���" << endl;
        return;
    }

    // д���ļ�
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "�޷�д���ļ�: " << filename << endl;
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

// ��ȡ�˵�
void loadMenu(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "�޷����ļ�: " << filename << endl;
        return;
    }

    file >> itemCount;
    file.ignore(); // ���Ի��з�

    for (int i = 0; i < itemCount; ++i) {
        file >> menu[i].id;
        file.ignore(); // ���Ի��з�
        getline(file, menu[i].name);
        file >> menu[i].price;
        file >> menu[i].status;
        file.ignore(); // ���Ի��з�
    }

    file.close();
}

// ����˵�
void saveMenu(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "�޷����ļ�: " << filename << endl;
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

// ��ʾ�˵�
void displayMenu() {
    cout << "\n��ǰ�˵�:\n";
    for (int i = 0; i < itemCount; ++i) {
        cout << "���: " << menu[i].id
            << ", ����: " << menu[i].name
            << ", �۸�: " << menu[i].price
            << ", ״̬: " << menu[i].status << endl;
    }
}
    // ��Ӳ�Ʒ
    void addMenuItem() {
        if (itemCount >= MAX_ITEMS) {
            cout << "�˵��������޷���Ӹ����Ʒ��\n";
            return;
        }

        MenuItem newItem;
        cout << "�������²�Ʒ��Ϣ:\n";
        cout << "���: ";
        cin >> newItem.id;
        cin.ignore();
        cout << "����: ";
        getline(cin, newItem.name);
        cout << "�۸�: ";
        cin >> newItem.price;
        cout << "״̬ (����: 101, 201): ";
        cin >> newItem.status;

        menu[itemCount++] = newItem;
        cout << "��Ʒ��ӳɹ�!\n";
    }

    // ɾ����Ʒ
    void deleteMenuItem() {
        int idToDelete;
        cout << "������Ҫɾ���Ĳ�Ʒ���: ";
        cin >> idToDelete;

        int index = -1;
        for (int i = 0; i < itemCount; ++i) {
            if (menu[i].id == idToDelete) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "δ�ҵ�ָ����ŵĲ�Ʒ��\n";
            return;
        }

        for (int i = index; i < itemCount - 1; ++i) {
            menu[i] = menu[i + 1];
        }

        --itemCount;
        cout << "��Ʒɾ���ɹ�!\n";
    }

    int change_menu() {
        string filename = "���ݴ洢/menu.txt";
        loadMenu(filename);

        int choice;
        do {
            cout << "\n�˵�����ϵͳ\n";
            cout << "1. ��ʾ�˵�\n";
            cout << "2. ��Ӳ�Ʒ\n";
            cout << "3. ɾ����Ʒ\n";
            cout << "4. ���沢�˳�\n";
            cout << "���������ѡ��: ";
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
                cout << "�����ѱ��棬�����˳�...\n";
                break;
            default:
                cout << "��Чѡ�������ԡ�\n";
            }
        } while (choice != 4);

        return 0;
    }
}
