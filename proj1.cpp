#include <iostream>
#include <vector>
using namespace std;

struct Piece{
    int lenght;
    int width;
    int price;
};

// Recursion that realizes the cut
int cut(Piece piece, int X, int Y){
    int a = piece.lenght;
    int b = piece.width;

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        return 0;
    }

    // The plate is equal to the piece
    else if (X == a && Y == b) {
        return 1;
    }

    // Case where the plate is cut vertically
    else if (X > a && Y == b) {
        return 1 + cut(piece, X - a, Y);
    }

    // Case where the plate is cut horizontally
    else if (Y > b && X == a) {
        return 1 + cut(piece, X, Y - b);
    } 

    else {
        return cut(piece, X - a, Y) + cut(piece, a, Y);
    }
}

int main(){
    int X, Y;
    int n;

    // results[0] = price of the piece, results[1] = Total price
    vector<int> results(2,0); 

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
        int temp = cut(newPiece, X, Y);
        temp *= newPiece.price;

        // Update the results
        if (results[1] < temp) {
            results[0] = newPiece.price;
            results[1] = temp;

        } else if (results[1] == temp) {
            results[0] = max(results[0], newPiece.price);
        }
    }

    cout << results[1] << endl;
    return 0;
}



