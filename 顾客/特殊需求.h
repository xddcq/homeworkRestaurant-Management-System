#pragma once
string special_requests_hot(int n)
{
    switch (n)
    {
    case 1:return "����";
    case 2:return "΢��";
    case 3:return "����";
    case 4:return "����";
    }
    return "-1";
}
string getSpecialRequests(int type) {
    if (type == 101) {
        cout << "�����������̶�:������1-4��ʾ��1�ǲ�����2��΢����3��������4������:";
        int spiceLevel = int_input(4,1);
        return special_requests_hot(spiceLevel);
    }
    return "��";
}