#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    double pesos, dollars;

    cout << "Enter number of Colombian Pesos: ";
    cin >> pesos;
    dollars = pesos * 0.00032;
    cout << "Total USD = $" << dollars << "\n";
}