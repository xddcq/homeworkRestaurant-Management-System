
void directory()
{
    while (1)
    {
        cout << "��ѡ��������\n";
        cout << "1:�˿͵��\n"
            "2:��ӪԱ\n"
            "3:��ʦ\n"
            "4:����Ա\n"
            "5:�����ϰ�\n"
            "6:ϵͳ����Ա\n"
            "7:���ڱ�ϵͳ\n"
            "8���˿�Ԥ����λ\n"
            "9��Ԥ����λ����\n"
            "0:�˳�����\n";
        int n = int_input(9);
        system("cls");
        switch (n)
        {
        case 1:costomer::customer(); break;
        case 2:cashier::cashier(); break;
        case 3:cook::cook(); break;
        case 4:server::server(); break;
        case 5:boss::boss(); break;
        case 6:administrator::administrator(); break;
        case 7:about::about(); break;
        case 8:costomer::book_customer();break;
        case 9:costomer::book_customer_arrival(); break;
        case 0:return ;
        default:
            break;
        }
        system("cls");
    }
}