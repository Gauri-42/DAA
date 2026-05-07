#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void bfs(int start, vector<vector<int>> &adj, vector<bool> &visited) {
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
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
        adj[v].push_back(u);         // Graph is undirected
    }

    vector<bool> visited(n, false);

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    cout << "BFS Traversal: ";

    bfs(start, adj, visited);

    // For disconnected components 
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            bfs(i, adj, visited);
        }
    }

    return 0;
}