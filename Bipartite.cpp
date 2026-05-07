#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool bfs(int start, vector<vector<int>> &adj, vector<int> &color) {
    queue<int> q;

    color[start] = 0;                                   // start with color 0
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor : adj[node]) {
            // If not colored
            if (color[neighbor] == -1) {
                color[neighbor] = 1 - color[node]; // assign opposite color
                q.push(neighbor);
            }
            else if (color[neighbor] == color[node]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n);

    cout << "Enter edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);   // undirected graph
    }

    vector<int> color(n, -1); // -1 means not colored

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            if (!bfs(i, adj, color)) {
                cout << "Graph is NOT Bipartite\n";
                return 0;
            }
        }
    }

    cout << "Graph is Bipartite\n";
    return 0;
}