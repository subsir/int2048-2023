/*
Time: 2021-10-21
Test: mul & div 
std Time: 0.03s
Time Limit: 1.00s
*/

#include "int2048.h"

sjtu::int2048 a, b;

int main()
{
    freopen("data/Integer2/9.in", "r", stdin);
    freopen("data/Integer2/self_9.out", "w", stdout);
    int T, cnt = 0;
    std::cin >> T;
    while (T--)
    {
        std::cin >> a >> b;
        std::cout << a / b << '\n';
        std::cout << (a /= b) << '\n';
        cnt += 2;
        sjtu::int2048 tmp;
        tmp = a * b;
        a *= b;
        a /= a;
        a *= b;
        tmp /= a;
        std::cout << tmp << '\n';
        cnt++;
    }
}