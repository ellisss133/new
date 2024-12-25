#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string trimZeros(string number)
{
    while (number.size() > 1 && number[0] == '0')
    {
        number.erase(0, 1);
    }
    return number;
}

int compareNumbers(string first, string second)
{
    if (first.size() > second.size())
        return 1;
    if (first.size() < second.size())
        return -1;
    return first.compare(second);
}

string sumNumbers(string first, string second)
{
    string result = "";
    int carry = 0;
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());

    int maxLength = max(first.size(), second.size());
    for (int i = 0; i < maxLength; i++)
    {
        int digit1 = i < first.size() ? first[i] - '0' : 0;
        int digit2 = i < second.size() ? second[i] - '0' : 0;
        int total = digit1 + digit2 + carry;
        carry = total / 10;
        result += (total % 10) + '0';
    }
    if (carry)
    {
        result += carry + '0';
    }
    reverse(result.begin(), result.end());
    return result;
}

string subtractNumbers(string first, string second)
{
    string result = "";
    int borrow = 0;
    reverse(first.begin(), first.end());
    reverse(second.begin(), second.end());

    for (int i = 0; i < first.size(); i++)
    {
        int digit1 = first[i] - '0';
        int digit2 = i < second.size() ? second[i] - '0' : 0;
        int difference = digit1 - digit2 - borrow;
        if (difference < 0)
        {
            difference += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        result += difference + '0';
    }
    reverse(result.begin(), result.end());
    return trimZeros(result);
}

string multiplyNumbers(string first, string second)
{
    string result(first.size() + second.size(), '0');

    for (int i = first.size() - 1; i >= 0; i--)
    {
        int carry = 0;
        for (int j = second.size() - 1; j >= 0; j--)
        {
            int temp = (result[i + j + 1] - '0') + (first[i] - '0') * (second[j] - '0') + carry;
            result[i + j + 1] = (temp % 10) + '0';
            carry = temp / 10;
        }
        result[i] += carry;
    }
    return trimZeros(result);
}

string divideNumbers(string first, string second)
{
    if (second == "0")
    {
        return "Error: Division by zero";
    }

    string result = "";
    string remainder = "";

    for (char digit : first)
    {
        remainder += digit;
        remainder = trimZeros(remainder);
        int count = 0;
        while (compareNumbers(remainder, second) >= 0)
        {
            remainder = subtractNumbers(remainder, second);
            count++;
        }
        result += count + '0';
    }
    return trimZeros(result);
}

int main()
{
    string first, second;
    char operation;

    cout << "Enter first number: ";
    cin >> first;
    cout << "Enter operator (+, -, *, /, <, >, =): ";
    cin >> operation;
    cout << "Enter second number: ";
    cin >> second;

    switch (operation)
    {
    case '+':
        cout << "Result: " << sumNumbers(first, second) << endl;
        break;

    case '-':
        if (compareNumbers(first, second) >= 0)
            cout << "Result: " << subtractNumbers(first, second) << endl;
        else
            cout << "Result: -" << subtractNumbers(second, first) << endl;
        break;

    case '*':
        cout << "Result: " << multiplyNumbers(first, second) << endl;
        break;

    case '/':
        cout << "Result: " << divideNumbers(first, second) << endl;
        break;

    case '>':
        cout << (compareNumbers(first, second) > 0 ? "true" : "false") << endl;
        break;

    case '<':
        cout << (compareNumbers(first, second) < 0 ? "true" : "false") << endl;
        break;

    case '=':
        cout << (compareNumbers(first, second) == 0 ? "true" : "false") << endl;
        break;

    default:
        cout << "Invalid operator!" << endl;
        break;
    }
}
