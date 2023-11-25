#define max(a, b) (a > b ? a : b)

#include <iostream>
#include <vector>
using namespace std;

// Recursive function that realizes the cuts
int main(){
    int X, Y, n;

    cin >> X >> Y;  // Plate dimensions
    cin >> n;       // Types of pieces

    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for(int i = 1; i <= n; i++){
        int a, b, price;
        cin >> a >> b >> price;

        if (a <= X && b <= Y) {
            dp[a][b] = max(dp[a][b], price);
        }
        // Rotate 
        if (a <= Y && b <= X) {
            dp[b][a] = max(dp[b][a], price);
        }
    }

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            for (int k = 1; k <= i; k++) {
                // Cut vertically
                dp[i][j] = max(dp[i][j], dp[k][j] + dp[i - k][j]);
            }
            for (int k = 1; k <= j; k++) {
                // Cut horizontally
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[i][j - k]);
            }
        }
    }

    cout << dp[X][Y] << endl;
    return 0;
}