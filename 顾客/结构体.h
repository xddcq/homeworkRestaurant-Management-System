#pragma once

#define MAX_MENU_ITEMS 100
#define MAX_NUMBER 100
using namespace std;
// 菜单项结构体
struct MenuItem {
    int id;             // 菜单项编号
    string name;        // 菜单项名称
    double price;       // 菜单项价格
    int type;           // 菜单项类型
};

// 订单项结构体
struct OrderItem {
    MenuItem item;      // 菜单项信息
    int quantity;       // 数量
    string special_requests; // 特殊要求
};

// 订单结构体
struct Order {
    string customer_name;            // 顾客姓名
    string contact_info;             // 顾客联系方式
    string remarks;                  // 订单备注
    int assigned_tables; // 分配的桌子编号数组
    int table_count;                 // 分配的桌子数量
    OrderItem items[MAX_MENU_ITEMS]; // 订单包含的菜品项
    int item_count;                  // 订单中的菜品总数
    double total_price;              // 订单总价
};
struct Table {
    int id;        // 桌子的编号
    int capacity;  // 桌子的容量（最多可以容纳多少人）
    int status;    // 桌子状态：1 表示可用，2 表示已占用
};

