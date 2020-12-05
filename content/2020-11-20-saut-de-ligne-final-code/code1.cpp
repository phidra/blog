#include <sstream>
#include <vector>

using namespace std;

vector<string> parse(istream& stream)
{
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
    istringstream iss("line1\nline2\n");
    bool is_ok = parse(iss) == vector<string>{"line1", "line2"};
    return int(!is_ok);
}
