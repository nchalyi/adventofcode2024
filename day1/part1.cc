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
    vector<int> sum1;
    vector<int> sum2;
    vector<int> newcollum1 = collum1;
    vector<int> newcollum2 = collum2;

    // Creating list of smallest numbers in vec 1
    for (int i = 0; i < collum1.size(); i++) {
        auto min_in1 = min_element(newcollum1.begin(),newcollum1.end());
        sum1.push_back(*min_in1);
        auto it = std::find(newcollum1.begin(), newcollum1.end(), *min_in1);
        newcollum1.erase(it);
    }

    // Creating list of smallest numbers in vec 2
    for (int i2 = 0; i2 < collum2.size(); i2++) {
        auto min_in2 = min_element(newcollum2.begin(),newcollum2.end());
        sum2.push_back(*min_in2);
        auto it2 = std::find(newcollum2.begin(), newcollum2.end(), *min_in2);
        newcollum2.erase(it2);
    }

    int ll = 0;
    // Output
    for (int k = 0; k < sum1.size(); k++) {
        //cout << k << " " << sum1[k] << " " << sum2[k] << endl;
        vector<int> checkvec = {sum1[k],sum2[k]};
        auto check = minmax_element(checkvec.begin(),checkvec.end());
        int diff = *check.second - *check.first;
        cout << k << "-st element distance: " << diff << endl;

        ll += diff;
    }
    cout << "RESULT: " << ll << endl; // Sum of all diffs
    return 0;
}