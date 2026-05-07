#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int prims(int n, vector<vector<pair<int,int>>> &adj) {
    vector<bool> visited(n, false);

    // min-heap: {weight, node}
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;

    int start;
    cout << "Enter starting node: ";
    cin >> start;

    pq.push({0, start});   // {weight, node}

    int totalWeight = 0;

    while (!pq.empty()) {

        int weight = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (visited[node]) continue;

        visited[node] = true;
        cout << node << " ";

        totalWeight += weight;

        for (auto neighbor : adj[node]) {

            int nextWeight = neighbor.first;
            int nextNode = neighbor.second;

            if (!visited[nextNode]) {
                pq.push({nextWeight, nextNode});
            }
        }
    }

    return totalWeight;
}

int main() {

    int n, m;

    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    // pair = {weight, node}
    vector<vector<pair<int,int>>> adj(n);

    cout << "Enter edges (u v weight):\n";

    for (int i = 0; i < m; i++) {

        int u, v, w;
        cin >> u >> v >> w;

        adj[u].push_back({w, v});
        adj[v].push_back({w, u});   // undirected graph
    }

    int mstWeight = prims(n, adj);

    cout << "\nTotal weight of MST: " << mstWeight << endl;

    return 0;
}