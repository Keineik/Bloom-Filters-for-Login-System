#include "bloom_filter.cpp"

void readbitWeakPass(Arrays &arrays)
{
    ifstream ifs("bitWeakPass.txt");
    if (!ifs)
        return;
    string s;
    while (getline(ifs, s, '\n'))
    {
        if (s == "")
            break;
        if (!lookup(arrays.bitWeakPass, s))
            insert(arrays.bitWeakPass, s);
    }
    ifs.close();
}

void readData(Arrays &arrays)
{
    ifstream ifs("SignUp.txt");
    if (!ifs)
        return;
    string s;
    while (getline(ifs, s, '\n'))
    {
        if (s == "")
            break;
        stringstream ss(s);
        string username, password;
        ss >> username >> password;
        insert(arrays.bitarray, username);
        insert(arrays.bitPasswordList, password);
    }
    ifs.close();
}

bool CheckUsername(string username, bool *bitarray)
{
    bool checkSpace = false;
    for (int i = 0; i < username.length(); i++)
        if (username[i] == ' ')
        {
            checkSpace = true;
            break;
        }
    if (checkSpace)
    {
        cout << "Your username must not contain space character." << endl;
        return false;
    }
    else if (username.length() >= 10)
    {
        cout << "Your username is too long." << endl;
        return false;
    }
    else if (username.length() <= 5)
    {
        cout << "Your username is too short." << endl;
        return false;
    }
    else if (lookup(bitarray, username))
    {
        cout << "Your username has been registered. Please input another username: " << endl;
        return false;
    }
    return true;
}

bool CheckPassword(string username, string password, Arrays &arrays)
{
    bool upperCheck = false, lowerCheck = false, numCheck = false, specialCharCheck = false, spaceCheck = false;
    for (int i = 0; i < password.length(); i++)
    {
        if (password[i] <= 'Z' && password[i] >= 'A')
            upperCheck = true;
        else if (password[i] <= 'z' && password[i] >= 'a')
            lowerCheck = true;
        else if (password[i] <= '9' && password[i] >= '0')
            numCheck = true;
        else if (password[i] == ' ')
            spaceCheck = true;
        else
            specialCharCheck = true;
    }
    if (spaceCheck)
    {
        cout << "Your password must not contain space character." << endl;
        return false;
    }
    if (!upperCheck || !lowerCheck || !numCheck || !specialCharCheck)
    {
        cout << "Your password must contain at least a lowercase letter, a capital letter, a number and a special character." << endl;
        return false;
    }
    else if (password.find(username) != -1)
    {
        cout << "Your password must not contain your username." << endl;
        return false;
    }
    else if (password.length() >= 20)
    {
        cout << "Your password is too long." << endl;
        return false;
    }
    else if (password.length() <= 10)
    {
        cout << "Your password is too short." << endl;
        return false;
    }
    else if (lookup(arrays.bitWeakPass, password))
    {   
        ifstream ifs("WeakPass.txt");
        string weakPass;
        while (getline(ifs, weakPass)) {
            if (password == weakPass) return false;
        }
        ifs.close();
    }
    return true;
}

bool CheckRegistration(string username, string password, Arrays &arrays)
{
    if (CheckUsername(username, arrays.bitarray) && CheckPassword(username, password, arrays))
    {
        cout << "Successfully registered." << endl;
        return true;
    }
    return false;
}

void registration(Arrays &arrays)
{
    ofstream failIn("Fail.txt", ios::app);
    string username, password;
    while (true)
    {
        cout << "Please input your username: ";
        getline(cin, username, '\n');
        cout << "Please input your password: ";
        getline(cin, password, '\n');
        if (CheckRegistration(username, password, arrays)) break;
        failIn << username << ' ' << password << endl;
    } 
    failIn.close();

    insert(arrays.bitarray, username);
    insert(arrays.bitPasswordList, password);
    ofstream successIn("SignUp.txt", ios::app);
    successIn << username << ' ' << password << endl;
    successIn.close();
}

void multiRegistration(Arrays &arrays)
{
    ofstream successIn("SignUp.txt", ios::app), failIn("Fail.txt", ios::app);
    cout << "Please input the number of account you want to register: ";
    int accountNum;
    cin >> accountNum;
    cin.ignore();
    vector<Account> list;
    for (int i = 0; i < accountNum; i++)
    {
        Account user;
        cout << "User " << i + 1 << endl;
        cout << "Please input your username: ";
        getline(cin, user.username, '\n');
        cout << "Please input your password: ";
        getline(cin, user.password, '\n');
        list.push_back(user);
    }
    for (int i = 0; i < list.size(); i++)
    {
        cout << "Account " << i + 1 << ": ";
        if (CheckRegistration(list[i].username, list[i].password, arrays))
        {
            insert(arrays.bitarray, list[i].username);
            insert(arrays.bitPasswordList, list[i].password);
            successIn << list[i].username << ' ' << list[i].password << endl;
        }
        else
        {
            failIn << list[i].username << ' ' << list[i].password << endl;
        }
    }
    successIn.close();
    failIn.close();
}

bool checkLogin(Account user, Arrays &arrays)
{
    if (!lookup(arrays.bitarray, user.username))
    {
        cout << "Invalid username." << endl;
        return false;
    }
    
    ifstream ifs("SignUp.txt");
    bool existUsername = false;
    while (!ifs.eof()) {
        Account tempAcc;
        getline(ifs, tempAcc.username, ' ');
        getline(ifs, tempAcc.password);
        if (tempAcc.username == user.username && tempAcc.password == user.password) {
            cout << "Successfully logged in" << endl;
            return true;
        }
        else if (tempAcc.username == user.username) existUsername = true;
    }
    ifs.close();

    if (existUsername) cout << "Wrong password." << endl;
    else cout << "Invalid username." << endl;
    return false;
}

void login(Account &user, Arrays &arrays)
{
    do
    {
        cout << "Please input your username: ";
        getline(cin, user.username, '\n');
        cout << "Please input your password: ";
        getline(cin, user.password, '\n');
    } while (!checkLogin(user, arrays));
}

void passwordChanging(Account user, Arrays &arrays)
{
    memset(arrays.bitarray, 0, MAXSIZE);
    memset(arrays.bitWeakPass, 0, MAXSIZE);
    memset(arrays.bitPasswordList, 0, MAXSIZE);

    vector<Account> list;
    ifstream ifs("SignUp.txt");
    if (!ifs)
        return;
    string s;
    while (getline(ifs, s, '\n'))
    {
        if (s == "")
            break;
        stringstream ss(s);
        Account userTemp;
        ss >> userTemp.username >> userTemp.password;
        list.push_back(userTemp);
    }
    ifs.close();

    int index = 0;
    for (; index < list.size(); index++)
        if (list[index].username == user.username)
            break;
    while (true)
    {
        string password;
        cout << "Please input your current password: ";
        getline(cin, password, '\n');
        if (password != list[index].password)
            continue;
        break;
    }
    while (true)
    {
        string password;
        cout << "Please input your new password: ";
        getline(cin, password, '\n');
        if (!CheckPassword(list[index].username, password, arrays))
            continue;
        cout << "Successfully changed your password" << endl;
        list[index].password = password;
        break;
    }

    ofstream ofs("SignUp.txt");
    for (int i = 0; i < list.size(); i++)
        ofs << list[i].username << ' ' << list[i].password << endl;
    ofs.close();

    readData(arrays);
}
