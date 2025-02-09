#include<bits/stdc++.h>
using namespace std;

int main() {

    int n;
    cout << "Enter no. of vertices: ";
    cin >> n;

    int graph[n][n];

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            graph[i][j] = 10000;
        }
    }

    int e;
    cout << "Enter no. of edges: ";
    cin >> e;

    while (e--) {
        int source, destination, weight;
        cout << "Enter source vertex: ";
        cin >> source;
        cout << "Enter destination vertex: ";
        cin >> destination;
        cout << "Enter weight: ";
        cin >> weight;
        graph[source][destination] = weight;
    }

    for (int k=0; k<n; k++) { // for every intermediate vertex k
        for (int i=0; i<n; i++) { // for every source i
            for (int j=0; j<n; j++) { // to every destination j
                graph[i][j] = min(graph[i][j], graph[i][k]+graph[k][j]);
            }
        }
    }

    // print the solution
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
