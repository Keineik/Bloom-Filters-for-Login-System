#include "header.h"

int getHash(int hashID, string s) {
    ll sdbm = 0;
    for (int i = 0; i < s.size(); i++) {
        sdbm = s[i] + (sdbm << 6) + (sdbm << 16) - sdbm;
        sdbm %= MAXSIZE;
    }

    ll djb2 = 5381;
    for (int i = 0; i < s.size(); i++) {
        djb2 = ((djb2 << 5) + djb2) + s[i];
        djb2 %= MAXSIZE;
    }

    return int((sdbm + (hashID - 1)*djb2) % MAXSIZE);
}

bool lookup(int *bitarray, string s)
{
    for (int i = 1; i <= MAXHASH; i++)
        if (bitarray[getHash(i, s)] == 0) 
            return false; 
    return true;
}

void insert(int *bitarray, string s)
{
    for (int i = 1; i <= MAXHASH; i++)
        bitarray[getHash(i, s)]++;
}

void deleteBit(int *bitarray, string s)
{
    for (int i = 1; i <= MAXHASH; i++)
        bitarray[getHash(i, s)]--;
}
