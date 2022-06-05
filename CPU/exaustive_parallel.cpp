#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <random>
#include <omp.h>
#include <bits/stdc++.h>

using namespace std;

int calcMax(string sub1, string sub2, int k) {
    int max = 0;
    for(int i=0; i<k; i++){
        if(sub1[i] == sub2[i]){
            max += 2;
        }
        else{
            max -= 1;
        }
    }
    return max;
}

int main() {
    omp_set_num_threads(8);
    int m; //tamanho da primeira sequencia
    int n; //tamanho da segunda sequencia
    string seq1;
    string seq2;
    cin >> m >> n >> seq1 >> seq2;

    ofstream outfile;
    outfile.open("outputExaustiva.txt");

    outfile << "SEQUÊNCIA 1: " << seq1  << endl;
    outfile << "TAMANHO SEQ 1: " << m << endl;
    outfile << "SEQUÊNCIA 2: " << seq2 << endl;
    outfile << "TAMANHO SEQ 2: " << n << endl << endl;

    outfile << "====================================================================================" << endl << endl;

    string maxSub1;
    string maxSub2;
    int max = 0;

    vector<string> subs1;
    vector<string> subs2;


    // Gerando todas as substrings de A
    for (int k = 1; k <= m; k++){
        for (int i = 0; i <= (m - k); i++){
            subs1.push_back(seq1.substr(i, k));
        }
    }

    // Gerando todas as substrings de B
    for (int k = 1; k <= n; k++){
        for (int i = 0; i <= (n - k); i++){
            subs2.push_back(seq2.substr(i, k));
        }
    }


    // Comparando todas as subsequências
    #pragma omp parallel for reduction(max:max)
    for (int i = 0; i < subs1.size(); i++){
        string sub1 = subs1[i];

        for (int j = 0; j < subs2.size(); j++){
            string sub2 = subs2[j];

            if (sub1.size() == sub2.size()){
                int result = calcMax(sub1, sub2, sub1.size());
                if (result > max){
                    max = result;
                    maxSub1 = sub1;
                    maxSub2 = sub2;
                }
            }
        }
    }
    

    // Printando as sequências ótimas
    outfile << endl << endl;
    outfile << "SCORE MÁXIMO:" << max << endl;
    outfile << "SEQUÊNCIA 1: " << maxSub1 << endl;
    outfile << "SEQUÊNCIA 2: " << maxSub2 << endl;


    outfile.close();
    return 0;
}