#include <iostream>
#include <list>
using namespace std;

struct Piece{
    int length;
    int width;
    int price;
};

// Recursive function that realizes the cut
int cut(Piece& piece, int X, int Y, list<Piece>& pieces, list<Piece>::iterator iter) {
    int a = piece.length;
    int b = piece.width;

    // Rotate the piece
    if ((a > X && b <= Y ) || (a <= X && b > Y)) {
            swap(a, b);
    } 

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        list<Piece>::iterator nextIter = std::next(iter);
        if (nextIter != pieces.end()) {
            return cut(*nextIter, X, Y, pieces, nextIter);
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
        return piece.price + cut(piece, X - a, Y, pieces, iter);
    }

    // Case where the plate is cut horizontally
    else if (Y > b && X == a) {
        return piece.price + cut(piece, X, Y - b, pieces, iter);
    } 

    else {
        return cut(piece, X - a, Y, pieces, iter) + cut(piece, a, Y, pieces, iter);
    }
}

void insertSorted(list<Piece>& pieces, Piece& newPiece) {
    list<Piece>::iterator iter = pieces.begin();

    // Find the correct position for insertion
    while (iter != pieces.end() && newPiece.price <= iter->price) {
        ++iter;
    }

    pieces.insert(iter, newPiece);
}

int main(){
    int X, Y, n;
    int result = 0;

    list <Piece> pieces;

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
        int temp = cut(piece, X, Y, pieces, pieces.begin());
        if (temp > result) {
            result = temp;
        }
    }

    cout << result << endl;
    return 0;
}



