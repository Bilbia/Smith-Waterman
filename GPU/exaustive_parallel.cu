#include <algorithm>  
#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <cstdlib>
#include <iomanip>
#include <tuple>


using namespace std;

struct calcMax{
    int diag, cima;
    char c;
    calcMax(int c_) : c(c_){};
    __host__ __device__
    int operator()(const thrust::tuple<char, int, int>& a){

        if(c == thrust::get<0>(a)){
            diagonal = thrust::get<1>(a) + 2;
        }else{
            diagonal = thrust::get<1>(a) - 1;
        }
        cima = thrust::get<2>(a) - 1;
        if ( diagonal > 0 && diagonal > cima ){
            return diagonal;
        }else if( cima > 0 && cima > diagonal){
            return cima;
        }else if(diagonal > 0 && diagonal == cima ){
            return cima;
        }else{
            return 0;
        }
    }
};

struct comp{
    __host__ __device__
    int operator()(const int& x, const int& y){
        int left = x - 1;
        int cell = y;

        if (cell > left && cell > 0){
            return cell;
        }else if(left > cell && left > 0){
            return left;
        }else if(cell == left  && cell > 0){
            return cell;
        }else{
            return 0;
        }
    }
};

int main(){
    int m, n; //tamanho da primeira e segunda sequencia
    string seq1, seq2;
    cin >> m >> n >> seq1 >> seq2;

    seq1 = '_' + seq1;
    seq2 = '_' + seq2;

    int max = -(m + n);
    int temp, lenMax;
    int k = 1;

    thrust::device_vector<char> seq1GPU(m+1);
    thrust::device_vector<char> seq2GPU(n+1);
    thrust::device_vector<int> H1(n+1);
    thrust::device_vector<int> H2(n+1);
    thrust::fill(H2.begin(), H2.end(), 0);

    for(int i = 0; i < m + 1; i++) {
        seq1GPU[i] = seq1[i];
    }
    for(int i = 0; i < n + 1; i++) {
        seq2GPU[i] = seq2[i];
    }

    if(m > n) {
        lenMax = n;
    }
    else {
        lenMax = m;
    }

    m++;
    n++;
    
    while(lenMax >= k && lenMax > 1) {
        for(int i = 0; i <= m - lenMax; i++){
            cout << i << endl;
            for(int j = 0; j <= n - lenMax; j++){
                thrust::fill(H1.begin(), H1.end(), 0);

                for(int l = 0; l < lenMax + 1; l++){
                    thrust::transform(thrust::make_zip_iterator(thrust::make_tuple(seq2GPU.begin() + 1 + j, H1.begin(), H1.begin() + 1)),
                                        thrust::make_zip_iterator(thrust::make_tuple(seq2GPU.end() + 1 + j + lenMax, H1.begin() + lenMax, H1.begin() + 1 + lenMax)),
                                        H2.begin() + 1,
                                        calcMax(seq1GPU[l]));

                    thrust::inclusive_scan(H2.begin(), H2.begin() + lenMax, H1.begin(), comp());

                    temp = thrust::reduce(H1.begin(), H1.begin() + lenMax, 0, thrust::maximum<int>());
                    
                    if(temp > max){
                        max = temp;
                    }
                }
            }
        }
        k = (max / 2) + 1;
        lenMax --;
        cout << "MAIOR SCORE: "<< max << endl;
   
    }
    return 0;
}

