#define max(a, b) (a > b ? a : b)

#include <stdio.h>
#include <vector>
using namespace std;

int main(){
    int X, Y, n;

    if (scanf("%d %d\n%d", &X , &Y, &n) != 3)   // Plate dimensions and number of pieces
        return 1;                               

    vector<int> dp((X + 1)*(Y + 1), 0);

    for(int i = 1; i <= n; i++){
        int a, b, price;

        if(scanf("%d %d %d", &a , &b, &price) != 3)  // Piece dimensions and price
            return 1;  

        if (a <= X && b <= Y) {
            dp[a + X * b] = max(dp[a + X * b], price);
        }
        
        // Rotate 
        if (a <= Y && b <= X) {
            dp[b + X * a] = max(dp[b + X * a], price);
        }
    }

    for (int i = 1; i <= X; i++) {
        for (int j = 1; j <= Y; j++) {
            for (int k = 1; k <= i/2; k++) {
                // Cut vertically
                dp[i + X * j] = max(dp[i + X * j], dp[k + X * j] + dp[(i - k) + X * j]);
            }
            for (int k = 1; k <= j/2; k++) {
                // Cut horizontally
                dp[i + X * j] = max(dp[i + X * j], dp[i + X * k] + dp[i + X * (j - k)]);
            }
        }
    }

    printf("%d\n", dp[X + X * Y]);
    return 0;
}