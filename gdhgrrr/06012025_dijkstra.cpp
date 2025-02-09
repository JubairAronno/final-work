#include<bits/stdc++.h>
using namespace std;

class Graph {
    int V; // no. of vertices
    vector<vector<pair<int, int> > > graph; // adj. list
public:
    Graph(int V) {
        this->V = V;
        graph.resize(V);
    }
    void addEdge(int src, int wgt, int dst, bool undir = true) {
        graph[src].push_back({wgt, dst});
        if (undir)
            graph[dst].push_back({wgt, src});
    }
    void dijkstra(int source) {
        vector<int> dist(V, INT_MAX);
        set<pair<int, int> > s;

        dist[source] = 0;
        s.insert({0, source});

        while (!s.empty()) {
            auto it = s.begin();
            int vertex = it->second;
            int distTillNow = it->first;

            s.erase(it);

            for (auto nbrPair:graph[vertex]) {
                int nbrVertex = nbrPair.second;
                int currentEdge = nbrPair.first;

                if (distTillNow+currentEdge < dist[nbrVertex]) {
                    auto f = s.find({dist[nbrVertex], nbrVertex});

                    if (f!=s.end())
                        s.erase(f);

                    dist[nbrVertex] = distTillNow + currentEdge;
                    s.insert({dist[nbrVertex], nbrVertex});
                }

            }
        }

        for (int i=0; i<V; i++)
            cout << "Shortest path from " << source << " to " << i << ": " << dist[i] << endl;
    }


};

int main() {

    Graph g(5);

    g.addEdge(0,1,1);
    g.addEdge(0,4,2);
    g.addEdge(0,7,3);
    g.addEdge(1,1,2);
    g.addEdge(2,2,3);
    g.addEdge(3,3,4);

    g.dijkstra(0);

    return 0;
}
