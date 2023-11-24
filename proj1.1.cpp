#define max(a, b) (a > b ? a : b)

#include <iostream>
#include <vector>
using namespace std;

// Recursive function that realizes the cut
int maxpriceCut(vector<vector<int>>& dp, int X, int Y) {

    //for (k = 0; k < size; k++) {
        for (int i = 0; i <= X; i++) {
            for (int j = 0; j <= Y ; j++) {
                dp[i][j] = max(dp[i][j], max(dp[X -i][j] + dp[i][j], dp[i][Y - j] + dp[i][j]));
            }
        }
    //}
    return dp[X][Y];
}

int main(){
    int X, Y, n;
    int result = 0;

    cin >> X >> Y;  // Plate dimensions
    cin >> n;       // Types of pieces

    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for(int i = 1; i <= n; i++){
        int a, b, price;
        cin >> a >> b >> price;
        if (a > X && b > Y){      // Piece is bigger than the plate
            continue;
        }

        //Piece newPiece = {a, b, price};
        if (dp[a][b] < price) {
            dp[a][b] = price;
        }
        if (dp[b][a] < price) {
            dp[b][a] = price;
        }
    }

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y ; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    result = maxpriceCut(dp, Y, X);

    cout << result << endl;
    return 0;
}