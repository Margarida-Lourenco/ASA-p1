#include <iostream>
#include <vector>
using namespace std;

struct Piece{
    int length;
    int width;
    int price;
};

// Recursive function that realizes the cut
int cut(Piece& piece, int X, int Y, vector<Piece>& pieces, size_t currIndx, vector<int>& maxPrices) {

    // verifies if the index is within the range of maxPrices vector
    if (currIndx >= maxPrices.size()) {
        return 0;
    }
    
    int a = piece.length;
    int b = piece.width;

    // Rotate the piece
    if ((a > X && b <= Y ) || (a <= X && b > Y)) {
            swap(a, b);
    }

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        if (currIndx + 1 < pieces.size()) {
            return cut(pieces[currIndx + 1], X, Y, pieces, currIndx + 1, maxPrices);
        } else {
            return 0;
        }
    }

    // The plate is equal to the piece
    else if (X == a && Y == b) {
        maxPrices[currIndx] = piece.price;
        return piece.price;
    }

    // Case where the plate is cut vertically
    else if (X > a && Y == b) {
        maxPrices[currIndx] = piece.price + cut(piece, X - a, Y, pieces, currIndx, maxPrices);
        return maxPrices[currIndx];
    }

    // Case where the plate is cut horizontally
    else if (Y > b && X == a) {
        maxPrices[currIndx] = piece.price + cut(piece, X, Y - b, pieces, currIndx, maxPrices);
        return maxPrices[currIndx];
    } 

    else {
        maxPrices[currIndx] = max(cut(piece, X - a, Y, pieces, currIndx, maxPrices) + cut(piece, a, Y, pieces, currIndx, maxPrices),
                            cut(piece, X, Y - b, pieces, currIndx, maxPrices) + cut(piece, X, b, pieces, currIndx, maxPrices));
        return maxPrices[currIndx];
    }
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

    vector<int> maxPrices(n);

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
    
    for (Piece piece : pieces) {
        int temp = cut(piece, X, Y, pieces, 0, maxPrices);
        result = max(result, temp);
    }

    for (int i=0; i < (int) maxPrices.size(); i++){
        cout << maxPrices[i] << "\n";
    }

    cout << result << endl;
    return 0;
}