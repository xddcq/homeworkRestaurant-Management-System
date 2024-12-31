#pragma once
// 菜品信息结构体(厨师）
namespace cook
{
    using namespace std;
    struct Dish {
        string name;
        string table_number;
        string order_number;
        string special_requests;
        string type;
        string status;
    };
}