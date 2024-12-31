
void directory()
{
    while (1)
    {
        cout << "请选择你的身份\n";
        cout << "1:顾客点餐\n"
            "2:收营员\n"
            "3:厨师\n"
            "4:服务员\n"
            "5:餐厅老板\n"
            "6:系统管理员\n"
            "7:关于本系统\n"
            "8、顾客预定餐位\n"
            "9、预定餐位兑现\n"
            "0:退出程序\n";
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