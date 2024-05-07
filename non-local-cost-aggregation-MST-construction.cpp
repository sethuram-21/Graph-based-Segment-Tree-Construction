#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define edge pair<int, int>

class Graph {
    private:
    vector<pair<int, edge> > G;  
    vector<pair<int, edge> > T;  
    int *parent;
    int V; 
    public:
    Graph(int V);
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};

Graph::Graph(int V) {

    parent = new int[V];

    for (int i = 0; i < V; i++)
        parent[i] = i;

    G.clear();
    T.clear();
}

void Graph::AddWeightedEdge(int u, int v, int w) {
    G.push_back(make_pair(w, edge(u, v)));
}

int Graph::find_set(int i) {
  // If i is the parent of itself
    if (i == parent[i])
        return i;
    else
    // Else if i is not the parent of itself
    // Then i is not the representative of his set,
    // so we recursively call Find on its parent
        return find_set(parent[i]);
}

void Graph::union_set(int u, int v) {
    parent[u] = parent[v];
}

void Graph::kruskal() {
    int i, uRep, vRep;
    sort(G.begin(), G.end());  
    for (i = 0; i < G.size(); i++) {
        uRep = find_set(G[i].second.first);
        vRep = find_set(G[i].second.second);
        if (uRep != vRep) {
            T.push_back(G[i]); 
            union_set(uRep, vRep);
        }
    }
}

void Graph::print() {
    cout << "Edge :"<< " Weight" << endl;

    for (int i = 0; i < T.size(); i++) {
        cout << T[i].second.first << " - " << T[i].second.second << " : "<< T[i].first;
        cout << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    Graph graph(n);

    cout << "Enter edges (source destination weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.AddWeightedEdge(u, v, weight);
    }
    clock_t start,end;
    start = clock();

    graph.kruskal();

    end = clock();
    graph.print();

    cout<<"time taken : "<<(float)start-end/CLOCKS_PER_SEC<<" Cycles per sec"<<endl;
    return 0;
}