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
#include"顾客/结构体.h"
#include"厨师/厨师结构体.h"
#include"头文件/展示全部文件.h"
#define 暂停 system("pause")
#define 清屏 system("cls")
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
    void displayAvailableOrders(const std::string& order_directory = "数据存储/订单数据");
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
    // 修改密码
    bool changePassword(const string& username, const string& newPassword);
    void cpass1(const string& username);//管理员端
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
void readallfile(std::string path = "数据存储/订单数据/");
bool cmd1(MenuItem a, MenuItem b);
int readNumberFromFile(const string& filename);
void writeNumberToFile(const string& filename, int newNumber);
namespace about
{
    void about();
}
#include"头文件/读取文件.h"
#include"头文件/密码.h"
#include"管理端/建议与投诉.h"
#include"管理端/查看统计数据.h"
#include"管理端/餐桌管理.h"
#include"管理端/查看统计数据.h"
#include"头文件/排序.h"
#include"头文件/输入判断.h"
#include"管理端/获取修改菜单.h"
#include"顾客/顾客_main.h"
#include"厨师/厨师main.h"
#include"服务员/服务员main.h"
#include"收营员/收营员main.h"
#include"管理员/管理员_main.h"
#include"老板/老板main.h"
#include"使用帮助/关于本系统.h"
#include"头文件/directory.h"
