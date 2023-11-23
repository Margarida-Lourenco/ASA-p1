#include <iostream>
#include <vector>
using namespace std;

struct Piece{
    int length;
    int width;
    int price;
};

#define max(a, b) (a > b ? a : b)

// Recursive function that realizes the cut
int maxpriceCut(vector<Piece>& pieces, int X, int Y) {
    vector<vector<int>> dp(X + 1, vector<int>(Y + 1, 0));

    for (Piece& piece : pieces) {
        for (int i = piece.length; i <= X; i++) {
            for (int j = piece.width; j <= Y; j++) {
                dp[i][j] = max(dp[i][j], max(dp[i - piece.length][j] + piece.price, dp[i][j - piece.width] + piece.price));
            }
        }

        // Rotate the piece
        swap(piece.length, piece.width);

        for (int i = piece.length; i <= X; i++) {
            for (int j = piece.width; j <= Y; j++) {
                dp[i][j] = max(dp[i][j], max(dp[i - piece.length][j] + piece.price, dp[i][j - piece.width] + piece.price));
            }
        }
    }

    return dp[X][Y];
}

void insertSorted(vector<Piece>& pieces, Piece& newPiece) {
    size_t position = 0;

    // Find the correct position for insertion
    while (position < pieces.size()) {
        if (newPiece.price > pieces[position].price) {
            break;
        }
        position++;
    }

    pieces.insert(pieces.begin() + position, newPiece);
}


int main(){
    int X, Y, n;
    int result = 0;

    vector<Piece> pieces;

    cin >> X >> Y;  // Plate dimensions
    cin >> n;       // Types of pieces

    for(int i = 1; i <= n; i++){
        int a, b, price;
        cin >> a >> b >> price;
        if (a > X && b > Y){      // Piece is bigger than the plate
            continue;
        }

        // Swap the dimensions to rotate the piece
        if ((a > X && b <= Y ) || (a <= X && b > Y)) {
            swap(a, b);
        }
        Piece newPiece = {a, b, price};
        insertSorted(pieces, newPiece);
    }

    result = maxpriceCut(pieces, Y, X);

    cout << result << endl;
    return 0;
}