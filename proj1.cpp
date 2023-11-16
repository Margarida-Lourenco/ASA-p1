#include<iostream>
using namespace std;

int main(){
    int X, Y;
    int n, areaChapa, result = 0;
    cin >> X >> Y;  //chapa dimensions
    cin >> n;       // types os chapas
    areaChapa = X * Y;

    for(int i = 1; i <= n; i++){
        int a, b, price;
        cin >> a >> b >> price;
        if (a > X || b > Y){
            cout << "0" << endl;
            break;
        }
        int areaPeca = a * b;
        int qtd = areaChapa / areaPeca;
        int totalPrice = qtd * price;

        if (totalPrice > result){
            result = totalPrice;
        }
    }
    
    cout << result << endl;
    return 0;
}