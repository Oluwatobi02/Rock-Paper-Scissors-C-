#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

char player_RPS() {
    char choice;
    cout << "Player 1: Enter your choice (1=paper, 2=scissors, 3=rock)\n";
    cin >> choice;
    return choice;
}

int RPS_comparison(string player_choice, string ai_choice) {
    if (player_choice == ai_choice) {
        return 0;
    }
    if ((player_choice == "paper" && ai_choice == "rock") ||  // Paper beats Rock
        (player_choice == "scissors" && ai_choice == "paper") ||  // Scissors beats Paper
        (player_choice == "rock" && ai_choice == "scissors")) {  // Rock beats Scissors
        return 1;
    } else {
        return -1;
    }
}

void winner_tally_to_file(string text) {
    ofstream myfile;
    
    myfile.open("rps.txt", ios::app);
    
    if (myfile.is_open()) {
        myfile << text << "\n";
    }
    myfile.close();
}
void official_tally_from_file() {
    ifstream myfile;
    string line;
    myfile.open("rps.txt");
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            cout << line << "\n";
        }
    }
    myfile.close();
}
int main() {
    map<int, string> dictfile;
    dictfile[1] = "PLAYER 1 HAS THE MOST WINS IN THE TEN GAME SERIES";
    dictfile[-1] = "THE COMPUTER HAS THE MOST WINS IN THE TEN GAME SERIES";
    dictfile[0] = "MAJORITY OF THE GAMES ENDED IN A TIE";
    
    map<int, string> result;
    result[1] = "PLAYER1-WINS!!!";
    result[-1] = "COMPUTER-WINS!!!";
    result[0] = "TIE!!!";
    
    map<char, std::string> dict;

    dict['1'] = "paper";
    dict['2'] = "scissors";
    dict['3'] = "rock";

    int player1_score = 0;
    int aiplayer_score = 0;
    int game_round = 1;
    char player1_choice;

    while (game_round <= 10) {
        cout << "ROCK, PAPER, SCISSORS GAME (MATCH #" << game_round << ")\n";
        cout << "=======================================================\n";
        player1_choice = player_RPS();
        cout << "Player 1 entered " + dict[player1_choice] + " as the choice\n";
        srand(time(0));
        char ai_move = char(rand() % 3 + '1');
        cout << "Computer selected " + dict[ai_move] + " as the choice\n";
        int res = RPS_comparison(dict[player1_choice], dict[ai_move]);
        if (res == -1) {
            aiplayer_score ++;
            winner_tally_to_file(result[res]);
        }
    else if (res == 1){ 
        player1_score ++;
        winner_tally_to_file(result[res]);
        }
        else {
            aiplayer_score ++;
            player1_score ++;
            winner_tally_to_file(result[res]);
        }
        
        cout << result[res];
        
        cout << "\n";

        game_round++;
    }
    official_tally_from_file();
    if (aiplayer_score > player1_score) {
        cout << dictfile[-1] << "\n";
    }
    else if (aiplayer_score < player1_score) {
        cout << dictfile[1] << "\n";
    }
    else {
        cout << dictfile[0] << "\n";
    }

    return 0;
}
