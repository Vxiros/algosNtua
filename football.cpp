#include <iostream> 
#include <list> 
#include <stack> 
using namespace std; 

long long int winners = 0;
  
class Graph { 
    int V;
    list<int> *adj;
  
    void fillOrder(int v, bool visited[], stack<int> &Stack); 
  
    void DFSUtil(int v, bool visited[]); 
public: 
    Graph(int V); 
    void addEdge(int v, int w); 
  
    void printWinners(); 
  
    Graph getTranspose(); 
}; 
  
Graph::Graph(int V) { 
    this->V = V; 
    adj = new list<int>[V]; 
} 
  
void Graph::DFSUtil(int v, bool visited[]) { 
    visited[v] = true; 
    winners++;
  
    list<int>::iterator i; 
    for (i = adj[v].begin(); i != adj[v].end(); ++i) 
        if (!visited[*i]) 
            DFSUtil(*i, visited); 
} 
  
Graph Graph::getTranspose() { 
    Graph g(V); 
    for (int v = 0; v < V; v++) { 
        list<int>::iterator i; 
        for(i = adj[v].begin(); i != adj[v].end(); ++i) { 
            g.adj[*i].push_back(v); 
        } 
    } 
    return g; 
} 
  
void Graph::addEdge(int v, int w) { 
    adj[v].push_back(w);
} 
  
void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) {  
    visited[v] = true; 
  
    list<int>::iterator i; 
    for(i = adj[v].begin(); i != adj[v].end(); ++i) 
        if(!visited[*i]) 
            fillOrder(*i, visited, Stack); 
  
    Stack.push(v); 
} 
  
void Graph::printWinners() { 
    stack<int> Stack; 
  
    bool *visited = new bool[V]; 
    for(int i = 0; i < V; i++) 
        visited[i] = false; 
  
    for(int i = 0; i < V; i++) 
        if(visited[i] == false) 
            fillOrder(i, visited, Stack); 
  
    Graph gr = getTranspose(); 
  
    for(int i = 0; i < V; i++) 
        visited[i] = false; 
  
    while (Stack.empty() == false) { 
        int v = Stack.top(); 
        Stack.pop(); 
   
        if (visited[v] == false) 
        { 
            gr.DFSUtil(v, visited); 
            cout << winners << endl; 
        } 
        break;
    } 
} 

/*int read_int() {
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
}*/

int main(void) {

    int N, lose_from, wins;
    //N = read_int();
    cin >> N;
    Graph G(N);

    for (int i=0; i<N; i++) {
        cin >> lose_from;
        for (int j=0; j<lose_from; j++) {
            //wins = read_int();
            cin >> wins;
            G.addEdge(wins-1, i);
        }
    }

    G.printWinners();

    return 0;
}