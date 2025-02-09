#include<bits/stdc++.h>
using namespace std;

// recursive O(2^n)
int fib (int n) {
    if (n==0 or n==1)
        return n;
    return fib(n-1) + fib(n-2);
}
// memoisation O(n)
int memo (int n, int* dp) {
    if (n==0 or n==1)
        return n;

    if (dp[n] != 0)
        return dp[n];

    return dp[n] = memo(n-1, dp) + memo(n-2, dp);
}
// tabulation O(n)
int tab(int n, int* dp) {
    dp[0] = 0;
    dp[1] = 1;

    for (int i=2; i<=n; i++)
        dp[i] = dp[i-1]+dp[i-2];

    return dp[n];
}

// no-memory dp
int no_memo(int n) {
    int prev = 0, curr = 1, next = 0;

    for (int i=0; i<n-1; i++) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }

    return next;
}

int main() {
    int n;
    cout << "Enter term: ";
    cin >> n;

    int dp[n+1] = {0};

    cout << n << "-th fibonacci: " << no_memo(n) << endl;

    return 0;
}
