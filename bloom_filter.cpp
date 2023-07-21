#include "header.h"

int h1(string s)
{
    ll hash = 0;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash + ((int)s[i]));
        hash = hash % MAXSIZE;
    }
    return hash;
}

int h2(string s)
{
    ll hash = 1;
    for (int i = 0; i < s.size(); i++)
    {
        hash = hash + pow(19, i) * s[i];
        hash = hash % MAXSIZE;
    }
    return hash % MAXSIZE;
}

int h3(string s)
{
    ll hash = 7;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash * 31 + s[i]) % MAXSIZE;
    }
    return hash % MAXSIZE;
}

int h4(string s)
{
    ll hash = 3;
    int p = 7;
    for (int i = 0; i < s.size(); i++)
    {
        hash += hash * 7 + s[0] * pow(p, i);
        hash = hash % MAXSIZE;
    }
    return hash;
}

bool lookup(bool *bitarray, string s)
{
    int a = h1(s);
    int b = h2(s);
    int c = h3(s);
    int d = h4(s);

    if (bitarray[a] && bitarray[b] && bitarray && bitarray[d])
        return true;
    else
        return false;
}

void insert(bool *bitarray, string s)
{
    if (!lookup(bitarray, s))
    {
        int a = h1(s);
        int b = h2(s);
        int c = h3(s);
        int d = h4(s);

        bitarray[a] = true;
        bitarray[b] = true;
        bitarray[c] = true;
        bitarray[d] = true;
    }
}

int hashPassword(string s)
{
    ll hash = h1(s) * pow(257.0, 4.0); 
    hash = hash % MAXSIZE; 
    hash += h2(s) * pow(257, 3); 
    hash = hash % MAXSIZE; 
    hash += h3(s) * pow(257, 2);
    hash = hash % MAXSIZE;  
    hash += h4(s) * 257;
    hash = hash % MAXSIZE; 

    return hash;
}