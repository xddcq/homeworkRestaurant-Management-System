#pragma once
void inputnotright() {
    cout << "\n��������ȷ������: ";
    cin.clear(); // ����������״̬
    cin.ignore(max_int, '\n'); // ��������
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