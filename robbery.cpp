#include <iostream>    
#include <queue>    
#include <vector>    
    
using namespace std;    
    
class Edge {    
public:    
    int num_edge, verticle1, verticle2, weight;    
    
    Edge() {}    
    
    void set(int n, int v1, int v2, int w) {  
        num_edge = n;  
        verticle1 = v1;    
        verticle2 = v2;    
        weight = w;    
    }    
};    
    
void Merge(Edge* &a, int low, int high, int mid)    
{    
    int i, j, k;    
    Edge temp[high-low+1];    
    i = low;    
    k = 0;    
    j = mid + 1;    
    
    while (i <= mid && j <= high) {    
        if (a[i].weight < a[j].weight) {    
            temp[k] = a[i];    
            k++;    
            i++;    
        }    
        else {    
            temp[k] = a[j];    
            k++;    
            j++;    
        }    
    }    
    
    while (i <= mid) {    
        temp[k] = a[i];    
        k++;    
        i++;    
    }    
    
    while (j <= high) {    
        temp[k] = a[j];    
        k++;    
        j++;    
    }    
    
    for (i = low; i <= high; i++) {    
        a[i] = temp[i-low];    
    }    
}    
    
void MergeSort(Edge* &a, int low, int high)    
{    
    int mid;    
    if (low < high)    
    {    
        mid=(low+high)/2;    
        MergeSort(a, low, mid);    
        MergeSort(a, mid+1, high);    
    
        Merge(a, low, high, mid);    
    }    
}    
    
class Set {    
public:    
    int num_set, num_vertices;    
    queue <int> vertices;    
    
    Set() {}    
    
    void init(int v) {    
        num_set = v;    
        num_vertices = 1;    
        vertices.push(v);    
    }    
    
    void add(Set s, int* &Vsets) {    
        int v;    
        queue <int> ver = s.vertices;    
    
        num_vertices += s.num_vertices;    
    
        while(!ver.empty()) {    
            v = ver.front();    
            ver.pop();    
            vertices.push(v);    
            Vsets[v] = num_set;    
        }    
    }    
};    
    
class same_weight {    
public:  
    int num_edge;    
    bool essential;    
    
    same_weight() {}    
    
    void init(int n) {  
        num_edge = n;  
        essential = true;    
    }  
    
    void not_ess() {    
        essential = false;    
    }    
};  
  
class int_pair {  
public:  
    int edge, verticle;  
  
    int_pair() {}  
  
    void set(int e, int v) {  
        edge = e;  
        verticle = v;  
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
  
bool find_cycle_edges(int source, int destination, queue<int_pair>* &Paths, bool* &F, queue<int> *q, int forbidden) {  
    queue<int_pair> p = Paths[source];  
    int_pair ev;  
    bool found;  
    while(!p.empty()) {  
        ev = p.front();  
        if (ev.verticle != forbidden) {  
            if (ev.verticle == destination) {  
                F[ev.edge] = true;  
                q->push(ev.edge);  
                return true;  
            }  
  
            found = find_cycle_edges(ev.verticle, destination, Paths, F, q, source);  
            if (found) {  
                F[ev.edge] = true;  
                q->push(ev.edge);  
                return true;  
            }  
        }  
        p.pop();  
    }  
    return false;  
}  
    
void add_edge(Edge edge, int* &Vsets, Set* &Sets, queue<int_pair>* &Paths) {    
    int set1 = Vsets[edge.verticle1];    
    int set2 = Vsets[edge.verticle2];    
    if (Sets[set1].num_vertices > Sets[set2].num_vertices) {    
        Sets[set1].add(Sets[set2], Vsets);    
    }    
    else {    
        Sets[set2].add(Sets[set1], Vsets);    
    }   
  
    int a, b;  
    int_pair ip;    
  
    ip.set(edge.num_edge,edge.verticle2);  
    Paths[edge.verticle1].push(ip);  
  
    ip.set(edge.num_edge,edge.verticle1);  
    Paths[edge.verticle2].push(ip);  
}    
    
int main(void) {  
    int N, M, ALWAYS = 0, SOMETIMES = 0, NEVER;    
    N = read_int();  
    M = read_int();
    
    int* Vsets = new int [N+1];    
    Set* Sets = new Set [N+1];    
    for(int i=1; i<=N; i++) {    
        Vsets[i] = i;    
        Sets[i].init(i);    
    }    
    
    Edge* Edges = new Edge [M];    
    int a_e, b_e, c_e;    
    for(int i=0; i<M; i++) {
        a_e = read_int();
        b_e = read_int();  
        c_e = read_int();   
        Edges[i].set(i, a_e, b_e, c_e);    
    }  
  
  
    MergeSort(Edges, 0, M-1);   
  
  
    queue<int_pair> *Paths = new queue<int_pair> [N+1];  
    bool *EdgesFound = new bool [M];  
    for (int i=0; i<M; i++) {  
        EdgesFound[i] = false;  
    }  
    queue<int> edge_q;  
    
    add_edge(Edges[0], Vsets, Sets, Paths);    
    int e = 0, edges = 1, prev_w = Edges[0].weight;    
    vector<same_weight> *same_weights = new vector<same_weight> [N];  
    int index = 0;    
    same_weight s;    
    s.init(Edges[0].num_edge);    
    same_weights[0].push_back(s);    
    ALWAYS++;    
  
    Edge edge;    
    bool found;  
    while(true) {    
        if (e == M-1) break;    
        e++;    
        edge = Edges[e];    
        if (Vsets[edge.verticle1] == Vsets[edge.verticle2]) {    
            if(edge.weight == prev_w) {  
  
                while(!edge_q.empty()) {  
                    EdgesFound[edge_q.front()] = false;  
                    edge_q.pop();  
                }  
  
                found = find_cycle_edges(edge.verticle1, edge.verticle2, Paths, EdgesFound, &edge_q, -1);  
  
                if(found) {  
                    found = false;  
                    for(int i=0; i<same_weights[index].size(); i++) {  
                        if(EdgesFound[same_weights[index][i].num_edge]) {  
                            found = true;  
                            if(same_weights[index][i].essential) {  
                                ALWAYS--;    
                                SOMETIMES++;    
                                same_weights[index][i].not_ess();  
                            }  
                        }  
                    }  
                    if(found) SOMETIMES++;   
                }    
            }    
            else {    
                prev_w = edge.weight;    
                index++;    
                if (edges == N-1) break;    
            }    
        }    
        else {  
            add_edge(edge, Vsets, Sets, Paths);  
            edges++;    
            ALWAYS++;    
            if(edge.weight != prev_w) {    
                prev_w = edge.weight;    
                index++;    
            }    
            s.init(edge.num_edge);    
            same_weights[index].push_back(s);    
        }    
    }    
    
    NEVER = M - ALWAYS - SOMETIMES;  
    
    cout << ALWAYS << endl << NEVER << endl << SOMETIMES << endl;    
    
    return 0;    
}