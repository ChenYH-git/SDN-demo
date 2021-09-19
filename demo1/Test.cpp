#include <iostream>
#include <string>
#include "gtest/gtest.h"
#include "myfunc.h"

using namespace std;

extern int TotalNum;
extern int IfElsNum;
extern int ElsIfNum;

TEST(TestDeleMuch, Test1) {
  string str,res;
  str = "int a aa /* int  */";
  res = "int a aa ";
  EXPECT_EQ(DeleMuch(str), res);
  EXPECT_TRUE(true);
}

TEST(TestDeleSingle, Test2) {
    string str, res;
    str = "int a aa "" // int  ";
    res = "int a aa  ";
    EXPECT_EQ(DeleSingle(str), res);
    EXPECT_TRUE(true);
}

TEST(TestDeleSingle, Test2pro) {
    string str, res;
    str = "int a aa \"int\"";
    res = "int a aa ";
    EXPECT_EQ(DeleSingle(str), res);
    EXPECT_TRUE(true);
}

TEST(TestCount_Key_Num, Test3) {
    string str, res;
    str = "#include <stdio.h> int main(){    int i=1;    double j=0;    long f;    switch(i){        case 0:            break;        case 1:            break;        case 2:            break;        default:            break;    }    switch(i){        case 0:            break;        case 1:            break;        default:            break;    }    if(i<0){        if(i<-1){}        else{}    }    else if(i>0){        if (i>2){}        else if (i==2) {}        else if (i>1) {}        else {}    }    else{        if(j!=0){}        else{}    }    return 0;}";
    res = "#include <stdio.h> int main(){    int i=1;    double j=0;    long f;    switch(i){        case 0:            break;        case 1:            break;        case 2:            break;        default:            break;    }    switch(i){        case 0:            break;        case 1:            break;        default:            break;    }    if(i<0){        if(i<-1){}        else{}    }    elseif(i>0){        if (i>2){}        elseif (i==2) {}        elseif (i>1) {}        else {}    }    else{        if(j!=0){}        else{}    }    return 0;}";
    EXPECT_EQ(Count_Key_Num(str), res);
    EXPECT_EQ(TotalNum, 35);
}

TEST(TestCount_IfEls_Num, Test4) {
    string str, res;
    str = "if(i<0){        if(i<-1){}        else{}    }    elseif(i>0){        if (i>2){}        elseif (i==2) {}        elseif (i>1) {}        else {}    }    else{        if(j!=0){}        else{}    }";
    Count_IfEls_Num(str, 3);
    EXPECT_EQ(IfElsNum, 2);
    EXPECT_EQ(ElsIfNum, 2);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);//将命令行参数传递给gtest
    return RUN_ALL_TESTS(); //RUN_ALL_TESTS()运行所有测试案例
    system("pause");
}