#include <iostream>
#include <string.h> 

using namespace std;

class BankAccount {
    string owner_name, address;
    int balance;

    public:
    void open_account();
    void main_menu();
    void display_balance();
    void withdraw();
    void deposit();
    void end_action();
};

void BankAccount::open_account(){
    cout << "Hello. Thank you for choosing to open an account with us today. What is your name?" << endl;
    cin >> owner_name;
    cout << "Great, your name is: " << owner_name << endl << "Please could you write down your current address?" << endl;
    cin >> address;
    cout << address << " is a lovely area! Thanks for the information, you're all setup. You will now proceed to the main menu." << endl;
}

void BankAccount::main_menu(){
    int choice;
    cout << "Hello " << owner_name << ". Welcome to the main menu. Please choose from the following options." << endl;
    cout << "Press 1 to display balance, 2 to withdraw or 3 to deposit." << endl;
    cin >> choice;
    cout << "You chose option: " << choice << endl;
    if(choice == 1){
        display_balance();
    }
    if(choice == 2){
        withdraw();
    }
    if(choice == 3){
        deposit();
    }
}

void BankAccount::display_balance(){
    int choice;
    cout << "Your current balance is: " << balance << endl;
    end_action();
}

void BankAccount::withdraw(){
    int withdrawAmount;
    int choice;
    cout << "How much would you like to withdraw today? Please enter a multiple of 10." << endl;
    cin >> withdrawAmount;
    balance -= withdrawAmount;
    cout << "You chose to withdraw: " << withdrawAmount << ". Your new balance is: " << balance << endl;
    end_action();
}

void BankAccount::deposit(){
    int depositAmount;
    int choice;
    cout << "How much would you like to deposit today? Please enter a multiple of 10." << endl;
    cin >> depositAmount;
    balance += depositAmount;
    cout << "You chose to deposit: " << depositAmount << ". Your new balance is: " << balance << endl;
    end_action();
}

void BankAccount::end_action(){
    int choice;
    cout << "Type 1 if you would like to return to the main menu or 2 if you would are finished banking." << endl;
    cin >> choice;
    if(choice == 1){
        main_menu();
    } else {
        cout << "Thank you for banking with us today.";
    }
}

int main(){
    BankAccount customer;
    customer.open_account();
    customer.main_menu();
}