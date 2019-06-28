#include <iostream>

using namespace std;

class Element {
public:
    long long int height;
    int position;

    Element() {}
    
    Element(long long int h, int p) {
        height = h;
        position = p;
    }
};

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

int N;

void read_heights(long long int* &H) {
    for (int i=0; i<N; i++) {
        H[i] = read_int();
    }
}

void find_left_costs(long long int* &H, long long int* &costs) {
    Element *max_elems;
    max_elems = new Element [N];
    int max = H[0];
    costs[0] = H[0];
    Element elem(H[0],0);
    int ptr = 0;
    max_elems[0] = elem;
    for(int i=1; i<N; i++) {
        if (H[i]>=max) {
            max = H[i];
            costs[i]=H[i]*(i+1);
        }
        else if (H[i]<=H[i-1]) {
            costs[i] = costs[i-1] + H[i];
        }
        else {
            while((max_elems[ptr].height < H[i]) && (ptr>=0)) {
                ptr--;
            }
            costs[i] = costs[max_elems[ptr].position] + H[i]*(i - max_elems[ptr].position);

        }
        Element elem(H[i],i);
        ptr++;
        max_elems[ptr] = elem;
    }
}

void find_right_costs(long long int* &H, long long int* &costs) {
    Element *max_elems;
    max_elems = new Element [N];
    int max = H[N-1];
    costs[N-1] = H[N-1];
    Element elem(H[N-1],N-1);
    int ptr = 0;
    max_elems[0] = elem;
    for(int i=N-2; i>=0; i--) {
        if (H[i]>=max) {
            max = H[i];
            costs[i] = H[i]*(N-i);
        }
        else if (H[i]<=H[i-1]) {
            costs[i] = costs[i+1] + H[i];
        }
        else {
            while((max_elems[ptr].height < H[i]) && (ptr>=0)) {
                ptr--;
            }
            costs[i] = costs[max_elems[ptr].position] + H[i]*(max_elems[ptr].position-i);
        }
        Element elem(H[i],i);
        ptr++;
        max_elems[ptr] = elem;
    }
}

void find_costs(long long int* &H, long long int* &l, long long int* &r, long long int* &total_costs) {
    for (int i=0; i<N; i++) {
        total_costs[i] = l[i] + r[i] - H[i];
    }
}

long long int find_min(long long int* &costs) {
    long long int min = costs[0];
    for (int i=1; i<N; i++) {
        if (costs[i]<min) {
            min = costs[i];
        }
    }
    return min;
}

int main(void) {
    N = read_int();
    long long int *H;
    H = new long long int [N];
    read_heights(H);
     
    long long int  *left_costs,*right_costs;  
    left_costs = new long long int [N];  
    right_costs = new long long int [N]; 

    find_left_costs(H, left_costs);
    find_right_costs(H, right_costs);
    
    long long int *costs;
    costs = new long long int [N];  
    find_costs(H, left_costs, right_costs, costs);

    long long int min = find_min(costs);

    cout << min << endl;

    delete [] left_costs;
    delete [] right_costs;
    delete [] costs;

    return 0;
}