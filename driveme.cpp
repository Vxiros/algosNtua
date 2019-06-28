#include<bits/stdc++.h>   
using namespace std;   
# define INF 0x3f3f3f3f   
    
int N, M, K, Q;  
long long int dist[101][1101];  
  
int readint() {  
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
  
class Graph   
{   
    int V;   
    vector< pair<int, int> > *adj;   
    
public:   
    Graph(int V);    
    void addEdge(int u, int v, int w);   
     
    void shortestPath(int s);   
};   
    
Graph::Graph(int V)   
{   
    this->V = V;   
    adj = new vector< pair<int,int> > [V];  
}   
    
void Graph::addEdge(int u, int v, int w)   
{   
    adj[u].push_back(make_pair(v, w));   
}   
    
void Graph::shortestPath(int src)  
{  
    priority_queue< pair<int, int>, vector < pair<int,int> > , greater< pair<int,int> > > pq;  
    pq.push(make_pair(0, src));  
    for(int i=0; i<(K+1)*N; i++) {  
        dist[src][i] = INF;  
    }  
    dist[src][src] = 0;  
    while (!pq.empty())  
    {  
        int u = pq.top().second;  
        pq.pop();  
        for (auto i = adj[u].cbegin(); i != adj[u].cend(); ++i)  
        {  
            int v = (*i).first;  
            int weight = (*i).second;  
            if (dist[src][v] > dist[src][u] + weight)  
            {  
                dist[src][v] = dist[src][u] + weight;  
                pq.push(make_pair(dist[src][v], v));  
            }  
        }  
    }  
}  
  
int to_idx(int i, int p) {  
    return (N*p+i);  
}  
  
int find_min_dist(int s, int d, int p) {  
    int dj = dist[s][d];  
    int j;  
    for (int i=1; i<=p; i++) {  
        j = to_idx(d,i);  
        if(dj>dist[s][j]) {  
            dj = dist[s][j];  
        }  
    }  
    return dj;  
}  
  
int main(void) {  
    N = readint();  
    M = readint();  
    K = readint();  
    Q = readint();  
  
    Graph G(N*(K+1));  
  
    int src, dst, d, src_j, dst_j, src_j1;  
  
    for (int i=0; i<M; i++) {  
        src = readint();  
        dst = readint();  
        d = readint();  
        for (int j=0; j<=K; j++) {  
            src_j = to_idx(src-1, j);  
            dst_j = to_idx(dst-1, j);  
  
            G.addEdge(src_j, dst_j, d);  
  
            if(j!=K) {  
                src_j1 = to_idx(src-1, j+1);  
                G.addEdge(dst_j, src_j1, d);  
            }  
        }  
    }  
  
    int p, min_dist;  
  
    for (int i=0; i<Q; i++) {  
        cin >> src >> dst >> p;  
        G.shortestPath(src-1);  
        min_dist = find_min_dist(src-1, dst-1, p);  
        if (min_dist == INF) {  
            cout << "IMPOSSIBLE" << endl;  
        }  
        else {  
            cout << min_dist << endl;  
        }  
    }  
    return 0;  
  
}  