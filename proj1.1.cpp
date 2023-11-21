#include <iostream>
#include <vector>
using namespace std;

struct Piece{
    int length;
    int width;
    int price;
};

// Recursive function that realizes the cut
int cut(Piece& piece, int X, int Y, vector<Piece>& pieces, size_t currIndx) {
    int a = piece.length;
    int b = piece.width;

    // Rotate the piece
    if ((a > X && b <= Y ) || (a <= X && b > Y)) {
            swap(a, b);
    }

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        if (currIndx + 1 < pieces.size()) {
            return cut(pieces[currIndx + 1], X, Y, pieces, currIndx + 1);
        } else {
            return 0;
        }
    }

    // The plate is equal to the piece
    else if (X == a && Y == b) {
        return piece.price;
    }

    // Case where the plate is cut vertically
    else if (X > a && Y == b) {
        return piece.price + cut(piece, X - a, Y, pieces, currIndx);
    }

    // Case where the plate is cut horizontally
    else if (Y > b && X == a) {
        return piece.price + cut(piece, X, Y - b, pieces, currIndx);
    } 

    else {
        return cut(piece, X - a, Y, pieces, currIndx) + cut(piece, a, Y, pieces, currIndx);
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
        int temp = cut(piece, X, Y, pieces, 0);
        if (temp > result) {
            result = temp;
        }
    }

    cout << result << endl;
    return 0;
}