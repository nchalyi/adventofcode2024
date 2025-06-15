#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;

// function for splitting line by pattern
vector<string> splitIgnoreDelimiters(const string text, const regex pattern) {
    vector<string> parts;
    sregex_token_iterator it(text.begin(), text.end(), pattern, -1);
    sregex_token_iterator end;
    
    while (it != end) {
        if (!it->str().empty())
            parts.push_back(*it);
        ++it;
    }
    
    return parts;
}

int main (int argc, char** argv) {
    const string filename = argv[1];
    string line;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "ERR opening file: " << filename << endl;
        return -1;
    }
    line = string((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
    regex pattern("mul\\((\\d+),(\\d+)\\)");
    int result = 0;
    regex noway("don\\'t\\(\\)[\\s\\S]*?do\\(\\)");
    auto newline = splitIgnoreDelimiters(line, noway);         
    for (const auto block : newline) {
        cout << "step 1 " << block << endl;
        regex dontcheck("don\\'t\\(\\)[\\s\\S]*$");
        string inblock = regex_replace(block, dontcheck, "");
        cout << "step 2 " << inblock << endl;
        auto inbegin = sregex_iterator(inblock.begin(), inblock.end(), pattern);
        auto inend = sregex_iterator();

        for (auto it = inbegin; it != inend; ++it) {
            cout << (*it)[1].str() << " " << (*it)[2].str() << endl;
            result += stoi((*it)[1].str())*stoi((*it)[2].str());
        }
    }
    cout << result << endl;

    return 0;
}