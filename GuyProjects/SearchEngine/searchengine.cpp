#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>


using namespace std;

struct episode {
    int season_number, episode_number;
    string episode_name;
    bool ross_and_rachel_together;
};

struct season {
    vector<episode> episodes;
};

struct friends_tv_series {
    int number_of_seasons;
    vector<season> seasons;
};


bool parseBoolFromString(const string& value) {
    return value == "1" || value == "true";
}

void pull_data_from_csv(const string& filename, friends_tv_series& show) {
    ifstream file(filename);
    string line;
    int current_season = -1;

    //data structure is: Season,Episode,Title,Writer,Director,Date Aired,Summary,Rating/Share,US Viewership (in millions)

    while (getline(file, line)) {
        stringstream ss(line);
        string season_number_string, episode_number_string, episode_name_string, writer, director, date, summary, rating, viewership;
        getline(ss, season_number_string, ',');
        getline(ss, episode_number_string, ',');
        getline(ss, episode_name_string, ',');
        getline(ss, writer, ',');
        getline(ss, director, ',');
        getline(ss, date, ',');
        getline(ss, summary, ',');
        getline(ss, rating, ',');
        getline(ss, viewership);

        int season_num = 0;
        try {
            season_num = stoi(season_number_string);
        } catch (const std::invalid_argument& e) {
            cerr << "Invalid argument for stoi. String was: '" << season_number_string << "'. Error: " << e.what() << endl;
            continue; // Skip this line or handle the error appropriately
        } catch (const std::out_of_range& e) {
            cerr << "Out of range error for stoi. String was: '" << season_number_string << "'. Error: " << e.what() << endl;
            continue; // Skip this line or handle the error appropriately
}
    
        int episode_num = stoi(episode_number_string);

        // If we're at a new season, add a new season to the show
        if (season_num != current_season) {
            show.seasons.push_back(season());
            current_season = season_num;
        }

        // Add episode to the latest season
        episode newEpisode = {season_num, episode_num, episode_name_string, false};
        show.seasons.back().episodes.push_back(newEpisode);
    }

}

void populate_relationship_status(friends_tv_series& show){
    for (auto& season : show.seasons){
        for (auto& episode : season.episodes){
            if (episode.season_number == 2 && episode.episode_number >= 7 ||
                episode.season_number == 3 && episode.episode_number <= 16 ||
                episode.season_number == 10 && episode.episode_number >= 17){
                    episode.ross_and_rachel_together = true;
                }
        }
    }
}

void display_interface_to_database(friends_tv_series& show){
    int input_season_num = -1;
    int input_episode_num = -1;
    bool relationship_status = false;
    cout << "Welcome to the Ross and Rachel super fan database. Never watch an episode of Friends that Ross and Rachel aren't together ever again." << endl;
    cout << "Please input the season you are watching: " << endl;
    cin >> input_season_num;
    cout << "Thanks! You are watching season " << input_season_num << "!" << endl;
    cout << "Please input the episode number you would like to watch: " << endl;
    cin >> input_episode_num;
    cout << "Thanks! You would like to watch episode number: " << input_episode_num << "!" << endl;
    cout << "Retrieving data..." << endl;
    Sleep(1000);
    int season_number_index = input_season_num - 1;
    int episode_number_index = input_episode_num - 1;
    if (season_number_index >= 0 && season_number_index < show.seasons.size()) {
        const season& season = show.seasons[season_number_index];

        // Check if the episode index is within bounds
        if (episode_number_index >= 0 && episode_number_index < season.episodes.size()) {
            const episode& chosen_episode = season.episodes[episode_number_index];
            bool output_relationship_status = chosen_episode.ross_and_rachel_together;
            if (output_relationship_status){
                cout << endl;
                cout << "Y   Y  EEEEE  SSSS\n";
                cout << " Y Y   E     S    \n";
                cout << "  Y    EEE    SSS \n";
                cout << "  Y    E         S\n";
                cout << "  Y    EEEEE  SSSS\n" << endl;
                cout << "Ross and Rachel WERE together in season " << input_season_num << " episode " << input_episode_num << ": " << chosen_episode.episode_name << ". Happy watching!" << endl;
            } else {
                cout << endl;
                cout << "N   N  OOOO \n";
                cout << "NN  N O    O\n";
                cout << "N N N O    O\n";
                cout << "N  NN O    O\n";
                cout << "N   N  OOOO \n" << endl;
                cout << "Ross and Rachel WERE NOT together in season " << input_season_num << " episode " << input_episode_num << ": " << chosen_episode.episode_name << ". DO NOT WATCH!" << endl;
            }
        } else {
            cout << "Episode number " << input_episode_num << " does not exist in season " << input_season_num  << "." << endl;
        }
    } else {
        cout << "Season number " << input_season_num  << " does not exist." << endl;
    }
}


int main() {
    friends_tv_series show;
    pull_data_from_csv("friends.csv", show);
    populate_relationship_status(show);
    display_interface_to_database(show);

    return 0;
}