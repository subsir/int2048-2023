#pragma once
#ifndef SJTU_BIGINTEGER
#define SJTU_BIGINTEGER

// Integer 1:
// 实现一个有符号的大整数类，只需支持简单的加减

// Integer 2:
// 实现一个有符号的大整数类，支持加减乘除，并重载相关运算符

// 请不要使用除了以下头文件之外的其它头文件
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>

// 请不要使用 using namespace std;

namespace sjtu {
class int2048 {
  // todo
public:
  // 构造函数
  static const long long BASE = (int)(1e8);
  static const int NUM_BIT = 8;
  std::vector<int> bits; // (1e8)进制，第0位存符号(1\-1表示正负)
  int2048() {
    bits.clear();
    bits.push_back(1); // +0 不输出+
    bits.push_back(0);
  }
  int2048(long long temp) {
    bits.clear();
    if (temp == 0) {
      bits.push_back(1);
      bits.push_back(0);
      return;
    }
    if (temp < 0) {
      temp *= -1;
      bits.push_back(-1);
    } else {
      bits.push_back(1);
    }
    while (temp != 0) {
      bits.push_back(temp % BASE);
      temp /= BASE;
    }
    while (bits.size() > 2 and bits[bits.size() - 1] == 0) {
      bits.pop_back();
    }
  }
  int2048(const std::string &s0) {
    bits.clear();
    std::string s;
    if (s0[0] == '-') {
      bits.push_back(-1);
      s = s0.substr(1);
    } else {
      bits.push_back(1);
      s = s0;
    }
    for (int i = s.size() - 1; i >= NUM_BIT - 1; i -= NUM_BIT) {
      bits.push_back(std::stoi(s.substr(i - NUM_BIT + 1, NUM_BIT)));
    }
    if (s.size() % NUM_BIT != 0) {
      bits.push_back(std::stoi(s.substr(0, s.size() % NUM_BIT)));
    }
    while (bits.size() > 2 and bits[bits.size() - 1] == 0) {
      bits.pop_back();
    }
  }
  int2048(const int2048 &other) {
    bits.clear();
    for (int i = 0; i < other.bits.size(); i++) {
      bits.push_back(other.bits[i]);
    }
    while (bits.size() > 2 and bits[bits.size() - 1] == 0) {
      bits.pop_back();
    }
  }

  // 以下给定函数的形式参数类型仅供参考，可自行选择使用常量引用或者不使用引用
  // 如果需要，可以自行增加其他所需的函数
  // ===================================
  // Integer1
  // ===================================

  // 读入一个大整数
  void read(const std::string &s0) {
    bits.clear();
    std::string s;
    if (s0[0] == '-') {
      bits.push_back(-1);
      s = s0.substr(1);
    } else {
      bits.push_back(1);
      s = s0;
    }
    for (int i = s.size() - 1; i >= NUM_BIT - 1; i -= NUM_BIT) {
      bits.push_back(std::stoi(s.substr(i - NUM_BIT + 1, NUM_BIT)));
    }
    if (s.size() % NUM_BIT != 0) {
      bits.push_back(std::stoi(s.substr(0, s.size() % NUM_BIT)));
    }
    while (bits.size() > 2 and bits.back() == 0) {
      bits.pop_back();
    }
  }
  // 输出储存的大整数
  void print() {
    if (bits.size() == 2 and bits[1] == 0) { // -0输出0
      std::cout << "0";
      return;
    }
    while (bits.size() > 2 and bits.back() == 0) {
      bits.pop_back();
    }
    std::cout << (bits[0] == -1 ? "-" : "");
    for (int i = bits.size() - 1; i >= 1; i--) {
      if (i != bits.size() - 1) {
        for (int j = std::to_string(bits[i]).length(); j < NUM_BIT; j++) {
          std::cout << "0";
        }
      }
      std::cout << bits[i];
    }
  }

  int Abs_Compare(
      const int2048 &other) const { // if |this| > |other| -1表示相等
    if (bits.size() != other.bits.size()) {
      return bits.size() > other.bits.size();
    }
    for (int i = bits.size() - 1; i >= 1; i--) {
      if (bits[i] != other.bits[i]) {
        return bits[i] > other.bits[i];
      }
    }
    return -1; // -1表示相等
  }

  // 加上一个大整数
  int2048 &add(const int2048 &other) {
    int max_bit = std::max(bits.size(), other.bits.size());
    if (bits[0] * other.bits[0] == -1) {
      int abs_compare = Abs_Compare(other);
      if (abs_compare == -1) {
        bits.clear();
        bits.push_back(1);
        bits.push_back(0);
        return *this;
      }
      if (abs_compare == 1) {
        for (int i = 1; i < max_bit; i++) {
          int x1 = 0, x2 = 0;
          if (i < other.bits.size()) {
            x2 = other.bits[i];
          }
          if (i < bits.size()) {
            x1 = bits[i];
            bits[i] = x1 - x2;
          } else {
            bits.push_back(x1 - x2);
          }
        }
        for (int i = 1; i < max_bit - 1; i++) {
          if (bits[i] < 0) {
            bits[i + 1]--;
            bits[i] += BASE;
          }
        }
        while (bits.size() > 2 and bits.back() == 0) {
          bits.pop_back();
        }
        return *this;
      }
      bits[0] = other.bits[0];
      for (int i = 1; i < max_bit; i++) {
        int x1 = 0, x2 = 0;
        if (i < other.bits.size()) {
          x2 = other.bits[i];
        }
        if (i < bits.size()) {
          x1 = bits[i];
          bits[i] = x2 - x1;
        } else {
          bits.push_back(x2 - x1);
        }
      }
      for (int i = 1; i < max_bit - 1; i++) {
        if (bits[i] < 0) {
          bits[i + 1]--;
          bits[i] += BASE;
        }
      }
      while (bits.size() > 2 and bits.back() == 0) {
        bits.pop_back();
      }
      return *this;
    }
    for (int i = 1; i < max_bit; i++) {
      int x1 = 0, x2 = 0;
      if (i < bits.size()) {
        x1 = bits[i];
      }
      if (i < other.bits.size()) {
        x2 = other.bits[i];
      }
      if (i < bits.size()) {
        x1 = bits[i];
        bits[i] = x1 + x2;
      } else {
        bits.push_back(x1 + x2);
      }
    }
    for (int i = 1; i < max_bit; i++) {
      if (bits[i] >= BASE) {
        if (i != max_bit - 1) {
          bits[i + 1]++;
          bits[i] %= BASE;
        } else {
          bits[i] %= BASE;
          bits.push_back(1);
        }
      }
    }
    while (bits.size() > 2 and bits.back() == 0) {
      bits.pop_back();
    }
    return *this;
  }
  // 返回两个大整数之和
  friend int2048 add(int2048 x1, const int2048 &x2) { return x1.add(x2); }

  // 减去一个大整数
  int2048 &minus(const int2048 &other) {
    int2048 temp_other(other);
    temp_other.bits[0] *= -1;
    return add(temp_other);
  }
  // 返回两个大整数之差
  friend int2048 minus(int2048 x1, const int2048 &x2) { return x1.minus(x2); }

  friend bool operator==(const int2048 &x1, const int2048 &x2) {
    if (x1.bits[0] == x2.bits[0] and x1.Abs_Compare(x2) == -1) {
      return true;
    }
    return false;
  }
  friend bool operator!=(const int2048 &x1, const int2048 &x2) {
    return not(x1 == x2);
  }
  friend bool operator<(const int2048 &x1, const int2048 &x2) {
    if (x1.bits[0] != x2.bits[0]) {
      return (x1.bits[0] < x2.bits[0]);
    }
    if (x1.Abs_Compare(x2) == -1) {
      return false;
    }
    if (x1.bits[0] == 1) {
      return not x1.Abs_Compare(x2);
    }
    return x1.Abs_Compare(x2);
  }
  friend bool operator>(const int2048 &x1, const int2048 &x2) {
    if (x1.bits[0] != x2.bits[0]) {
      return (x1.bits[0] > x2.bits[0]);
    }
    if (x1.Abs_Compare(x2) == -1) {
      return false;
    }
    if (x1.bits[0] == 1) {
      return x1.Abs_Compare(x2);
    }
    return not x1.Abs_Compare(x2);
  }
  friend bool operator<=(const int2048 &x1, const int2048 &x2) {
    return not(x1 > x2);
  }
  friend bool operator>=(const int2048 &x1, const int2048 &x2) {
    return not(x1 < x2);
  }

  // 返回两个大整数之积
  friend int2048 mul(int2048 x1, const int2048 &x2) {
    int2048 temp(0);
    temp.bits[0] = x2.bits[0] * x1.bits[0];
    temp.bits.resize(x1.bits.size() + x2.bits.size());
    for (int i = 1; i < x2.bits.size(); i++) {
      for (int j = 1; j < x1.bits.size(); j++) {
        long long temp_x = 1ll * x2.bits[i] * x1.bits[j];
        temp.bits[i + j] += temp_x / BASE;
        temp.bits[i + j - 1] += temp_x % BASE;
        if (temp.bits[i + j] > (1 << 31)) {
          temp.bits[i + j + 1] += temp.bits[i + j] / BASE;
          temp.bits[i + j] %= BASE;
        }
        if (temp.bits[i + j - 1] > (1 << 30)) {
          temp.bits[i + j] += temp.bits[i + j - 1] / BASE;
          temp.bits[i + j - 1] %= BASE;
        }
      }
    }
    for (int i = 1; i < temp.bits.size(); i++) {
      if (temp.bits[i] >= BASE) {
        if (i != temp.bits.size() - 1) {
          temp.bits[i + 1] += temp.bits[i] / BASE;
          temp.bits[i] %= BASE;
        } else {
          temp.bits.push_back(temp.bits[i] / BASE);
          temp.bits[i] %= BASE;
        }
      }
    }
    while (temp.bits.size() > 2 and temp.bits.back() == 0) {
      temp.bits.pop_back();
    }
    return temp;
  }

  friend int2048 operator*(int2048 x1, const int2048 &x2) {
    return mul(x1, x2);
  }

  static int digit_div(int2048 x1, const int2048 &x2, int shift_bit) {
    shift_bit--;
    if (shift_bit > x1.bits.size() - 1) {
      return 0;
    }
    for (int i = 1; i < x1.bits.size() - shift_bit; i++) {
      x1.bits[i] = x1.bits[i + shift_bit];
    }
    x1.bits.resize(x1.bits.size() - shift_bit);
    int left, right, mid, result = -1;
    while (x1.bits.size() > 2 and x1.bits.back() == 0) {
      x1.bits.pop_back();
    }
    int back = x2.bits.size() - 1;
    while (back > 1 and x2.bits[back] == 0) {
      back--;
    }
    long long x1_back = x1.bits.back();
    if (x1.bits.size() > back + 1) {
      x1_back *= BASE;
      x1_back += x1.bits[x1.bits.size() - 2];
    }
    left = x1_back / (x2.bits[back] + 1);
    right = (x1_back + 1) / x2.bits[back] + 1;
    while (left <= right) {
      mid = (right + left) >> 1;
      if (x1.Abs_Compare(mul(x2, mid)) != 0) {
        result = mid;
        left = mid + 1;
      } else {
        right = mid - 1;
      }
    }
    if (result == -1) {
      result = left;
    }
    return result;
  }

  // 返回两个大整数之比
  friend int2048 div(int2048 x1, const int2048 &x2) {
    if (x1.Abs_Compare(x2) == 0) {
      if (x1.bits[0] * x2.bits[0] == 1) {
        return int2048(0);
      }
      return int2048(-1);
    }
    int shift_bit = x1.bits.size() - x2.bits.size() + 1;
    int2048 ans, ans_mul;
    ans.bits.resize(shift_bit + 1);
    ans.bits[0] = x1.bits[0] / x2.bits[0];
    while (shift_bit > 0) {
      ans.bits[shift_bit] = digit_div(x1, x2, shift_bit);
      ans_mul = mul(x2, ans.bits[0] * ans.bits[shift_bit]);
      for (int i = 0; i < shift_bit - 1; i++) {
        ans_mul.bits.insert(ans_mul.bits.begin() + 1, 0);
      }
      x1 = x1 - ans_mul;
      shift_bit--;
    }
    while (ans.bits.size() > 2 and ans.bits.back() == 0) {
      ans.bits.pop_back();
    }
    if (ans.bits[0] == -1 and x1 != 0) {
      ans.minus(1);
    }
    return ans;
  }

  int2048 &operator=(const int2048 &other) {
    bits.clear();
    for (int i = 0; i < other.bits.size(); i++) {
      bits.push_back(other.bits[i]);
    }
    return *this;
  }

  int2048 &operator+=(const int2048 &other) {
    this->add(other);
    return *this;
  }
  friend int2048 operator+(int2048 x1, const int2048 &x2) { return x1.add(x2); }

  int2048 &operator-=(const int2048 &other) {
    this->minus(other);
    return *this;
  }
  friend int2048 operator-(int2048 x1, const int2048 &x2) {
    return x1.minus(x2);
  }

  int2048 operator+() const { return *this; }
  int2048 operator-() const { return int2048(0) - *this; }

  int2048 &operator*=(const int2048 &other) {
    return *this = mul(*this, other);
  }

  int2048 &operator/=(const int2048 &other) {
    return *this = div(*this, other);
  }
  friend int2048 operator/(int2048 x1, const int2048 &x2) {
    return div(x1, x2);
  }

  int2048 &operator%=(const int2048 &other) {
    return *this = *this - other * div(*this, other);
  }
  friend int2048 operator%(int2048 x1, const int2048 &x2) {
    return x1 - x2 * div(x1, x2);
  }

  friend std::istream &operator>>(std::istream &is, int2048 &x) {
    std::string s;
    is >> s;
    x.read(s);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const int2048 &x) {
    std::string s = "";
    if (x.bits.size() == 2 and x.bits[1] == 0) { // -0输出0
      s += "0";
      os << s;
      return os;
    }
    s += (x.bits[0] == -1 ? "-" : "");
    for (int i = x.bits.size() - 1; i >= 1; i--) {
      if (i != x.bits.size() - 1) {
        for (int j = std::to_string(x.bits[i]).length(); j < NUM_BIT; j++) {
          s += "0";
        }
      }
      s += std::to_string(x.bits[i]);
    }
    os << s;
    return os;
  }
};
} // namespace sjtu

#endif