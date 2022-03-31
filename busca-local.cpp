#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

int compare(char A, char B) {
    if (A == B){
        return 2;
    }
    else {
        return -1;
    }
}

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
    int m; //tamanho da primeira sequencia
    int n; //tamanho da segunda sequencia
    string seq1;
    string seq2;
    cin >> m >> n >> seq1 >> seq2;

    ofstream outfile;
    outfile.open("outputLocal.txt");

    outfile << "SEQUÊNCIA 1: " << seq1  << endl;
    outfile << "TAMANHO SEQ 1: " << m << endl;
    outfile << "SEQUÊNCIA 2: " << seq2 << endl;
    outfile << "TAMANHO SEQ 2: " << n << endl << endl;

    outfile << "====================================================================================" << endl << endl;

    int count = 0;
    int max = 0;
    string subs1;
    string subs2;
    // default_random_engine gen;
    random_device seed;
    uniform_int_distribution<int> distRound(10, 50);
    uniform_int_distribution<int> distCount(10, 50);

    int roundMax = distRound(seed);
    int countMax = distCount(seed);

    for (int round = 0; round < roundMax; round++){
        uniform_int_distribution<int> distK(1, m);
        int k = distK(seed);
        uniform_int_distribution<int> distI(0, m-k);
        int i = distI(seed);
        string sub1 = seq1.substr(i, k);

        while (count < countMax){
            uniform_int_distribution<int> distJ(0, n-k);
            int j = distJ(seed);
            string sub2 = seq2.substr(j, k);
            int result = calcMax(sub1, sub2, k);

            if(result> max){
                max = result;
                subs1 = sub1;
                subs2 = sub2;
                count = 0;
            }
            count ++;
        }
        
    }
    

    // Printando as sequências ótimas
    outfile << endl << endl;
    outfile << "====================================================================================" << endl << endl;
    outfile << "SCORE MÁXIMO:" << max << endl;
    outfile << "SEQUÊNCIA 1: " << subs1 << endl;
    outfile << "SEQUÊNCIA 2: " << subs2 << endl;


    outfile.close();
    return 0;
}