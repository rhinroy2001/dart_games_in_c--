#include <iostream>
#include <iterator>
#include <list>

using namespace std;

class Player{
    public: 
        int score;
        int number;
        Player(int playerNumber, int playerScore){
            setNumber(playerNumber);
            setScore(playerScore);
        }
        int getScore(){
            return score;
        }
        int getNumber(){
            return number;
        }
        void setScore(int x){
            score = x;
        }
        void setNumber(int x){
            number = x;
        }
};

void whatToAimFor(int round, int target){
       cout << "round " << round << "/15 | aim for " << target << endl;
}

bool halveIt(int x, int y, int z){
    if(x == 0 && y == 0 && z ==0){
        return true;
    }
    return false;
}

int calculateScore(int curScore, int x, int y, int z, int mult){
    return curScore + ((x + y + z) * mult);
}

void displayScore(list<Player>::iterator itr, list<Player> players){
    for(list<Player>::iterator i = players.begin(); i != players.end(); ++i){
        cout << "player " << i->number << ": " << i->score << endl;
    }
}

list<Player> createPlayers(int numPlayers, list<Player> playerList){
    for(int i = 1; i < numPlayers + 1; i++){
        Player player = Player(i, 0);
        playerList.push_back(player);
    }
    return playerList;
}

list<Player> createPlayers(int numPlayers, list<Player> playerList, int startingScore){
    for(int i = 1; i < numPlayers + 1; i++){
        Player player = Player(i, startingScore);
        playerList.push_back(player);
    }
    return playerList;
}


void playHalveIt(){
    list<Player> playerList;
    list<Player>::iterator itr;
    int numPlayers = 0;
    int round = 1;
    srand((unsigned) time(NULL));

    cout << "Enter the number of players" << endl;
    cin >> numPlayers;
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You have entered invalid input" << endl;
            cout << "Reenter the number of player" << endl;
            cin >> numPlayers;
        }
        if(!cin.fail()){
            break;
        }
    }
    playerList = createPlayers(numPlayers, playerList);
    for(; round <= 15; round++){
        int random = rand() % 21;
        whatToAimFor(round, random);
        for(list<Player>::iterator i = playerList.begin(); i != playerList.end(); ++i){
            int dart1;
            int dart2;
            int dart3;
            cout << "player " << i->number << " is up" << endl;
            cout << "Enter the score for your 3 darts. 0 for miss, 1 for single, 2 for double, 3 for triple" << endl;
            cin >>  dart1 >> dart2 >> dart3;
            while(1){
                if(cin.fail()){
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You have entered invalid input" << endl;
                    cout << "Reenter your score" << endl;
                    cin >> dart1 >> dart2 >> dart3;
                }
                if(!cin.fail()){
                    break;
                }
            }
            if(halveIt(dart1, dart2, dart3)){
                i->score = i->score / 2;
            }else{
                int newScore = calculateScore(i->getScore(), dart1, dart2, dart3, random);
                i->setScore(newScore);
            }
        }
        displayScore(itr, playerList);
    }
}

int pick01x(int x){
    if(x == 1){
        return 301;
    }
    if(x == 2){
        return 501;
    }
    if(x == 3){
        return 701;
    }
    if(x == 4){
        return 901;
    }
}

bool gameOver(list<Player>::iterator itr, list<Player> players){
    for(list<Player>::iterator i = players.begin(); i != players.end(); ++i){
        if(i->score == 0){
            return true;
        }
    }
    return false;
}

int prefixScore(char prefix, int dart){
    if(prefix == 'S'){
        return dart;
    }
    if(prefix == 'D'){
        return dart * 2;
    }
    if(prefix == 'T'){
        return dart * 3;
    }
    if(prefix == 'B' && dart == 1){
        return 25;
    }
    if(prefix == 'B' && dart == 2){
        return 50;
    }
}

int calculateScore(int curScore, int dart1, int dart2, int dart3){
    int newScore = curScore - dart1 - dart2 - dart3;
    if(newScore < 0){
        return curScore;
    }
    return newScore;
}

void play01x(){
    list<Player> playerList;
    list<Player>::iterator itr;
    int numPlayers = 0;
    int round = 1;
    int startingScore = 0;

    cout << "Enter the number of players" << endl;
    cin >> numPlayers;
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You have entered invalid input" << endl;
            cout << "Reenter the number of player" << endl;
            cin >> numPlayers;
        }
        if(!cin.fail()){
            break;
        }
    }

    cout << "Pick a game \n1->301\n 2->501\n 3->701\n 4->901" << endl;
    cin >> startingScore;
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You have entered invalid input" << endl;
            cout << "Reenter game" << endl;
            cin >> startingScore;
        }
        if(!cin.fail()){
            break;
        }
    }

    createPlayers(numPlayers, playerList, startingScore);

    while(1){
        cout << "round " << round << endl;
        for(list<Player>::iterator i = playerList.begin(); i != playerList.end(); ++i){
            int dart1;
            int dart2;
            int dart3;
            char prefix1;
            char prefix2;
            char prefix3;
            cout << "player " << i->number << " is up" << endl;
            cout << "Enter the score for your 3 darts\nS number for single\nD number for double\nT number for triple\nB 1 for single bull\nB 2 for double bull" << endl;
            cin >> prefix1 >> dart1 >> prefix2 >> dart2 >> prefix3 >> dart3;
            dart1 = prefixScore(prefix1, dart1);
            dart2 = prefixScore(prefix2, dart2);
            dart3 = prefixScore(prefix3, dart3);
            i->score = calculateScore(i->score, dart1, dart2, dart3);
            if(gameOver(itr, playerList)){
                break;

            }
        }
        displayScore(itr, playerList);
    }


}

int main(){
    int num;
    cout << "1-> 01x games\n2-> Halve it\n0-> Quit game" << endl;
    cin >> num;
    while(1){
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "You have entered invalid input" << endl;
            cout << "Reenter game" << endl;
            cin >> num;
        }
        if(!cin.fail()){
            break;
        }
    }
    if(num == 1){
        play01x();
    }
    if(num == 2){
        playHalveIt();
    }
    if(num == 0){
        return 0;
    }
}