#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "test_runner.h"
#include "../src/poly_sparse.h"

using namespace std;


void TestConstructors() {
  // const
  cout << "test const\n";
  vector<double> coeffs = {15.1};
  Polynomial<double> p1(coeffs);
  AssertEqual(p1[0], 15.1, "const from vector 1");
  AssertEqual(p1[1], 0, "const from vector 2");
  AssertEqual(p1[10], 0, "const from vector 3");

  Polynomial<double> p2(-23.45);
  AssertEqual(p2[0], -23.45, "const from constructor 4");
  AssertEqual(p2[1], 0, "const from constructor 5");
  AssertEqual(p2[10], 0, "const from constructor 6");

  // const coefficient is zero
  cout << "test non-const only\n";
  coeffs = {0, 1.2};
  Polynomial<double> p3(coeffs);
  AssertEqual(p3[0], 0, "non-const from vector 7");
  AssertEqual(p3[1], 1.2, "non-const from vector 8");
  AssertEqual(p3[10], 0, "non-const from vector 9");

  // common coefficients
  cout << "test common coefficients\n";
  coeffs = {1, 2, 0, 14.3, -4, 0};
  Polynomial<double> p4(coeffs);
  AssertEqual(p4[0], 1, "common from vector 10");
  AssertEqual(p4[1], 2, "common from vector 11");
  AssertEqual(p4[2], 0, "common from vector 12");
  AssertEqual(p4[3], 14.3, "common from vector 13");
  AssertEqual(p4[4], -4, "common from vector 14");
  AssertEqual(p4[5], 0, "common from vector 15");
  AssertEqual(p4[10], 0, "common from vector 16");

  // construct using iterators
  cout << "test iterators\n";
  coeffs = {33.21};
  Polynomial<double> p5(coeffs.begin(), coeffs.end());
  AssertEqual(p5[0], 33.21, "const from vector using iterators 17");
  AssertEqual(p5[10], 0, "const from vector using iterators 18");
  
  coeffs = {0, 0, 20, 33.21};
  Polynomial<double> p6(coeffs.begin(), coeffs.end());
  AssertEqual(p6[0], 0, "common from vector using iterators 19");
  AssertEqual(p6[1], 0, "common from vector using iterators 20");
  AssertEqual(p6[2], 20, "common from vector using iterators 21");
  AssertEqual(p6[3], 33.21, "common from vector using iterators 22");
  AssertEqual(p6[10], 0, "common from vector using iterators 23");

  coeffs = {1, 2, 0, 3, 0, 4};
  Polynomial<double> p7(coeffs.begin(), coeffs.end());
  AssertEqual(p7[0], 1, "common from vector using iterators 24");
  AssertEqual(p7[1], 2, "common from vector using iterators 25");
  AssertEqual(p7[2], 0, "common from vector using iterators 26");
  AssertEqual(p7[3], 3, "common from vector using iterators 27");
  AssertEqual(p7[4], 0, "common from vector using iterators 28");
  AssertEqual(p7[5], 4, "common from vector using iterators 29");
  AssertEqual(p7[10], 0, "common from vector using iterators 30");
}

void TestBasicArithmetics() {
  //const
  AssertEqual(Polynomial<double>(2.03) + Polynomial<double>(4.39), Polynomial<double>(2.03 + 4.39), "sum of two const 1");
  AssertEqual(Polynomial<double>(2.03) + 4.39, Polynomial<double>(2.03 + 4.39), "sum of two const 2");
  AssertEqual(Polynomial<double>(2.04) - Polynomial<double>(2.04), Polynomial<double>(0), "constitution of two const 3");
  AssertEqual(Polynomial<double>(2) - 3, Polynomial<double>(-1), "constitution of two const 4");

  // non-const of same degree
  AssertEqual(Polynomial<double>({0, 0, 3.5}) + Polynomial<double>({0, 0, 4.03}), Polynomial<double>({0, 0, 3.5 + 4.03}), "sum of two non-const 5");
  AssertEqual(Polynomial<double>({0, 2, 0, 3, 0}) - Polynomial<double>({0, 2, 0, 3, 0, 0}), Polynomial<double>(0), "sum of two non-const 6");

  // non-const of different degrees
  AssertEqual(Polynomial<double>({0, 0, 3.5}) + Polynomial<double>({0, 2, 0, 0, 4.45}), Polynomial<double>({0, 2, 3.5, 0, 4.45}), "sum of two non-const 7");
  AssertEqual(Polynomial<double>({0, 2, 0, 21.4}) - Polynomial<double>({1, 2, 3.47, 1.2}), Polynomial<double>({-1, 0, -3.47, 20.2}), "sum of two non-const 8");
}

void TestMultiplicationAndDivision() {
  // multiplication
  AssertEqual(Polynomial<int>({1, 1, 0}) * Polynomial<int>({1, 1, 0}), Polynomial<int>({1, 2, 1}), "multiplication 1");
  AssertEqual(Polynomial<int>({1, 2, 0}) * Polynomial<int>({2, 3, 0}), Polynomial<int>({2, 7, 6}), "multiplication 2");
  AssertEqual(Polynomial<int>({2}) * Polynomial<int>({2, 0, 4, 1}), Polynomial<int>({4, 0, 8, 2}), "multiplication 3");
  AssertEqual(2 * Polynomial<int>({2, 0, 4, 1}), Polynomial<int>({4, 0, 8, 2}), "multiplication 4");
  AssertEqual(Polynomial<int>({2, 0, 4, 1}) * 2, Polynomial<int>({4, 0, 8, 2}), "multiplication 5");
  AssertEqual(Polynomial<int>({2, 0, 4, 1}) * 0, 0, "multiplication 5");

  // division
  AssertEqual(Polynomial<double>({2, 0, 4, 1}) / Polynomial<double>(2), Polynomial<double>({1, 0, 2, 0.5}), "division 6");
  AssertEqual(Polynomial<double>({1, 2, 1}) / Polynomial<double>({1, 1, 0}), Polynomial<double>({1, 1, 0}), "multiplication 7");
}

void TestFunctional() {
  // common
  AssertEqual(Polynomial<int>({1, 2, 1})(0), 1, "func 1");
  AssertEqual(Polynomial<int>({1, 2, 1})(5), 36, "func 2");
  AssertEqual(Polynomial<int>({-2, 1, 3, 0, 4})(-1), 4, "func 3");
  AssertEqual(Polynomial<int>({1, 2, 3, 4})(2), 49, "func 4");
}

void TestGCD() {
  auto p1 = Polynomial<double>({1, 1, 0});
  auto p2 = Polynomial<double>({2, 1, -3});
  auto p3 =  Polynomial<double>({2, 0, 1, 34});
  auto p4 =  Polynomial<double>({9, 3, -1, 2});

  AssertEqual((p1, p1), p1, "GCD 1");
  AssertEqual((p1 * p3, p2 * p4), Polynomial<double>(1), "GCD 2");
}

void TestOutput() {
  stringstream buffer1;
  buffer1 << Polynomial<int>(2);
  AssertEqual(buffer1.str(), "2", "output 1");

  stringstream buffer2;
  buffer2 << Polynomial<int>({1, 2, 1});
  AssertEqual(buffer2.str(), "x^2+2*x+1", "output 2");

  stringstream buffer3;
  buffer3 << Polynomial<int>({0, 2, 10, 0, 23});
  AssertEqual(buffer3.str(), "23*x^4+10*x^2+2*x", "output 3");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestConstructors, "TestConstructors");
  runner.RunTest(TestBasicArithmetics, "TestBasicArithmetics");
  runner.RunTest(TestMultiplicationAndDivision, "TestMultiplicationAndDivision");
  runner.RunTest(TestFunctional, "TestFunctional");
  runner.RunTest(TestGCD, "TestGCD");
  runner.RunTest(TestOutput, "TestInputOutput");


  return 0;
}
