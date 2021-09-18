#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <regex>
#include <stack>
#include <vector>

using namespace std;

const int KeyNum = 32;
const int SwitchIdx = 25;
const int ElseIdx = 9;

struct Key{
    string word;
    int num;
}   key[KeyNum] = {
    "auto", 0, "break", 0,
    "case", 0, "char", 0,
    "const", 0, "continue", 0,
    "default", 0, "do", 0,
    "double", 0, "else", 0,
    "enum", 0, "extern", 0,
    "float", 0, "for", 0,
    "goto", 0, "if", 0,
    "int", 0, "long", 0,
    "register", 0, "return", 0,
    "short", 0, "signed", 0,
    "sizeof", 0, "static", 0,
    "struct", 0, "switch", 0,
    "typedef", 0, "union", 0,
    "unsigned", 0, "void", 0,
    "volatile", 0, "while", 0
};
 
ifstream OpenMyFile(const string& fp) {
    ifstream testFile(fp);
    if ( !testFile.is_open() ) 
    {
        cout << "file open failed!\n";
        exit(0);
    } 
    return testFile;
}

void BinSearch(int index, int len, const string& str) {
    string wd;
    for (int i = index; i < len; i++) 
    {
        if ( isalpha(str[i]) ) 
        {
            wd += str[i];
        } 
        else if ( isalpha(str[i-1]) && !isalpha(str[i]) ) 
        {
            int high = KeyNum - 1, low = 0, cond;
            const char *s1 = wd.data();
            while( low <= high ) 
            {
                int mid = (high + low) / 2;
                const char *s2 = key[mid].word.data();
                if ( (cond = (strcmp(s1, s2))) < 0) 
                {
                    high = mid - 1;
                } 
                else if (cond > 0) 
                {
                    low = mid + 1;
                } 
                else 
                {
                    if (key[mid].word != wd)
                    {
                        break;
                    }
                    key[mid].num++;
                    break;
                }
            }
            wd = "";
        }
    }
}

string DeleSingle(const string& str) {
    string temp = str;
    regex r("//.*");
    smatch m;
    string match;
    bool found = regex_search(temp, m, r);
    if (found)
    {
        match = m.str(0);
        // cout << "single matched: " << m.str(0) << endl;
        int strlen = match.length();
        int st = temp.find(match);
        temp.erase(st, strlen);
    }
    regex x("\"([^\"]*)\"");
    found = regex_search(temp, m, x);
    if (found)
    {
        match = m.str(0);
        // cout << "single matched: " << m.str(0) << endl;
        int strlen = match.length();
        int st = temp.find(match);
        temp.erase(st, strlen);
    }
    regex z("else if");
    temp = regex_replace(temp, z, "elseif");
    return temp;
}

string DeleMuch(const string& str) {
    string temp = str;
    int st = 0, ed = 0, len = str.length() - 1;
    bool stFlag = false, edFlag = false;
    int i = 0;
    while(i < len)
    {
        if (temp[i] == '/' && temp[i+1] == '*')
        {
            st = i;
            stFlag = true;
        }
        if (temp[i] == '*' && temp[i+1] == '/')
        {
            ed = i + 2;
            edFlag = true;
        }
        if (stFlag && edFlag)
        {
            stFlag = edFlag = false;
            temp.erase(st, ed - st);
            i = ed = st - 1;
            len = temp.length() - 1;
        }
        i++;
    }
    return temp;
}

string Count_Key_Num(const string& str) {
    int total = 0,start_index = 0, end_index;;
    string NewStr = DeleMuch(str);
    end_index = NewStr.length();
    BinSearch(start_index, end_index, NewStr);
    for ( int i = 0; i < KeyNum; i++ ) 
    {
        if ( key[i].num != 0 )
        {
            total += key[i].num;
            // cout << key[i].word << " num: " << key[i].num << endl;
        }
    }
    cout << "total num: " << total << endl;
    // cout << NewStr << endl;
    return NewStr;
}

string Count_SwiCase_Num(const string& str) {
    string NewStr = Count_Key_Num(str);
    int len = NewStr.length(), index = 0, cnt;
    stack<int> IdxStack;
    while( (index = NewStr.find("switch", index)) < len && (index != -1) )
    {
        IdxStack.push(index);
        index++;
        // cout << "index:" << index << endl;
    }
    printf("switch num: %d\n", key[SwitchIdx].num);
    printf("case num:");
    vector<int> CaseNum;
    while( !IdxStack.empty() )
    {
        cnt = 0, index = IdxStack.top() + 5;
        while( (index = NewStr.find("case", index)) < len && (index != -1) )
        {
            cnt++;
            index++;
        }
        len = IdxStack.top();
        IdxStack.pop();
        CaseNum.push_back(cnt);
    }
    for (int i = CaseNum.size() - 1; i >= 0; i--)
    {
        printf(" %d", CaseNum[i]);
    }
    putchar('\n');
    return NewStr;
}

void Count_IfEls_Num(const string& str, int level) {
    string NewStr = Count_SwiCase_Num(str);
    string wd;
    stack<string> IfStack;
    int len = NewStr.length(), IfElsNum = 0, ElsIfNum = 0;
    for (int i = 0; i < len; i++) 
    {
        if ( isalpha(NewStr[i]) ) 
        {
            wd += NewStr[i];
        } 
        else if ( isalpha(NewStr[i-1]) && !isalpha(NewStr[i]) ) 
        {
            if (wd == "if" || wd == "elseif")
            {
                IfStack.push(wd);
            }
            else if (wd == "else")
            {
                if (IfStack.top() == "elseif")
                {
                    ElsIfNum++;
                    while (IfStack.top() == "elseif")
                    {
                        IfStack.pop();
                    }
                }
                else
                {
                    IfElsNum++;
                }
                IfStack.pop();
            }
            wd = "";
        }
    }
    cout << "if-else num: " << IfElsNum << endl;
    if ( level == 4 )
    {
        cout << "if-elseif-else num: " << ElsIfNum << endl;
    }
    return ;
}

void SelectFunc(int level, const string& str) {
    if (str.empty()) 
    {
        cout << "Get no text!\n";
        return ;
    }
    switch (level)
    {
    case 1: 
        Count_Key_Num(str);
        break;
    case 2:
        Count_SwiCase_Num(str);
        break;
    case 3:
        Count_IfEls_Num(str,3);
        break;
    case 4:
        Count_IfEls_Num(str,4);
        break;
    default:
        cout << "wrong level num!\n";
        return ;
    }
}

int main() {
    int level;
    string filePath;
    string str;

    cout << "input filepath: ";
    cin >> filePath;
    cout << "input level: ";
    cin >> level;

    string temp;
    ifstream file = OpenMyFile(filePath);
    while ( getline(file, temp)) 
    {
        str += DeleSingle(temp);
    }
    SelectFunc(level, str);

    file.close();
    return 0;
}
