#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

int Check(vector<int> report) {
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
            notsafe = 1;
        }
        for (int j = 1; j < sign.size(); j++) {
            if (sign[j-1] != sign[j]) {
                notsafe = 1;
            }          
        }
    }
    return notsafe;
}

int main (int argc, char** argv) {
    const string filename = argv[1];
    string line;
    int ll = 0;
    int lll = 0;
    vector<int> report;
    vector<vector<int>> whole;
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
        whole.push_back(report);
        report.clear();
    }
    for (const auto& row : whole) {

        for (int nume : row) {
            cout << nume << " ";
        }
        cout << endl;

        int safe = Check(row);
        if (safe == 0) {
            ll++;
        } else {
            for (size_t i = 0; i < row.size(); ++i) {
                vector<int> temp = row;
                temp.erase(temp.begin() + i);
                int safe2 = Check(temp);
                if (safe2 == 0) {
                    ll++;
                    break;
                }
            }
        }
    }
    cout << "RESULT: " << ll << endl;
    return 0;
}