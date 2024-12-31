#pragma once
string special_requests_hot(int n)
{
    switch (n)
    {
    case 1:return "不辣";
    case 2:return "微辣";
    case 3:return "中辣";
    case 4:return "麻辣";
    }
    return "-1";
}
string getSpecialRequests(int type) {
    if (type == 101) {
        cout << "请输入辣椒程度:用数字1-4表示，1是不辣，2是微辣，3是中辣，4是麻辣:";
        int spiceLevel = int_input(4,1);
        return special_requests_hot(spiceLevel);
    }
    return "无";
}