#include "bloom_filter.cpp"

// For reading the weak password from the file into the filter
void readbitWeakPass(Arrays &arrays)
{
    ifstream ifs("WeakPass.txt");
    if (!ifs)
        return;
    string s;
    while (getline(ifs, s, '\n'))
    {
        if (s == "")
            break;
        insert(arrays.bitWeakPass, s);
    }
    ifs.close();
}

// For reading the accounts' information into the username filter and password filter
void readData(Arrays &arrays)
{
    ifstream ifs("accounts.txt");
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

// For checking whether the username is valid or not
bool CheckUsername(string username, int *bitarray)
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

// For checking whether the password is valid or not
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

// Checking whether the registration request is valid or not
bool CheckRegistration(string username, string password, Arrays &arrays)
{
    if (CheckUsername(username, arrays.bitarray) && CheckPassword(username, password, arrays))
    {
        cout << "Successfully registered." << endl;
        return true;
    }
    return false;
}

// For creating an account
void registration(Arrays &arrays)
{
    string username, password;
    while (true)
    {
        cout << "Please input your username: ";
        getline(cin, username, '\n');
        cout << "Please input your password: ";
        getline(cin, password, '\n');
        if (CheckRegistration(username, password, arrays)) break;
    }

    insert(arrays.bitarray, username);
    insert(arrays.bitPasswordList, password);

    ofstream successIn("accounts.txt", ios::app);
    successIn << username << ' ' << password << endl;
    successIn.close();
}

// For creating multiple accounts which are read from file
void multiRegistration(Arrays &arrays)
{
    ifstream ifs("SignUp.txt");
    ofstream successIn("accounts.txt", ios::app), failIn("Fail.txt");

    vector<Account> list;

    Account user;
    while (ifs >> user.username)
    {
        if (user.username == "") return;
        ifs >> user.password;
        list.push_back(user);
    }

    streambuf* orig_buf = cout.rdbuf();
    cout.rdbuf(NULL);

    int countSuccess = 0, countFail = 0;
    for (int i = 0; i < list.size(); i++)
    {
        if (CheckRegistration(list[i].username, list[i].password, arrays))
        {
            insert(arrays.bitarray, list[i].username);
            insert(arrays.bitPasswordList, list[i].password);
            successIn << list[i].username << ' ' << list[i].password << endl;
            countSuccess++;
        }
        else
        {
            failIn << list[i].username << ' ' << list[i].password << endl;
            countFail++;
        }
    }
    cout.rdbuf(orig_buf);

    cout << "Finish Multiple Registrations" << endl;
    cout << "Successfully Registered " << countSuccess << " Accounts" << endl;
    cout << "There are " << countFail << " Failed Registration Attempts" << endl;

    successIn.close();
    failIn.close();
}

// Checking whether login request is valid or not
bool checkLogin(Account user, Arrays &arrays)
{
    if (!lookup(arrays.bitarray, user.username) || !lookup(arrays.bitPasswordList, user.password))
    {
        cout << "Invalid username or password." << endl;
        return false;
    }
    
    ifstream ifs("accounts.txt");
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

// For users to login their account
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

// For users to change their accounts' password
void passwordChanging(Account user, Arrays &arrays)
{
    vector<Account> list;
    ifstream ifs("accounts.txt");
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
        {
            cout << "The input password does not match the current password.\n";
            continue;
        }
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
        deleteBit(arrays.bitPasswordList, list[index].password);
        list[index].password = password;
        insert(arrays.bitPasswordList, list[index].password);
        break;
    }

    ofstream ofs("accounts.txt");
    for (int i = 0; i < list.size(); i++)
        ofs << list[i].username << ' ' << list[i].password << endl;
    ofs.close();
}
