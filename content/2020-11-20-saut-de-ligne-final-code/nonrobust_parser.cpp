#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<string> parse1(istream& stream)
{
    vector<string> to_return;

    while(stream.good())
    {
        string line;
        getline(stream, line);
        if (stream.good())
        {
            to_return.push_back(line);
        }
    }
    return to_return;
}

vector<string> parse1bis(istream& stream)
{
    vector<string> to_return;

    while(stream.good())
    {
        string line;
        getline(stream, line);
        to_return.push_back(line);
    }
    return to_return;
}

vector<string> parse2(istream& stream)
{
    vector<string> to_return;

    string line;
    // celui-ci n'est pas robuste car il sort du while dès qu'on a atteint EOF, sans ajouter le dernier token
    while(getline(stream, line).good())
    {
        to_return.push_back(line);
    }
    cout << "ON est sorti, que valent les flags :" << endl;
    cout << boolalpha;
    cout << "\t good() " << stream.good() << endl;
    cout << "\t bad()  " << stream.bad() << endl;
    cout << "\t eof()  " << stream.eof() << endl;
    cout << "\t fail() " << stream.fail() << endl;
    return to_return;
}

vector<string> parse3(istream& stream)
{
    vector<string> to_return;

    string line;
    while(getline(stream, line))
    {
        to_return.push_back(line);
    }
    cout << "ON est sorti, que valent les flags :" << endl;
    cout << boolalpha;
    cout << "\t good() " << stream.good() << endl;
    cout << "\t bad()  " << stream.bad() << endl;
    cout << "\t eof()  " << stream.eof() << endl;
    cout << "\t fail() " << stream.fail() << endl;
    return to_return;
}

bool check(string input, vector<string> expected)
{
    cout << boolalpha;
    stringstream ssA{input};
    stringstream ssB{input};
    stringstream ssC{input};
    stringstream ssD{input};

    cout << "AVEC good()" << endl;
    cout << (parse2(ssA) == expected ? "[OK]" : "BOUM") << endl;
    cout << "AVEC operator!()" << endl;
    cout << (parse3(ssB) == expected ? "[OK]" : "BOUM") << endl;

    cout << endl;
    cout << endl;
    cout << "Mes parseurs :" << endl;
    cout << "non-robuste :      " << (parse1(ssC) == expected ? "[OK]" : "BOUM") << endl;
    cout << "    robuste :      " << (parse1bis(ssD) == expected ? "[OK]" : "BOUM") << endl;
}

int main(void)
{
    /* check("", {}); */
    /* check("\n", {""}); */
    /* check("coucou\n", {"coucou"}); */
    /* check("coucou\npouet\n", {"coucou", "pouet"}); */
    check("coucou\npouet\nyoupi", {"coucou", "pouet", "youpi"});
}
