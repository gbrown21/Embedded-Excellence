#include <iostream>
#include <string>
#include <limits>
#include <windows.h>
#include <random>
#include <list>

using namespace std;

int game_height = 10;
int game_width = 15;
int hidden_word_length, turn_number, number_of_incorrect_guesses, number_of_correct_guesses;
bool game_running;
list<char> correctly_guessed_letters, previously_guessed_letters;
list<char> hidden_word;

class GameTracker {
    public:

    void generate_word();
    char receive_guess();
    void turn();
    void is_game_over();
};

void GameTracker::generate_word(){
    list<string> possible_words;
    possible_words.push_back("cat");
    possible_words.push_back("dog");
    possible_words.push_back("coconuts");
    possible_words.push_back("valquiria");
    possible_words.push_back("montstmichel");
    random_device rd;  // Will be used to obtain a seed for the random number engine
    mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(0, 4); // Define the range [0, 4]
    int randomiser_result = distrib(gen);
    auto iterator = possible_words.begin(); // Iterator to the start of the list
    advance(iterator, randomiser_result); // Advance the iterator to the randomiser result element
    string output_word = *iterator;
    for (char output_word_letter : output_word){
        hidden_word.push_back(output_word_letter);
    }
    hidden_word_length = hidden_word.size();
}

char GameTracker::receive_guess() {
    char current_guess;
    bool guess_is_unique = false; // Start with false to enter the while loop
    cout << endl << "------------ Turn number: " << turn_number << "! ----------" << endl;
    cout << "Please type a letter to make a guess: " << endl;

    while (!guess_is_unique) {
        if (!(cin >> current_guess) || cin.peek() != '\n') { // Also check if more than one character is entered
            cout << "Invalid input. Please enter a single lowercase letter: ";
            cin.clear(); // Clear the error flag
            cin.ignore(std::numeric_limits<streamsize>::max(), '\n'); // Ignore the incorrect input
            continue; // Skip the rest of the loop and try again
        }
        
        guess_is_unique = true; // Assume the guess is unique until proven otherwise
        for (char previous_guess : previously_guessed_letters) {
            if (previous_guess == current_guess) {
                guess_is_unique = false;
                cout << "Letter '" << current_guess << "' has already been guessed. Please try a different letter: ";
                break; // No need to check further
            }
        }

        if (guess_is_unique) {
            previously_guessed_letters.push_back(current_guess); // Add the new, unique guess to the list
        }
    }

    return current_guess;
}

void GameTracker::turn(){
    bool was_guess_correct = false;
    char current_guess = receive_guess();
    for (char letter : hidden_word){
        if (current_guess == letter){
            number_of_correct_guesses++;
            correctly_guessed_letters.push_back(current_guess);
            previously_guessed_letters.push_back(current_guess);
            was_guess_correct = true;
        }
    }
    if (was_guess_correct == false){
        previously_guessed_letters.push_back(current_guess);
        number_of_incorrect_guesses++;
    }
    turn_number++;
}

void GameTracker::is_game_over(){
    if(number_of_incorrect_guesses == 8){
        cout << "YOU LOSE!";
        game_running = false;
    }
    if(number_of_correct_guesses >= hidden_word_length){
        cout << "YOU WIN!";
        game_running = false;
    }
}

class GameRender {
    public:

    void render_game();
    void render_letters();
};

void GameRender::render_game() {
    system("cls");
    
    for (int i = 0; i < game_height; i++) {
        for (int j = 0; j < game_width; j++){
            if(i == 0 && number_of_incorrect_guesses >= 3){
                cout << "-";
            }
        }
        for (int j = 0; j < game_width; j++){
            if (i == game_height - 1 && i != 0 && number_of_incorrect_guesses >= 1){
                cout << "-";
            }
            if (i != 0 && i != game_height - 1 && j == 0 && number_of_incorrect_guesses >= 2) {
                cout << "|";
            }
            if (i == 1 && j == 0 && number_of_incorrect_guesses >= 4){
                cout << "/";
            }
            if (((i == 1 && j == 13) || (i == 2 && j == 14)) && number_of_incorrect_guesses >= 5){
                cout << "|";
            }
            if (i == 3 && j == 14 && number_of_incorrect_guesses >= 6){
                cout << "O";
            }
            if (i == 4 && j == 12 && number_of_incorrect_guesses >= 7){
                cout << "--|--";
            }
            if (i == 5 && j == 13 && number_of_incorrect_guesses >= 8){
                cout << "/ |";
            }
             else {
                cout << " ";
            }
        }
        cout << endl;
    }
}

void GameRender::render_letters(){
    cout << endl;
    for (char letter : hidden_word){
        bool letter_display = false;
        for (char guessed_letter : correctly_guessed_letters){
            if (guessed_letter == letter){
                letter_display = true;
            }
        }
        if (letter_display){
            cout << letter << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}


int main(){
    GameTracker game_tracker;
    GameRender game_render;
    game_running = true;
    game_tracker.generate_word();
    cout << "\n-----------------WELCOME TO HANGMAN"
         << "-------------------------\n";
    turn_number = 1;
    while (game_running){
    game_tracker.turn();
    game_render.render_game();
    game_render.render_letters();
    game_tracker.is_game_over();
    
    }
    

}