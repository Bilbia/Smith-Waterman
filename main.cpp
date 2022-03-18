#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

struct cell{
    int value = 0;
    int x;
    int y;
};

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

    cell max;
    int diag = 0;
    int del = 0;
    int ins = 0;
    cell H[n+1][m+1] = {};

    ofstream outfile;
    outfile.open("output.txt");

    outfile << "SEQUÊNCIA 1: " << seq1  << endl;
    outfile << "TAMANHO SEQ 1: " << n << endl;
    outfile << "SEQUÊNCIA 2: " << seq2 << endl;
    outfile << "TAMANHO SEQ 2: " << m << endl << endl;

    outfile << "====================================================================================" << endl << endl;

    // Gerando a matriz
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            diag = H[i-1][j-1].value + compare(seq1[i-1], seq2[j-1]);
            del = H[i-1][j].value - 1;
            ins = H[i][j-1].value - 1;

            H[i][j].value = calcMax(diag, del, ins);
            H[i][j].x = i;
            H[i][j].y = j;

            if(H[i][j].value > max.value){
                max = H[i][j];
            }
        }
    }

    // Printando a matriz
    outfile << "MATRIZ GERADA:" << endl << endl;
    for(int i = 0; i <=n; i++){
        for(int j = 0; j <=m; j++){
            outfile << H[i][j].value << " ";
        }
        outfile << endl;
    }

    outfile << endl << "VALOR MÁXIMO ENCONTRADO: " << max.value << endl;
    outfile << "POSIÇÃO DO VALOR MÁXIMO ENCONTRADO: (" << max.x << ", " << max.y << ")" << endl;
    
    // Pegando sequências ótimas
    vector<cell> seq;
    cell current = max;
    seq.push_back(current);
    string ali1 = "";
    string ali2 = "";

    while (current.value > 0) {
        diag = H[current.x - 1][current.y - 1].value + 2;
        del = H[current.x - 1][current.y].value;
        ins = H[current.x][current.y - 1].value;

        int dir = calcMax(diag, del, ins);
        if (dir == diag) {
            current = H[current.x-1][current.y-1];
            seq.push_back(current);
            ali1 += seq1[current.x];
            ali2 += seq2[current.y];

        }
        else if (dir == del) {
            current = H[current.x-1][current.y];
            seq.push_back(current);
            ali1 += seq1[current.x];
            ali2 += "_";

        }
        else if (dir == ins) {
            current = H[current.x][current.y-1];
            seq.push_back(current);
            ali1 += "_";
            ali2 += seq2[current.y];
        }        
    }

    reverse(ali1.begin(), ali1.end());
    reverse(ali2.begin(), ali2.end());


    outfile << "VALORES CAMINHADA DE VOLTA: ";
    for (int i = 0; i < seq.size(); i++){
        outfile << seq[i].value << " ";
    }

    // Printando as sequências ótimas
    outfile << endl << endl;
    outfile << "====================================================================================" << endl << endl;
    outfile << "ALINHAMENTO SEQUENCIAL ÓTIMO:" << endl;
    outfile << "SEQUÊNCIA 1: " << ali1 << endl;
    outfile << "SEQUÊNCIA 2: " << ali2 << endl;


    outfile.close();
    return 0;
}