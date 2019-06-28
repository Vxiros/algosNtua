#include <iostream>

using namespace std;

class Element {
public:
    int num;
    float time;

    Element() {}

    Element(int n, float t) {
        num = n;
        time = t;
    }
};

class Match {
public:
    int a, b;

    Match() {}

    Match(int num_a, int num_b) {
        a = num_a;
        b = num_b;
    }
};



int N, L, K;

void read_input(int* &ta, int* &tb, int* &ua, int* &ub) {
    for (int i=0; i<N; i++) {
        cin >> ta[i];
        cin >> ua[i];
    }
    for (int i=0; i<N; i++) {
        cin >> tb[i];
        cin >> ub[i];
    }
}

int main(void) {
    cin >> N;
    cin >> L;
    cin >> K;

    int *ta, *tb, *ua, *ub;
    ta = new int [N];   
    tb = new int [N];
    ua = new int [N];
    ub = new int [N];

    read_input(ta,tb,ua,ub);

    Element *first_a, *first_b;
    first_a = new Element [N];
    first_b = new Element [N];


    delete [] ta;
    delete [] tb;
    delete [] ua;
    delete [] ub;
    delete [] first_a;
    delete [] first_b;

    return 0;
}