#include <iostream>
#include <vector>
using namespace std;

struct Piece{
    int lenght;
    int width;
    int price;
};

// Recursive function that realizes the cut
int cut(Piece piece, int X, int Y, vector <Piece> pieces);


// Function that verifies if there is a piece that can be cut
int verify_pieces(vector <Piece> pieces, int X, int Y){
    int i = 1;

    while (i < (int) pieces.size()){
        if (pieces[i].lenght < X || pieces[i].width < Y){
            return cut(pieces[i], X, Y, pieces);
        }
        i++;
    }
    
    return 0;
}


int cut(Piece piece, int X, int Y, vector <Piece> pieces){
    int a = piece.lenght;
    int b = piece.width;

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        return verify_pieces(pieces, X, Y);
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

void insertSorted(std::vector<Piece>& pieces, Piece& newPiece) {
    int position = 0;

    // Find the correct position for insertion
    while (position < (int) pieces.size() && newPiece.price < pieces[position].price) {
        position++;
    }

    pieces.insert(pieces.begin() + position, newPiece);
}

int main(){
    int X, Y, n;
    int result = 0;

    vector <Piece> pieces;

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

    for (int i = 0; i < (int) pieces.size(); i++){
        int temp = cut(pieces[i], X, Y, pieces);
        if (temp > result){
            result = temp;
        }
    }

    cout << result << endl;
    return 0;
}



