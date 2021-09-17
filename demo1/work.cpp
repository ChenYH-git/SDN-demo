#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <regex>

using namespace std;

const int KeyNum = 32;

bool NotesFlag = false, StrFlag = false;

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

void Find(const string& str) {
    int start_index = 0, end_index = str.length(), len = end_index;
    for (int i = 0; i < len-1; i++) 
    {
        if (str[i]=='/' && str[i+1]=='/') 
        {
            end_index = i - 1;
            break;
        } 
        if (str[i]=='*' && str[i+1]=='/') 
        {
            NotesFlag = false;
        }
        if (str[i]=='/' && str[i+1]=='*') 
        {
            NotesFlag = true;
            end_index = i - 1;
            BinSearch(start_index, end_index, str);
        }
        if (str[i]=='"') 
        {
            if (StrFlag == false)
            {
                end_index = i - 1;
            }
            StrFlag = !StrFlag;
        }
    }
    if (NotesFlag || StrFlag) 
    {
        return ;
    }
    BinSearch(start_index, end_index, str);
}

void CountKeyNum_1(const vector<string>& str) {
    int total = 0;
    for (auto it : str) 
    {
        Find(it);
    }
    for (int i = 0; i < KeyNum; i++) 
    {
        if (key[i].num != 0)
        {
            total += key[i].num;
            cout << key[i].word << " num: " << key[i].num << endl;
        }
    }
    cout << "total num: " << total << endl;
}

void CountKeyNum_2(const vector<string>& str) {

}

void CountKeyNum_3(const vector<string>& str) {

}

void CountKeyNum_4(const vector<string>& str) {

}

void SelectFunc(int level, const vector<string>& str) {
    if (str.empty()) 
    {
        cout << "Get no text!\n";
        return ;
    }
    switch (level)
    {
    case 1: 
        CountKeyNum_1(str);
        break;
    case 2:
        CountKeyNum_2(str);
        break;
    case 3:
        CountKeyNum_3(str);
    case 4:
        CountKeyNum_4(str);
    default:
        cout << "error level num!\n";
        return ;
    }
}

int main() {
    int level;
    string filePath;
    vector<string> str;

    cout << "input filepath: ";
    cin >> filePath;
    cout << "input level: ";
    cin >> level;

    string temp;
    ifstream file = OpenMyFile(filePath);
    while ( getline(file, temp)) 
    {
        str.push_back(temp);
    }
    SelectFunc(level, str);

    file.close();
    return 0;
}
