#include <iostream>
#include <string.h> 

using namespace std;

double balance = 500;

void deposit(){
    double depositAmount;
    cout << "Great. How much would you like to deposit today?";
    cin >> depositAmount;
    balance += depositAmount;
    cout << "Thank you. That amount has been deposited. Please choose display to see your updated balance.";
}

void withdraw(){
    double withdrawalAmount;
    cout << "Great. How much would you like to withdraw today?";
    cin >> withdrawalAmount;
    balance -= withdrawalAmount;
    cout << "Thank you. That amount has been withdrawn. Please choose display to see your updated balance.";
}

void display(){
    string displayString = "Your current balance is: £" + to_string(balance) + ".";
    cout << displayString;
}

int main(){
    string actionChoice;
    cout << "Welcome to Guy's bank. What would you like to do today? Type deposit, withdraw or display balance.";
    cin >> actionChoice;
    if(actionChoice == "deposit"){
        deposit();
    }
    if(actionChoice == "withdraw"){
        withdraw();
    }
    if(actionChoice == "displayBalance"){
        display();
    }
}