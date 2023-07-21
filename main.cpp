#include "function.cpp"

int main()
{
    bool bitarray[500];
    bool weakPass[500];
    int arrSize = 500;
    bool passwordList[500][500];
    for (int i = 0; i < arrSize; i++)
    {
        bitarray[i] = 0;
        weakPass[i] = 0;
        for (int j = 0; j < arrSize; j++)
            passwordList[i][j] = 0;
    }
    readWeakPass(weakPass, arrSize);
    readData(bitarray, arrSize, passwordList);
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
            registration(bitarray, weakPass, arrSize, passwordList);
            break;
        case 2:
            multiRegistration(bitarray, weakPass, arrSize, passwordList);
            break;
        case 3:
            login(currentUser, bitarray, arrSize, passwordList);
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
                passwordChanging(currentUser, bitarray, weakPass, arrSize, passwordList);
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