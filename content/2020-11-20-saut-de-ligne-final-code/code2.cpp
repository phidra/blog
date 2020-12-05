#include <iostream>
#include <sstream>
#include <vector>
#include <cassert>

using namespace std;

vector<string> loose_parse(string str)
{
    istringstream stream(str);
    vector<string> to_return;
    string line;
    while(getline(stream, line))
    {
        to_return.push_back(line);
    }
    return to_return;
}

vector<string> strict_parse(string str)
{
    istringstream stream(str);
    vector<string> to_return;
    string line;
    while(getline(stream, line).good())
    {
        to_return.push_back(line);
    }
    return to_return;
}

int main(void)
{
    assert((strict_parse("pomme\npêche\npoire") == vector<string>{"pomme", "pêche"}));
    assert((strict_parse("\npêche\npoire") == vector<string>{"", "pêche"}));
    assert((strict_parse("pomme\n\npoire") == vector<string>{"pomme", ""}));
    assert((strict_parse("pomme\npêche\n") == vector<string>{"pomme", "pêche"})); // ok :-)

    assert((loose_parse("pomme\npêche\npoire") == vector<string>{"pomme", "pêche", "poire"}));
    assert((loose_parse("\npêche\npoire") == vector<string>{"", "pêche", "poire"}));
    assert((loose_parse("pomme\n\npoire") == vector<string>{"pomme", "", "poire"}));
    assert((loose_parse("pomme\npêche\n") == vector<string>{"pomme", "pêche", ""})); // boum !

    cout << "All is OK :-)" << endl;
    return 0;
}

