#include "function.cpp"

int main()
{
    Arrays arrays;

    memset(arrays.bitarray, 0, MAXSIZE);
    memset(arrays.bitWeakPass, 0, MAXSIZE);
    memset(arrays.bitPasswordList, 0, MAXSIZE);

    readbitWeakPass(arrays);
    readData(arrays);
    while (true)
    {
        Account currentUser = {"", ""};
        int cmd;
        bool checkLog = false;
        cout << "Input 1 to register." << endl
             << "Input 2 to register multiple account." << endl
             << "Input 3 to login" << endl
             << "Input 0 to quit" << endl
             << "Please input your command: ";
        cin >> cmd;
        cin.ignore();
        if (!cmd)
            return 0;
        switch (cmd)
        {
        case 1:
            registration(arrays);
            break;
        case 2:
            multiRegistration(arrays);
            break;
        case 3:
            login(currentUser, arrays);
            checkLog = true;
            break;
        default:
            cout << "Invalid command!" << endl;
            break;
        }
        cout << "=============================\n\n";

        while(checkLog)
        {
            int cmd1;
            cout << "Input 1 to change your password." << endl
                 << "Input 2 to log out." << endl
                 << "Input 0 to quit." << endl
                 << "Please input your command: ";
            cin >> cmd1;
            cin.ignore();
            if (!cmd1) return 0;
            switch (cmd1)
            {
            case 1:
                passwordChanging(currentUser, arrays);
                break;
            case 2:
                currentUser = {"", ""};
                checkLog = false;
                break;
            default:
                cout << "Invalid command!" << endl;
                break;
            }
            cout << "=============================\n\n";
        }
    }
    return 0;
}