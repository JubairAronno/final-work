#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int source, destination, weight;
};

void bellmanFord (int n, int source, vector<Edge>& edgeList) {
    vector<int>dist(n, INT_MAX); // store distance to each vertex
    dist[source] = 0; // distance to source is zero

    for (int i=0; i<n-1; i++) { // relax (n-1) times
        for (Edge edge:edgeList) { // for every edge in the edge list
            int u = edge.source;
            int v = edge.destination;
            int w = edge.weight;

            if (dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (Edge edge:edgeList) { // check one more time
        int u = edge.source;
        int v = edge.destination;
        int w = edge.weight;

        if (dist[u] + w < dist[v]) { // if it can still be relaxed, then negative cycle found
            cout << "Negative cycle found! Solution not possible!";
            return;
        }
    }

    // print the solution
    for (int i=0; i<n; i++)
        cout << "Shortest path from vertex " << source <<
        " to " << i << ": " << dist[i] << endl;
}

int main() {
    int n;
    cout << "Enter no. of vertices: ";
    cin >> n;

    int e;
    cout << "Enter no. of edges: ";
    cin >> e;

    vector<Edge> edgeList;

    while (e--) {
        Edge E;
        cout << "Enter source vertex: ";
        cin >> E.source;
        cout << "Enter destination vertex: ";
        cin >> E.destination;
        cout << "Enter weight: ";
        cin >> E.weight;
        edgeList.push_back(E);
    }

    bellmanFord(n, 0, edgeList);

    return 0;
}
