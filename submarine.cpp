#include <iostream>   
#include <vector>  
  
using namespace std;  
  
int N,M,K,X;

int read_int() {
    int n = 0;
    char c = getchar_unlocked();
    while ( !( '0' <= c && c <= '9' ) ) {
        c = getchar_unlocked();
    }
    while ( '0' <= c && c <= '9' ) {
        n = n * 10 + c - '0';
        c = getchar_unlocked();
    }
    return n;
}

int number_of_paths(int position, int available, int** &DP, vector<int>* v, bool* &pilotikh) {
    if (DP[position][available] < 0) {
        int numPaths = 0, new_available = available;
        if (pilotikh[position]) new_available--;
        for (int i=0; i<v[position].size(); i++) {
            numPaths += number_of_paths(v[position][i], new_available, DP, v, pilotikh);
            numPaths = numPaths % 1000000103;
        }
        DP[position][available] = numPaths;
    }
    return DP[position][available];
}

int main() {
    N = read_int();
    M = read_int();
    K = read_int();
    X = read_int();

    vector<int> *v = new vector<int> [N*M];

    bool *pilotikh = new bool[N*M];
    for(int i=0; i<N*M; i++) {
        pilotikh[i] = false;
    }

    int s, e, s_x, s_y, e_x, e_y;
    for (int i=0; i<K; i++){  
        s = read_int();
        e = read_int();
        s_x = s / M;  
        s_y = s % M;  
        e_x = e / M;  
        e_y = e % M ; 
        v[s_x*M + s_y].push_back(e_x*M + e_y);
        pilotikh[s_x*M + s_y] = true;
    }

    for (int i = 0; i< N; i++) { 
        for (int j=0; j< M ; j++) {
            if(!pilotikh[i*M+j]) {
                if (i!=0) v[i*M+j].push_back(M*(i-1)+j);  
                if (j!=0) v[i*M+j].push_back(i*M+j-1);
            }
        }
    }

    int** DP;
    DP = new int* [N*M];
    for (int i=0; i<N*M; i++) DP[i]= new int[X+1];

    for (int i=0; i<N*M; i++) {
        if (pilotikh[i]) {
            DP[i][0] = 0;
        }
        else {
            DP[i][0] = -1;
        }
        for (int j=1; j<X+1; j++) {
            DP[i][j] = -1;
            
        }
    }
    for (int i=0; i<X+1; i++) {
        DP[0][i] = 1;
    }

    cout << number_of_paths(N*M-1, X, DP, v, pilotikh) << endl;

    return 0;
}