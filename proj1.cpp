#include<iostream>
#include<vector>
using namespace std;

struct Plate{
    int lenght;
    int width;
    int price;
};

// recursion that realizes the cut
int cut(Plate plate, int X, int Y){
    int a = plate.lenght;
    int b = plate.width;

    // The plate is smaller than the piece
    if (X < a || Y < b) {
        return 0;
    }

    // The plate is equal to the piece
    else if (X == a && Y == b) {
        return 1;
    }

    // Case where the piece is cut horizontally
    else if (X > a && Y == b) {
        return 1 + cut(plate, X - a, Y);
    }

    // Case where the piece is cut vertically
    else if (Y > b && X == a) {
        return 1 + cut(plate, X, Y - b);
    } else {
        return cut(plate, X - a, Y);
    }
}

// Function to insert novaplate in the correct order which is higher to lower by price
int insertSorted(std::vector<Plate>& plates, Plate& newPlate) {
    int position = 0;

    // Find the correct position for insertion
    while (position < (int) plates.size() && newPlate.price > plates[position].price) {
        position++;
    }

    plates.insert(plates.begin() + position, newPlate);
    return position;
}


int main(){
    int X, Y;
    int n, result = 0;
    vector<Plate> plates;

    cin >> X >> Y;  // plate dimensions
    cin >> n;       // types of plates

    for(int i = 1; i <= n; i++){
        int a, b, price;
        cin >> a >> b >> price;
        if (a > X || b > Y){      // plate is bigger than the original
            continue;
        }

        Plate newPlate = {a, b, price};
        int indx = insertSorted(plates, newPlate);
        int temp = cut(plates[indx], X, Y);
        temp *= plates[indx].price;
        if(temp > result){
            result = temp;
        }
    }

    cout << result << endl;
    return 0;
}



