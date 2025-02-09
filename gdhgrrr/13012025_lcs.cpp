#include<bits/stdc++.h>
using namespace std;

// recursive
int LCS(string& s1, int i, string& s2, int j) { // reference
    if (i == s1.length() or j == s2.length())
        return 0;

    if (s1[i] == s2[j])
        return 1 + LCS(s1, i+1, s2, j+1);

    return max(LCS(s1, i+1, s2, j), LCS(s1, i, s2, j+1));

}

// memoisation
int LCS_memo(string& s1, int i, string& s2, int j, vector<vector<int> >& dp, string& ans) {
    if (i == s1.length() or j == s2.length())
        return 0;

    if (dp[i][j] != 0)
        return dp[i][j];

    if (s1[i] == s2[j]) {
        ans += s2[j];
        dp[i][j] = 1 + LCS_memo(s1, i+1, s2, j+1, dp, ans);
    }
    else {
        dp[i][j] = max(LCS_memo(s1, i+1, s2, j, dp, ans), LCS_memo(s1, i, s2, j+1, dp, ans));
    }

    return dp[i][j];
}

int LCS_tab(string& s1, int n, string& s2, int m, vector<vector<int> >& dp) {
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (s1[i-1] == s2[j-1])
                dp[i][j] = 1 + dp[i-1][j-1];
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    return dp[n][m];
}

int main() {

    string s2 = "abcdefghi";
    string s1 = "bdcgi";

    int n = s1.length(), m = s2.length();

    string ans = "";

    vector<vector<int> > dp(n+1, vector<int>(m+1, 0));

    cout << "LCS Length: " << LCS_tab(s1, n, s2, m, dp) << endl;
    //reverse(ans.begin(), ans.end());
    cout << "Subsequence: " << ans << endl;

    return 0;
}
