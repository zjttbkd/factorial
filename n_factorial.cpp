#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <climits>
#include <iomanip>
#include <future>
#include <algorithm>
#include <cstring>
#include "time.h"

using namespace std;

const unsigned int SLOT_MAX = 1000000000;

string getFactorial(int m, int n)
{
    vector<unsigned long long> res;
    res.emplace_back(1);

    for(int i=m; i<=n;)
    {
        unsigned long long j = i++;
        while(j < UINT_MAX && i<=n+1)
        {
            j *= i;
            ++i;
        }
        --i;
        j /= i;

        unsigned long long carry = 0;
        for(int k=0; k<res.size(); k++)
        {
            unsigned long long prod = res[k] * j + carry;
            res[k] = prod % SLOT_MAX;
            carry = prod / SLOT_MAX;
        }
        while(carry)
        {
            res.emplace_back(carry % SLOT_MAX);
            carry /= SLOT_MAX;
        }
    }

    stringstream ss;
    ss << res[res.size()-1];
    for(int i=static_cast<int>(res.size())-2; i>=0; i--)
    {
        ss << setw(9) << setfill('0') << res[i];
    }
    return ss.str();
}

int main()
{
    clock_t start, finish;

    int n = 3000;
    
    start = clock();
    string res1 = getFactorial(2, n);
    finish = clock();

    cout << n << "'s factorial is: " << res1 << endl;
    cout << "time usage: " << (double)(finish - start)/CLOCKS_PER_SEC << "s" << endl;
}
