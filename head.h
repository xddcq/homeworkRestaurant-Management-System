#pragma once
#pragma comment(linker, "/STACK:52428800,4096")
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include<algorithm>
#include <sstream>
#include <string>
#include<windows.h>
const int MAX_MENU_ITEMS = 150;
const int MAX_NUMBER = 50;
#include"�˿�/�ṹ��.h"
#include"��ʦ/��ʦ�ṹ��.h"
#include"ͷ�ļ�/չʾȫ���ļ�.h"
#define ��ͣ system("pause")
#define ���� system("cls")
namespace boss
{
    void boss();
}
namespace cook {
    int readOrderFile(const std::string& filepath, const std::string& order_number, cook::Dish dishes[], int start_index);
    void updateOrderStatus(const std::string& filepath, const cook::Dish& dish);
    int cooker_cook();
    void cook();
}
namespace server {
    int readWaiterFile(const std::string& filepath, cook::Dish dishes[], int start_index);
    int readWaiterFile(const std::string& filepath, cook::Dish dishes[], int start_index, const std::string& order_number);
    void markDishAsCompleted(const std::string& filepath, const cook::Dish& dish);
    int waiter_serve();
    void server();
    void displayAvailableOrders(const std::string& order_directory = "���ݴ洢/��������");
    void serverAddDishesToOrder(const std::string& order_file, const MenuItem menu[], int menu_size);
    void serveradd();
    void serverDeleteDishFromOrder(const std::string& order_file);
    void serverDelete();
}
namespace costomer {
    int updateSerialNumber(const std::string& filename);
    int customer();
    int getValidQuantity();
    int selectMenuItems(MenuItem menu[], int itemCount, Order& order);
    string special_requests_hot(int n);
    string getSpecialRequests(int type);
    void saveFeedback();
    void calculateTotal(Order& order);
    string class_dishes(int n);
    void getUserDetails(Order& order);
    void printOrderSummary(const Order& order);
    void addMenuItem(Order& order, const MenuItem menu[], int itemCount);
    void saveOrderToFile(const Order& order, int order_number);
    bool cmd1(const Table& a, const Table& b);
    int loadTablesFromFile(const string& filename, Table tables[], int maxTables);
    void saveTablesToFile(const string& filename, Table tables[], int tableCount);
    int assignTable(int customerCount, Table tables[], int tableCount, Order& order);
    void printAssignedTables(const Order& order);
    int select_table();
    int book_customer();
    void book_customer_arrival();
}
int loadMenuFromFile(const string& filename, MenuItem menu[]);
string showmenutype(int n);
void showMenu(MenuItem menu[], int itemCount);
void changemunu(const string& filename);
template<typename T, typename Compare>
void bubbleSort(T* head, T* tail, Compare comp);
namespace sys
{
    struct DishStats {
        string name;
        int completed_count;
        int pending_count;
    };
    using namespace std;
    void loadMenu(const string& filename);
    void saveMenu(const string& filename);
    void displayMenu();
    void addMenuItem();
    void deleteMenuItem();
    int change_menu();
    string removeSpaces(const string& str);
    void processFile(const string& filename, DishStats dishStatistics[], int& dishCount, double& totalRevenue);
    void analyzeReceipts(const string& folderPath);
    int loadMenuFromFile(const string& filename, MenuItem menu[]);
    string showmenutype(int n);
    void showMenu(MenuItem menu[], int itemCount);
    void changemunu(const string& filename);
    void loadMenu(const string& filename);
    void saveMenu(const string& filename);
    void displayMenu();
    void addMenuItem();
    void deleteMenuItem();
    int change_menu();
    void password(string name);
    bool checkPassword(const string& username, const string& inputPassword);
    // �޸�����
    bool changePassword(const string& username, const string& newPassword);
    void cpass1(const string& username);//����Ա��
    void cpass2(const string& username);
}
namespace administrator
{
    void test();
    void administrator();
    void set_feel();
}
namespace cashier
{
    struct Dish {
        std::string name;
        std::string table_number;
        double price;
        int quantity;
        std::string special_requests;
        std::string type;
        std::string status;
    };
    void cashier();
    void clearFileContent(const std::string& filepath);
    void previewReceipt(const Dish dishes[], int count, int customer_count);
    int readWaiterFile(const std::string& filepath, cashier::Dish dishes[], int& start_index, int& customer_count);
    void generateReceipt(const std::string& outputPath, const Dish dishes[], int count, int customer_count, const std::string& payment_method, double cash = 0.0);
    void cashier_recipet();
}
void inputnotright();
#define max_int 0x7fffffff
int int_input(int input_max = max_int, int input_min = 0);
void separator(int n);
void directory();
void readallfile(std::string path = "���ݴ洢/��������/");
bool cmd1(MenuItem a, MenuItem b);
int readNumberFromFile(const string& filename);
void writeNumberToFile(const string& filename, int newNumber);
namespace about
{
    void about();
}
#include"ͷ�ļ�/��ȡ�ļ�.h"
#include"ͷ�ļ�/����.h"
#include"�����/������Ͷ��.h"
#include"�����/�鿴ͳ������.h"
#include"�����/��������.h"
#include"�����/�鿴ͳ������.h"
#include"ͷ�ļ�/����.h"
#include"ͷ�ļ�/�����ж�.h"
#include"�����/��ȡ�޸Ĳ˵�.h"
#include"�˿�/�˿�_main.h"
#include"��ʦ/��ʦmain.h"
#include"����Ա/����Աmain.h"
#include"��ӪԱ/��ӪԱmain.h"
#include"����Ա/����Ա_main.h"
#include"�ϰ�/�ϰ�main.h"
#include"ʹ�ð���/���ڱ�ϵͳ.h"
#include"ͷ�ļ�/directory.h"
