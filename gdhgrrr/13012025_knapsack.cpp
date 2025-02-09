#include<bits/stdc++.h>
using namespace std;

int knapsack(int capacity, vector<int>& weights, vector<int>& profits, int n) {
    vector<vector<int> > dp(n+1, vector<int>(capacity+1, 0));

    for (int i=1; i<=n; i++) {
        for (int w=1; w<=capacity; w++) {
            if (weights[i-1] <= w)
                dp[i][w] = max(dp[i-1][w], dp[i-1][w-weights[i-1]]
                               +profits[i-1]);
            else
                dp[i][w] = max(dp[i-1][w], dp[i][w-1]);
        }
    }

    for (int i=0; i<=n; i++) {
        for (int w=0; w<=capacity; w++) {
            cout << dp[i][w] << " ";
        }
        cout << endl;
    }

    return dp[n][capacity];
}

int main() {

    int n;
    cout << "Enter no. of items: ";
    cin >> n;

    int capacity;
    cout << "Enter capacity: ";
    cin >> capacity;

    vector<int> weights(n), profits(n);

    for (int i=0; i<n; i++) {
        cout << "Enter item " << i+1 << " profit: ";
        cin >> profits[i];
        cout << "Enter item " << i+1 << " weight: ";
        cin >> weights[i];
    }

    int res = knapsack(capacity, weights, profits, n);

    cout << "Maximum profit: " << res << endl;

    return 0;
}
