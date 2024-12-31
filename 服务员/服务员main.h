#pragma once
#include"服务员上菜.h"
#include"服务员修改订单.h"
namespace server
{
    using namespace std;
    void server()
    {
        sys::password("服务员");
        while(1)
        {
            cout << "请选择你需要的功能" << endl;
            cout << "1、上菜" << endl;
            cout << "2、订单添加菜品" << endl;
            cout << "3、订单删除菜品" << endl;
            cout << "4、修改菜品状态（是否售罄）" << endl;
            cout << "5、修改密码" << endl;
            cout << "0、退出程序" << endl;
            int n = ::int_input(5);
            switch (n)
            {
            case 1:waiter_serve(); break;
            case 2:serveradd(); break;
            case 3:serverDelete(); break;
            case 4: changemunu("数据存储/menu.txt"); break;
            case 5:sys::cpass2("服务员"); break;
            case 0:return;
            }
        }
    }
}