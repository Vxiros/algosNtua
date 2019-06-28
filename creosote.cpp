#include <bits/stdc++.h>
        
using namespace std;      
        
int N, a, b, c;      
        
class Grammh {
public:
    long long int a, b;

    Grammh() {}
    
    Grammh(long long int new_a, long long int new_b) {
        a = new_a;
        b = new_b;
    }

    void set(long long int new_a, long long int new_b) {
        a = new_a;
        b = new_b;
    }

    long long int y(long long int x) {
        return a*x + b;
    }
};

vector<Grammh> G;
int start = 0;

bool useless(Grammh g1, Grammh g2, Grammh g3) {
    return (g3.b - g1.b) * (g1.a - g2.a) > (g2.b - g1.b) * (g1.a - g3.a);
}

void add(Grammh g) {
    int size;
    while(G.size()>=2) {
        size = G.size();
        if (useless(G[size-1], G[size-2], g)) {
            G.pop_back();
        }
        else {
            break;
        }
    }
    G.push_back(g);
}

long long int search(long long int x) {
    int size = G.size();
    if (start>=size) start = size-1;
    while(start<size-1) {
        if(G[start].y(x) < G[start+1].y(x)) {
            start++;
        }
        else {
            break;
        }
    }
    return G[start].y(x);
}

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
   
void read_input(long long int* &X) {      
    for(int i=0; i<N; i++) {
        X[i] = read_int();
    }      
}      
        
void find_sums(long long int* &X, long long int* &S) {      
    S[0] = X[0];      
    for(int i=1; i<N; i++) {      
        S[i] = S[i-1] + X[i];      
    }      
}      
        
long long int f(long long int x) {      
    return a*x*x + b*x + c;      
}

long long int max(long long int a, long long int b) {
    if (a>b) return a;
    return b;
}
        
void find_tastes(long long int* &S, long long int* &T) {
    long long int fsi, s;
    T[0] = f(S[0]);
    Grammh g( -2*a*S[0] , S[0]*(a*S[0]-b) + T[0]);
    add(g);
    for(int i=1; i<N; i++) {
        fsi = f(S[i]);
        s = search(S[i]) + fsi;
        T[i] = max(fsi, s);
        g.set( -2*a*S[i] , S[i]*(a*S[i]-b) + T[i] );
        add(g);
    }
}

int main(void) {  
    N = read_int();
    cin >> a >> b >> c;      
    long long int *X = new long long int [N];      
    read_input(X);      
        
    long long int *Sums = new long long int [N];      
    find_sums(X, Sums);      
        
    long long int *Tastes = new long long int [N];      
    find_tastes(Sums, Tastes);      
        
    cout << Tastes[N-1] << endl;      
    
    delete[] X;  
    delete[] Sums;  
    delete[] Tastes;  
        
    return 0;      
} 