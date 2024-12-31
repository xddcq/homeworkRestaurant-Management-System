#pragma once
void inputnotright() {
    cout << "\n请输入正确的数字: ";
    cin.clear(); // 重置输入流状态
    cin.ignore(max_int, '\n'); // 清理缓冲区
}
int int_input(int input_max,int input_min)
{
    int n;
    while(1)
    {
        if (cin >> n &&cin.good() && n >= 0 && n <= input_max && n >= input_min)
        {
            return n;
        }
        else
        {
            inputnotright();
        }
    }

}
void separator(int n)
{
    for (int i(0); i < n; i++)
    {
        cout << "-";
    }
    cout << endl;
}