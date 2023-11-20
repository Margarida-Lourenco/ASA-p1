#include <iostream>
#include <list>
using namespace std;

struct Piece{
    int lenght;
    int width;
    int price;
};

// Recursive function that realizes the cut


#include <iostream>
#include <list>

int cut(const Piece& piece, int X, int Y, list<Piece>& pieces, list<Piece>::iterator iter) {
    int a = piece.lenght;
    int b = piece.width;

    // A placa é menor que a peça
    if (X < a || Y < b) {
        auto nextIter = std::next(iter);
        if (nextIter != pieces.end()) {
            // Chamar a função recursivamente para a próxima peça
            return cut(*nextIter, X, Y, pieces, nextIter);
        } else {
            return 0;  // Se não houver próxima peça, retorne 0 ou o valor desejado
        }
    }

    // A placa é igual à peça
    else if (X == a && Y == b) {
        return piece.price;
    }

    // Caso em que a placa é cortada verticalmente
    else if (X > a && Y == b) {
        return piece.price + cut(piece, X - a, Y, pieces, iter);
    }

    // Caso em que a placa é cortada horizontalmente
    else if (Y > b && X == a) {
        return piece.price + cut(piece, X, Y - b, pieces, iter);
    } 

    else {
        return cut(piece, X - a, Y, pieces, iter) + cut(piece, a, Y, pieces, iter);
    }
}

void insertSorted(list<Piece>& pieces, const Piece& newPiece) {
    list<Piece>::iterator iter = pieces.begin();

    // Encontrar a posição correta para inserção
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



