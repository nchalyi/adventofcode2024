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
    int ll = 0;
    vector<int> report;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "ERR opening file: " << filename << endl;
        return -1;
    }
    while (getline(file, line)) {
        istringstream iss(line);
        int num;
        while (iss >> num) {
            report.push_back(num);
        }
        int notsafe = 0;
        vector<int> sign;
        for (int k = 1; k < report.size(); k++) {
            if (report[k-1] - report[k] >= 0) {
                sign.push_back(1);
            } else {
                sign.push_back(0);
            }
            int diff = abs(report[k-1] - report[k]);
            if (diff > 3 || diff == 0 ) {
                notsafe++;
            }
            for (int j = 1; j < sign.size(); j++) {
                if (sign[j-1] != sign[j]) {
                    notsafe++;
                }          
            }
        }
        report.clear();
        if (notsafe == 0) {
            ll++;
        }
    }
    cout << "RESULT: " << ll << endl;
    return 0;
}