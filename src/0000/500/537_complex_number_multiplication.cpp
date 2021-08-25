// 537_complex_number_multiplication
// Nevin Zheng
// 8/24/21

#include <bits/stdc++.h>
#include <catch2/catch.hpp>
#include <fmt/format.h>

using namespace std;

class Complex {
 public:
  int real_;
  int imag_;

  Complex(int real, int imag) : real_(real), imag_(imag) {}

  explicit Complex(const string& s) {
    auto plus_it = s.find('+');
    auto i_it = s.find('i');
    real_ = std::stoi(s.substr(0, plus_it));
    imag_ = std::stoi(s.substr(plus_it + 1, i_it - plus_it + 1));
  }

  [[nodiscard]] std::string to_string() const {
    std::stringstream ss;
    ss << real_ << '+' << imag_ << 'i';
    return ss.str();
  }

  static Complex multiply(const Complex& x, const Complex& y) {
    auto a = x.real_;
    auto b = x.imag_;
    auto c = y.real_;
    auto d = y.imag_;
    return Complex(a * c - b * d, b * c + a * d);
  }
};

class Solution {
 public:
  static string complexNumberMultiply(const string& num1, const string& num2) {
    Complex x{num1};
    Complex y{num2};
    return Complex::multiply(x, y).to_string();
  }
};

TEST_CASE("537::1", "[537]") {
  string num1 = "1+1i";
  string num2 = "1+1i";
  string expected = "0+2i";
  REQUIRE(Solution::complexNumberMultiply(num1, num2) == expected);
}

TEST_CASE("537::2", "[537]") {
  string num1 = "1+-1i";
  string num2 = "1+-1i";
  string expected = "0+-2i";
  REQUIRE(Solution::complexNumberMultiply(num1, num2) == expected);
}