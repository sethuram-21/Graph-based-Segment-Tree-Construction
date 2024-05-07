#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
};

struct Node {
    int parent;
    int rank;
};

class Graph {
private:
    vector<Node> nodes;
    vector<Edge> edges;

    int find(int u) {
        if (nodes[u].parent != u)
            nodes[u].parent = find(nodes[u].parent);
        return nodes[u].parent;
    }

    void unionSets(int u, int v) {
        int uRoot = find(u);
        int vRoot = find(v);

        if (nodes[uRoot].rank < nodes[vRoot].rank)
            nodes[uRoot].parent = vRoot;
        else if (nodes[uRoot].rank > nodes[vRoot].rank)
            nodes[vRoot].parent = uRoot;
        else {
            nodes[vRoot].parent = uRoot;
            nodes[uRoot].rank++;
        }
    }

public:
    Graph(int n) {
        nodes.resize(n);
        edges.clear();
        for (int i = 0; i < n; ++i) {
            nodes[i].parent = i;
            nodes[i].rank = 1;
        }
    }

    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    bool compareEdges(Edge a, Edge b) {
        return a.weight < b.weight;
    }

    vector<Edge> segmentTree(int k,int n) {
        sort(edges.begin(), edges.end(), [&](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        vector<Edge> result;
        for (const Edge& edge : edges) {
            int uRoot = find(edge.u);
            int vRoot = find(edge.v);
            if (uRoot != vRoot && satisfiesCondition(edge, k)) {
                result.push_back(edge);
                unionSets(uRoot, vRoot);
            }
        }

        for (const Edge& edge : edges) {
            int uRoot = find(edge.u);
            int vRoot = find(edge.v);
            if (uRoot != vRoot) {
                result.push_back(edge);
                unionSets(uRoot, vRoot);
            }
            if(result.size() == n-1)
            {
                break;
            }
        }


        return result;
    }

    bool satisfiesCondition(Edge edge, int k) {
        int uRoot = find(edge.u);
        int vRoot = find(edge.v);
        int maxWeightU = edge.weight, maxWeightV = edge.weight;
        for (const Edge& e : edges) {
            if (find(e.u) == uRoot && e.weight > maxWeightU)
                maxWeightU = e.weight;
            if (find(e.v) == vRoot && e.weight > maxWeightV)
                maxWeightV = e.weight;
        }
        return edge.weight <= min(maxWeightU + k / nodes[uRoot].rank, maxWeightV + k / nodes[vRoot].rank);
    }
};

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    Graph graph(n);

    cout << "Enter edges (source destination weight):" << endl;
    for (int i = 0; i < m; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    int k = 1200; // constant parameter

    clock_t start,end;
    start = clock();
    vector<Edge> segmentTree = graph.segmentTree(k,n);
    end = clock();

    cout << "Edges in the segment tree:" << endl;
    for (const Edge& edge : segmentTree) {
        cout << edge.u << " " << edge.v << " " << edge.weight << endl;
    }

    cout<<"time taken : "<<(float)end-start/CLOCKS_PER_SEC<<" Cycles per sec"<<endl;

    return 0;
}
