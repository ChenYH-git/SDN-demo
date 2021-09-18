#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "myfunc.h"

using namespace std;

TEST(TestCountDeleMuch, Test1) {
  string str,res;
  str = "int a aa /* int  */";
  res = "int a aa ";
  EXPECT_EQ(DeleMuch(str), res);
  EXPECT_TRUE(true);
}

TEST(TestDeleSingle, Test2) {
    string str, res;
    str = "int a aa // int main";
    res = "int a aa ";
    EXPECT_EQ(DeleSingle(str), res);
    EXPECT_TRUE(true);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);//将命令行参数传递给gtest
    return RUN_ALL_TESTS(); //RUN_ALL_TESTS()运行所有测试案例
    system("pause");
}