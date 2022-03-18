#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

int compare(char A, char B) {
    if (A == B){
        return 2;
    }
    else {
        return -1;
    }
}

int calcMax(int diag, int del, int ins) {
    int max = 0;
    if(diag>max) {
        max = diag;
    }
    if(del>max) {
        max = del;
    }
    if(ins>max) {
        max = ins;
    }
    return max;
}

int main() {
    int m; //tamanho da primeira sequencia
    int n; //tamanho da segunda sequencia
    string seq1;
    string seq2;
    cin >> n >> m >> seq1 >> seq2;

    int max;
    int diag = 0;
    int del = 0;
    int ins = 0;
    vector<vector<int>> H;

    ofstream outfile;
    outfile.open("output.txt");

    outfile << "eae";
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            diag = H[i-1][j-1] + compare(seq1[i], seq2[j]);
            del = H[i-1][j] - 1;
            ins = H[i][j-1] - 1;

            H[i][j] = calcMax(diag, del, ins);
            outfile << H[i][j] << " ";
        }
    }

    for(int i = 0; i <=n; i++){
        for(int j = 0; j <=m; j++){
            outfile << H[i][j] << " ";
        }
        outfile << std::endl;
    }
    outfile.close();









    return 0;
}