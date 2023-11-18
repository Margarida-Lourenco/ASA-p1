#include<iostream>
#include<vector>
using namespace std;

struct Chapa{
    int lenght;
    int width;
    int price;
};

// recursion that realizes the cut (n sei como fazer)
int cut(Chapa chapa, int &result, int X, int Y){
}

int main(){
    int X, Y;
    int n, areaChapa, result = 0;
    vector<Chapa> chapas;
    Chapa chapa;

    cin >> X >> Y;  //chapa dimensions
    cin >> n;       // types os chapas
    areaChapa = X * Y;

    for(int i = 1; i <= n; i++){
        int a, b, price;
        cin >> a >> b >> price;
        if (a > X || b > Y){      // chapa bigger than the original
            continue;
        }
        chapa.lenght = a;
        chapa.width = b;
        chapa.price = price;
        chapas.push_back(chapa);
    }
    
    // final vector is ordered by price (higher to lower)
    for(int i = 0; i < chapas.size(); i++){
        for(int j = i + 1; j < chapas.size(); j++){
            if(chapas[i].price < chapas[j].price){
                Chapa aux = chapas[i];
                chapas[i] = chapas[j];
                chapas[j] = aux;
            }
        }
    }

    for(int i = 0; i < chapas.size(); i++){
        //cut(chapas[i], result);
    }


    cout << result << endl;
    return 0;
}
