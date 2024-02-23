#include <iostream>
#include <string>
#include <limits>
#include <windows.h>
#include <random>
#include <list>

using namespace std;

int game_height = 10;
int game_width = 15;

class GameTracker {
    public:
    list<char> hidden_word;
    list<char> guesses;
    int hidden_word_length, number_of_guesses;

    string generate_word();
    void game_init();
    void update_game();
};

string GameTracker::generate_word(){
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
    return *iterator; // Dereference the iterator to get the second element
}

class GameRender {
    public:

    void render_game();
};

void GameRender::render_game() {
    system("cls");
    
    for (int i = 0; i < game_height; i++) {
        for (int j = 0; j < game_width; j++){
            if(i == 0){
                cout << "-";
            }
        }
        for (int j = 0; j < game_width; j++){
            if (i != 0 && j == 1){
                cout << "|";
            }
             else {
                cout << " ";
            }
        }
        cout << endl;
    }
}


int main(){
    GameTracker game_tracker;
    GameRender game_render;
    game_render.render_game();
    

}