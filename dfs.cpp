#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int start, vector<vector<int>> &adj, vector<bool> &visited) {
    stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";

            // push neighbors in reverse order
            for (int i = adj[node].size() - 1; i >= 0; i--) {
                int neighbor = adj[node][i];
                if (!visited[neighbor]) {
                    st.push(neighbor);
                }
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
        adj[v].push_back(u);   // undirected graph
    }

    vector<bool> visited(n, false);

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    cout << "DFS Traversal (Iterative): ";

    dfs(start, adj, visited);

    // disconnected components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i, adj, visited);
        }
    }

    return 0;
}