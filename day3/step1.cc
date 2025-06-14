#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <regex>
using namespace std;

int main (int argc, char** argv) {
    const string filename = argv[1];
    string line;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "ERR opening file: " << filename << endl;
        return -1;
    }

    regex pattern("mul\\((\\d+),(\\d+)\\)");
    int result = 0;
    while (getline(file, line)) {
        istringstream iss(line);

        string text;
        while ( iss >> text ) {
            auto begin = sregex_iterator(text.begin(), text.end(), pattern);
            auto end = sregex_iterator();

            for (auto it = begin; it != end; ++it) {
                result += stoi((*it)[1].str())*stoi((*it)[2].str());
            }
        }
   
    }
    cout << result << endl;

    return 0;
}