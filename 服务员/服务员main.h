#pragma once
#include"����Ա�ϲ�.h"
#include"����Ա�޸Ķ���.h"
namespace server
{
    using namespace std;
    void server()
    {
        sys::password("����Ա");
        while(1)
        {
            cout << "��ѡ������Ҫ�Ĺ���" << endl;
            cout << "1���ϲ�" << endl;
            cout << "2��������Ӳ�Ʒ" << endl;
            cout << "3������ɾ����Ʒ" << endl;
            cout << "4���޸Ĳ�Ʒ״̬���Ƿ�������" << endl;
            cout << "5���޸�����" << endl;
            cout << "0���˳�����" << endl;
            int n = ::int_input(5);
            switch (n)
            {
            case 1:waiter_serve(); break;
            case 2:serveradd(); break;
            case 3:serverDelete(); break;
            case 4: changemunu("���ݴ洢/menu.txt"); break;
            case 5:sys::cpass2("����Ա"); break;
            case 0:return;
            }
        }
    }
}