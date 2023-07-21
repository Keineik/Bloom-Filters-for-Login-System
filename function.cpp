#include "bloom_filter.cpp"

void readWeakPass(bool *weakPass, int arrSize)
{
    ifstream ifs("WeakPass.txt");
    if (!ifs)
        return;
    string s;
    while (getline(ifs, s, '\n'))
    {
        if (s == "")
            break;
        if (!lookup(weakPass, arrSize, s))
            insert(weakPass, arrSize, s);
    }
    ifs.close();
}

void readData(bool *bitarray, int arrSize, bool passwordList[][500])
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
        insert(bitarray, arrSize, username);
        insert(passwordList[hashPassword(username, arrSize)], arrSize, password);
    }
    ifs.close();
}

bool CheckUsername(string username, bool *bitarray, int arrSize)
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
    else if (lookup(bitarray, arrSize, username))
    {
        cout << "Your username has been registered. Please input another username: " << endl;
        return false;
    }
    return true;
}

bool CheckPassword(string username, string password, bool *bitarray, bool *weakPass, int arrSize)
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
    else if (lookup(weakPass, arrSize, password))
    {
        cout << "Your password is too weak." << endl;
        return false;
    }
    return true;
}

bool CheckRegistration(string username, string password, bool *bitarray, bool *weakPass, int arrSize)
{
    if (CheckUsername(username, bitarray, arrSize) && CheckPassword(username, password, bitarray, weakPass, arrSize))
    {
        cout << "Successfully registered." << endl;
        return true;
    }
    return false;
}

void registration(bool *bitarray, bool *weakPass, int arrSize, bool passwordList[][500])
{
    ofstream failIn("Fail.txt", ios::app);
    string username, password;
    while (true)
    {
        cout << "Please input your username: ";
        getline(cin, username, '\n');
        cout << "Please input your password: ";
        getline(cin, password, '\n');
        if (CheckRegistration(username, password, bitarray, weakPass, arrSize)) break;
        failIn << username << ' ' << password << endl;
    } 
    failIn.close();

    insert(bitarray, arrSize, username);
    insert(passwordList[hashPassword(username, arrSize)], arrSize, password);
    // passwordList[hashPassword(username, arrSize)].push_back(password);
    ofstream successIn("SignUp.txt", ios::app);
    successIn << username << ' ' << password << endl;
    successIn.close();
}

void multiRegistration(bool *bitarray, bool *weakPass, int arrSize, bool passwordList[][500])
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
        if (CheckRegistration(list[i].username, list[i].password, bitarray, weakPass, arrSize))
        {
            insert(bitarray, arrSize, list[i].username);
            // passwordList[hashPassword(list[i].username, arrSize)].push_back(list[i].password);
            insert(passwordList[hashPassword(list[i].username, arrSize)], arrSize, list[i].password);
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

bool checkLogin(Account user, bool *bitarray, int arrSize, bool passwordList[][500])
{
    if (!lookup(bitarray, arrSize, user.username))
    {
        cout << "Invalid username." << endl;
        return false;
    }
    int index = hashPassword(user.username, arrSize);
    if (!lookup(passwordList[index], arrSize, user.password))
    {
        cout << "Invalid password." << endl;
        return false;
    }
    cout << "Successfully logged in" << endl;
    return true;
}

void login(Account &user, bool *bitarray, int arrSize, bool passwordList[][500])
{
    do
    {
        cout << "Please input your username: ";
        getline(cin, user.username, '\n');
        cout << "Please input your password: ";
        getline(cin, user.password, '\n');
    } while (!checkLogin(user, bitarray, arrSize, passwordList));
}

void passwordChanging(Account user, bool *bitarray, bool *weakPass, int arrSize, bool passwordList[][500])
{
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
        if (!CheckPassword(list[index].username, password, bitarray, weakPass, arrSize))
            continue;
        cout << "Successfully changed your password" << endl;
        list[index].password = password;
        break;
    }

    ofstream ofs("SignUp.txt");
    for (int i = 0; i < list.size(); i++)
        ofs << list[i].username << ' ' << list[i].password << endl;
    ofs.close();

    readData(bitarray, arrSize, passwordList);
}
