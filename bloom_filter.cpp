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

bool lookup(int *bitarray, string s)
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

void insert(int *bitarray, string s)
{
    int a = h1(s);
    int b = h2(s);
    int c = h3(s);
    int d = h4(s);
    bitarray[a] ++;
    bitarray[b] ++;
    bitarray[c] ++;
    bitarray[d] ++;
}

void deleteBit(int *bitarray, string s)
{
    int a = h1(s);
    int b = h2(s);
    int c = h3(s);
    int d = h4(s);
    bitarray[a] --;
    bitarray[b] --;
    bitarray[c] --;
    bitarray[d] --;
}