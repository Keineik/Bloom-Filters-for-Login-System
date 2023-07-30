#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
#include <iomanip>
using namespace std;

#define ll long long int
#define MAXSIZE 40000

struct Account{
    string username;
    string password;
};

struct Arrays {
    int bitarray[MAXSIZE];
    int bitWeakPass[MAXSIZE]; 
    int bitPasswordList[MAXSIZE];
    vector<string> weakPassword;
};