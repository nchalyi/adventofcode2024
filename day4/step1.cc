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
    string findword = argv[2]; // word to find in file
    regex pattern1(findword);
    reverse(findword.begin(),findword.end()); // reversed word
    regex pattern2(findword);
    string line;
    ifstream file(filename);

    vector<string> cooked;
    vector<vector<char>> MATRIX;
    vector<vector<char>> MiMATRIX;
    vector<char> elm;
    vector<char> revelm;
    
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
                elm.push_back(c);
            }
            cooked.push_back(readline);
            MATRIX.push_back(elm);
            reverse(readline.begin(), readline.end());
            for (char cc : readline) {
                revelm.push_back(cc);
            }
            MiMATRIX.push_back(revelm);
            elm.clear();
            revelm.clear();
        }
    }
    // Creating elm words vector
    int rows = MATRIX.size();
    int cols = MATRIX[0].size();
    for (int i = 0; i<cols; ++i) {
        string verticalWord = "";
        for (int j = 0; j<rows; ++j) {
            verticalWord += MATRIX[j][i];
        }
        cooked.push_back(verticalWord);
    } 
    // Creating revelm words vector
    for (int d = 0; d < rows + cols - 1; ++d) {
        string diagonalWord1 = "";
        string diagonalWord2 = "";
        for (int i = max(0, d - cols + 1), j = min(d, cols - 1); i < rows && j >= 0; ++i, --j) {
            diagonalWord1 += MATRIX[i][j];
            diagonalWord2 += MiMATRIX[i][j];
        }
        cooked.push_back(diagonalWord1);
        cooked.push_back(diagonalWord2);
    }
    // Find all words
    int ll = 0;
    for (int iter = 0; iter < cooked.size(); ++iter) {
        auto pat1_begin = sregex_iterator(cooked[iter].begin(), cooked[iter].end(), pattern1);
        auto pat1_end = sregex_iterator();
        ll += distance(pat1_begin, pat1_end);
        auto pat2_begin = sregex_iterator(cooked[iter].begin(), cooked[iter].end(), pattern2);
        auto pat2_end = sregex_iterator();
        ll += distance(pat2_begin, pat2_end);
    }
    cout << "RESULT: " << ll << endl;
    return 0;
}