#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

int main (int argc, char** argv) {
    const string filename = argv[1]; // filename
    string line;
    ifstream file(filename);

    vector<vector<string>> MATRIX;
    vector<string> elm;
    
    if (!file.is_open()) {
        cerr << "ERR opening file: " << filename << endl;
        return -1;
    }
    // Read file and create horizondtal words vector
    while (getline(file, line)) {
        istringstream iss(line);
        string readline;
        while ( iss >> readline ) {
            for (char c : readline) {
                string s = "";
                s+=c;
                elm.push_back(s);
            }
            MATRIX.push_back(elm);
            elm.clear();
        }
    }
    // Creating elm words vector
    const int rows = MATRIX.size();
    const int cols = MATRIX[0].size();
    const string center = "A";
    const string M1 = "M";
    const string S1 = "S";
    int ll = 0;
    for (int i = 0; i<rows; ++i) {
        for (int j = 0; j<cols; ++j) {
            string tmp = MATRIX[i][j];
            //cout << tmp << " ";
            if (tmp == center) {
                if (i > 0 && i < rows-1 && j > 0 && j < cols-1) {
                    if (((MATRIX[i-1][j-1] == M1 && MATRIX[i-1][j+1] == S1) && 
                        (MATRIX[i+1][j-1] == M1 && MATRIX[i+1][j+1] == S1))||
                        ((MATRIX[i-1][j-1] == M1 && MATRIX[i-1][j+1] == M1) && 
                        (MATRIX[i+1][j-1] == S1 && MATRIX[i+1][j+1] == S1))||
                        ((MATRIX[i-1][j-1] == S1 && MATRIX[i-1][j+1] == S1) && 
                        (MATRIX[i+1][j-1] == M1 && MATRIX[i+1][j+1] == M1))||
                        ((MATRIX[i-1][j-1] == S1 && MATRIX[i-1][j+1] == M1) && 
                        (MATRIX[i+1][j-1] == S1 && MATRIX[i+1][j+1] == M1))){
                            ll++;                            
                    }
                }
            }
        } 
        //cout << endl;
    } 
    cout << "RESULT: " << ll << endl;
    return 0;
}