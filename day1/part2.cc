#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int main (int argc, char** argv) {
    const string filename = argv[1];
    string line;
    vector<int> collum1;
    vector<int> collum2;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "ERR opening file: " << filename << endl;
        return -1;
    }

    // Get every symbol from line and put them in 2 arrays
    while (getline(file, line)) {
        istringstream iss(line);
        int n,k;
        if (iss >> n >> k) {
            collum1.push_back(n);
            collum2.push_back(k);
        }
    }
    int ll = 0;
    // Output
    for (int k = 0; k < collum1.size(); k++) {
        auto often = std::count(collum2.begin(), collum2.end(), collum1[k]);
        ll += collum1[k]*(often);
        cout << collum1[k]*(often) << endl;
    }
    cout << "RESULT: " << ll << endl; // Sum of all diffs
    return 0;
}