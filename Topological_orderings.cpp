#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Kahn's algorithm to check if graph is DAG

bool isDAG(int n, vector<vector<int>> &adj, vector<int> inDegree) {
    queue<int> q;

    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0)
            q.push(i);
    }

    int count = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        count++;

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return (count == n);
}

// Backtracking function using Kahn's logic

void allTopo(vector<vector<int>> &adj, vector<int> &inDegree, vector<bool> &visited, vector<int> &result, int n) {

    bool flag = false;

    for (int i = 0; i < n; i++) {
        if (!visited[i] && inDegree[i] == 0) {

            // choose
            visited[i] = true;
            result.push_back(i);

            for (int neighbor : adj[i]) {
                inDegree[neighbor]--;
            }

            // explore
            allTopo(adj, inDegree, visited, result, n);

            // backtrack
            visited[i] = false;
            result.pop_back();

            for (int neighbor : adj[i]) {
                inDegree[neighbor]++;
            }

            flag = true;
        }
    }
    
    // if no node chosen → one valid ordering

    if (!flag) {
        for (int x : result)
            cout << x << " ";
        cout << endl;
    }
}

int main() {
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> inDegree(n, 0);

    cout << "Enter directed edges (u v):\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        inDegree[v]++;
    }

    // Check if graph is DAG using Kahn's algorithm
    
    if (!isDAG(n, adj, inDegree)) {
        cout << "Graph has a cycle. No topological ordering exists.\n";
        return 0;
    }

    vector<bool> visited(n, false);
    vector<int> result;

    cout << "All Topological Orderings:\n";
    allTopo(adj, inDegree, visited, result, n);

    return 0;
}