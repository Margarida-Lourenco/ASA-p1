#include <iostream>
#include <vector>
using namespace std;

struct Piece{
    int lenght;
    int width;
    int price;
};

// Recursive function that realizes the cut

int search_position(vector<Piece>& pieces, int X, int Y) {
    int position = 0;

    // Find the correct position for insertion
    while (position < (int) pieces.size()) {
        if (pieces[position].lenght < X || pieces[position].width < Y) {
            break;
        }
        position++;
    }
    return position;
}

int cut(Piece& piece, int X, int Y, vector<Piece>& pieces){
    int a = piece.lenght;
    int b = piece.width;

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        int position = search_position(pieces, X, Y);
        if (position == 0)
            return 0;
        else
            return cut(pieces[position], X, Y, pieces);
    }

    // The plate is equal to the piece
    else if (X == a && Y == b) {
        return piece.price;
    }

    // Case where the plate is cut vertically
    else if (X > a && Y == b) {
        return piece.price + cut(piece, X - a, Y, pieces);
    }

    // Case where the plate is cut horizontally
    else if (Y > b && X == a) {
        return piece.price + cut(piece, X, Y - b, pieces);
    } 

    else {
        return cut(piece, X - a, Y, pieces) + cut(piece, a, Y, pieces);
    }
}

void insertSorted(vector<Piece>& pieces, Piece& newPiece) {
    int position = 0;

    // Find the correct position for insertion
    while (position < (int) pieces.size()) {
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
        int temp = cut(piece, X, Y, pieces);
        if (temp > result) {
            result = temp;
        }
    }

    cout << result << endl;
    return 0;
}