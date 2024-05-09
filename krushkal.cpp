
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(vector<int>& a, vector<int>& b) {
    return a[2] < b[2];
}

void makeSet(vector<int>& parent, vector<int>& rank, int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(vector<int>& parent, int node) {
    if (parent[node] == node) {
        return node;
    }
    return parent[node] = findParent(parent, parent[node]);
}

void unionSet(int u, int v, vector<int>& parent, vector<int>& rank) {
    u = findParent(parent, u);
    v = findParent(parent, v);
    if (rank[u] > rank[v]) {
        parent[v] = u;
    } else if (rank[u] < rank[v]) {
        parent[u] = v;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

int minimumSpanningTree(vector<vector<int>>& edges, int n, vector<vector<int>>& mst) {
    sort(edges.begin(), edges.end(), cmp);
    vector<int> rank(n), parent(n);
    makeSet(parent, rank, n);
    
    int minWeight = 0;

    for (auto& edge : edges) {
        int u = findParent(parent, edge[0]);
        int v = findParent(parent, edge[1]);
        int wt = edge[2];

        if (u != v) {
            unionSet(u, v, parent, rank);
            minWeight += wt;
            mst.push_back({edge[0], edge[1], wt});
        }
    }

    return minWeight;
}

int main() {
    int n, e;
    cout << "Enter the number of nodes and edges: ";
    cin >> n >> e;
    vector<vector<int>> edges(e, vector<int>(3));

    cout << "Enter each edge as: node1 node2 weight\n";
    for (int i = 0; i < e; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    vector<vector<int>> mst;
    int totalWeight = minimumSpanningTree(edges, n, mst);

    cout << "Edges in the MST with their weights:\n";
    for (auto& edge : mst) {
        cout << edge[0] << " - " << edge[1] << " : " << edge[2] << "\n";
    }
    cout << "Total weight of MST: " << totalWeight << endl;
    return 0;
}
