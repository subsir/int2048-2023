/*
Time: 2021-10-21
Test: mul & div
std Time: 0.01s
Time Limit: 1.00s
*/

#include "int2048.h"

sjtu::int2048 a;
std::string s;

int main()
{
        freopen("data/Integer2/10.in", "r", stdin);
    freopen("data/Integer2/self_10.out", "w", stdout);
    int n;
    std::cin >> n;
    a = 1;
    for (int i = 1; i <= n; i++)
    {
        int ty = 0;
        std::cin >> ty >> s;
        
        if (ty)
            a /= s;
        else
            a *= s;
        
        std::cout << a << '\n';
    }
}