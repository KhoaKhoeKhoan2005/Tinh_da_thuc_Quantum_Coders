#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
using namespace std;

int Tinh(string s) {
    vector<int> numbers;
    vector<char> operators;
    string temp = "";
    for (int i = 0; i < s.size(); ++i) {
        if (isdigit(s[i])) {
            temp += s[i];
        }
        else {
            numbers.push_back(stoi(temp));
            operators.push_back(s[i]);
            temp = "";
        }
    }
    if (!temp.empty()) {
        numbers.push_back(stoi(temp));
    }
    for (int i = 0; i < operators.size(); ++i) {
        if (operators[i] == '*' || operators[i] == '/') {
            int left = numbers[i];
            int right = numbers[i + 1];
            int result = (operators[i] == '*') ? (left * right) : (left / right);
            numbers[i] = result;
            numbers.erase(numbers.begin() + i + 1);
            operators.erase(operators.begin() + i);
            --i;
        }
    }
    int result = numbers[0];
    for (int i = 0; i < operators.size(); ++i) {
        if (operators[i] == '+') {
            result += numbers[i + 1];
        }
        else if (operators[i] == '-') {
            result -= numbers[i + 1];
        }
    }
    return result;
}

void Thay_The(string& s) {
    int start, end;
    while ((start = s.find_last_of('(')) != string::npos) {
        end = s.find(')', start);
        if (end == string::npos) break;
        string subExpr = s.substr(start + 1, end - start - 1);
        int value = Tinh(subExpr);
        s.replace(start, end - start + 1, to_string(value));
    }
}

int main() {
    string s;
    cout << "Nhap bieu thuc: ";
    cin >> s;
    Thay_The(s);
    int result = Tinh(s);
    cout << "Gia tri cua bieu thuc la: " << result << endl;

    return 0;
}