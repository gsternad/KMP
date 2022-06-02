#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

ofstream out;

string inputText(const string &pot) {
    ifstream input(pot);
    stringstream sstream;

    if (!input.is_open()) {
        return string();
    }

    sstream << input.rdbuf();
    return sstream.str();
}

void KMPNext(const string& vzorec, int* kmpNext)
{
    // KMPNext
    int len = vzorec.length();
    kmpNext[len];
    string prefix;
    string suffix;
    kmpNext[0] = -1;
    kmpNext[1] = 0;
    int i = 2;
    while(i < len)
    {
        int j = i-1;            // dolžina nizov prefix in suffix, niz se manjša za 1, če suffix != prefix
        int k = 1;              // začetna pozicija prvega suffix char
        while(j > 0 && k < len)
        {
            prefix = vzorec.substr(0, j);
            suffix = vzorec.substr(k, j);
            if(prefix == suffix)
            {
                kmpNext[i] = prefix.length(); // ali suffix length, saj nima veze, oba sta enako dolga
                break;
            }
            else
            {
                kmpNext[i] = 0;
                j--;
                k++;
            }
        }
        i++;
    }
}

void izpis_KMPnext(const int* polje, unsigned int len)
{
    for (int i = 0; i < len; ++i) {
        out << polje[i] << " ";
    }
    out << endl;
}

void KMP(const string& text, const string& vzorec, int* kmpNext)
{
    KMPNext(vzorec, kmpNext);
    izpis_KMPnext(kmpNext, vzorec.length());
    // iskanje s KMP
    int i = 0;
    int j = 0;
    int m = vzorec.length();
    int n = text.length();
    while(j < n)
    {
        if(vzorec[i] != text[j+i])
        {
            j += i-kmpNext[i];
            i = 0;
        }
        else if(vzorec[i] == text[j+i])
        {
            i++;
            if(i == m-1)
            {
                out << "Ujemanje na " << j << ".\n";
                i = 0;
                j += m;
            }
        }
    }
}

int main(int argc, const char *const argv[]) {
    if (argc != 3) {
        return -1;
    }

    string text = inputText(argv[2]);
    string vzorec = argv[1];

    out.open("out.txt");

    if (!out) {
        return -2;
    }
    unsigned int len = vzorec.length();
    int* kmpNext = new int[len];
    KMP(text, vzorec, kmpNext);
    delete[] kmpNext;
    return 0;
}