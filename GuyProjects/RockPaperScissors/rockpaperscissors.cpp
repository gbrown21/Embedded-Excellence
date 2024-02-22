#include <iostream>
#include <string>
#include <limits>
#include <windows.h>
#include <random>

using namespace std;

class Game {
    public:
    int best_of, computer_wins, user_wins, keeps_playing;

    void start_game();
    void turn();
    int get_computer_choice();
    void end_game();
};

void Game::start_game(){
    computer_wins = 0;
    user_wins = 0;
    cout << "Welcome to Rock, Paper, Scissors. I hope you're feeling lucky." << endl;
    cout << "How many rounds would you like to play to decide the winner? Please enter an odd number between 1 and 9:" << endl;
    while(!(cin >> best_of) || best_of < 1 || best_of > 9 || !(best_of % 2 == 1)){
        std::cout << "Invalid input. Please enter an odd number between 1 and 9: ";
        std::cin.clear(); // Clear the error flag
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    cout << "Great! We will play a best of " << best_of << endl;
}

void Game::turn(){
    int user_choice;
    string computer_choice;
    int randomiser;
    int turn_number = user_wins + computer_wins;
    cout << "\n ------------------- round " << turn_number << " -------------------" << endl; 
    cout << "What will you choose? 1 for rock, 2 for paper, 3 for scissors." << endl;
    cin >> user_choice;
    cout << "THREE! ";
    Sleep(1000);
    cout << "TWO! ";
    Sleep(1000);
    cout << "ONE!" << endl;
    Sleep(1000);
    randomiser = get_computer_choice();
    if(randomiser == 1) {
        computer_choice = "ROCK!";
    }
    if(randomiser == 2) {
        computer_choice = "PAPER!";
    }
    if(randomiser == 3) {
        computer_choice = "SCISSORS!";
    }
    cout << computer_choice << endl;
    if(user_choice == randomiser){
        cout << "AH IT'S A DRAW. GO AGAIN GO AGAIN!!" << endl;
    } else if(user_choice == randomiser - 2 || user_choice == randomiser + 1){
        user_wins += 1;
        cout << "NOOO YOU WIN." << endl << "THAT MEANS I'VE WON " << computer_wins << " GAMES, AND YOU'VE WON " << user_wins << "!!" << endl;
    } else if(randomiser == user_choice -2 || randomiser == user_choice + 1){
        computer_wins += 1;
        cout << "YESSS I WINNN!!" << endl << "THAT MEANS I'VE WON " << computer_wins << " GAMES, AND YOU'VE WON " << user_wins << "!!" << endl;
    }
}

int Game::get_computer_choice(){
    //Generate computer choice
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(1, 3); // Define the range [0, 2]
    int randomiser_result = distrib(gen);
    return randomiser_result;
}

void Game::end_game(){
    int play_again;
    if(user_wins > computer_wins){
        cout << "OH NO I'VE LOST! NOT FAIR YOU CHEATED, LET'S PLAY AGAIN AND NO CHEATING THIS TIME!" << endl;
    } else if(computer_wins > user_wins){
        cout << "YES I WINNNNN!!! I AM THE GREATEST ROCK PAPER SCISSORS PLAYER OF ALL TIMMMME! YOU WOULDN'T DARE GIVE ME A REMATCH!" << endl;
    }
    cout << "Would you like to play again? Type 1 to play again, 2 to end the game." << endl;
    cin >> play_again;
    if(play_again == 1){
        user_wins = 0;
        computer_wins = 0;
        keeps_playing = 1;
    } else {
        keeps_playing = 0;
        cout << "Thank you for playing!" << endl;
    }
}

int main() {
    Game game;
    game.keeps_playing = 1;
    while(game.keeps_playing == 1){
    game.start_game();
    while(game.computer_wins + game.user_wins <= game.best_of / 2 || game.computer_wins == game.user_wins){
        game.turn();
    }
    game.end_game();
    }
}