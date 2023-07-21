#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

#define ll long long int
#define MAXSIZE 500

struct Account{
    string username;
    string password;
};

struct Arrays {
    bool bitarray[MAXSIZE];
    bool bitWeakPass[MAXSIZE]; 
    bool bitPasswordList[MAXSIZE][MAXSIZE];
    vector<string> weakPassword;
};
