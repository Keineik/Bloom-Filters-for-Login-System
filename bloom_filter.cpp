#include "header.h"

int h1(string s, int arrSize)
{
    ll hash = 0;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash + ((int)s[i]));
        hash = hash % arrSize;
    }
    return hash;
}

int h2(string s, int arrSize)
{
    ll hash = 1;
    for (int i = 0; i < s.size(); i++)
    {
        hash = hash + pow(19, i) * s[i];
        hash = hash % arrSize;
    }
    return hash % arrSize;
}

int h3(string s, int arrSize)
{
    ll hash = 7;
    for (int i = 0; i < s.size(); i++)
    {
        hash = (hash * 31 + s[i]) % arrSize;
    }
    return hash % arrSize;
}

int h4(string s, int arrSize)
{
    ll hash = 3;
    int p = 7;
    for (int i = 0; i < s.size(); i++)
    {
        hash += hash * 7 + s[0] * pow(p, i);
        hash = hash % arrSize;
    }
    return hash;
}

bool lookup(bool *bitarray, int arrSize, string s)
{
    int a = h1(s, arrSize);
    int b = h2(s, arrSize);
    int c = h3(s, arrSize);
    int d = h4(s, arrSize);

    if (bitarray[a] && bitarray[b] && bitarray && bitarray[d])
        return true;
    else
        return false;
}

void insert(bool *bitarray, int arrSize, string s)
{
    if (!lookup(bitarray, arrSize, s))
    {
        int a = h1(s, arrSize);
        int b = h2(s, arrSize);
        int c = h3(s, arrSize);
        int d = h4(s, arrSize);

        bitarray[a] = true;
        bitarray[b] = true;
        bitarray[c] = true;
        bitarray[d] = true;
    }
}

int hashPassword(string s, int arrSize)
{
    ll hash = h1(s, arrSize) * pow(257.0, 4.0); 
    hash = hash % arrSize; 
    hash += h2(s, arrSize) * pow(257, 3); 
    hash = hash % arrSize; 
    hash += h3(s, arrSize) * pow(257, 2);
    hash = hash % arrSize;  
    hash += h4(s, arrSize) * 257;
    hash = hash % arrSize; 

    return hash;
}