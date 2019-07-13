#include <iostream>
#include <bits/stdc++.h>
#include <math.h>

using namespace std;

class Player {
    public:
        string name;
        int score;
};

class Team{
    public:
        vector<Player*> players;
        map<string, bool> present;
        float average;
        string names;

        bool isPresent(vector<Player*> otherPlayers) {
            for(int i = 0;i<otherPlayers.size();i++){
                if(present.find(otherPlayers[i]->name)!=present.end()){
                    return true;
                }
            }
            return false;
        }

        void makeMap(){
            for(int i=0;i<this->players.size();i++){
                present[this->players[i]->name] = this->players[i]->score;
            }
        }

        void calcAverage(){
            this->average = 0.0;
            for(int i=0;i<this->players.size();i++){
                this->average+=this->players[i]->score;
            }
            this->average = (float)this->average/(float)this->players.size();
        }

        void concatNames() {
            this->names = "";
            for(int i=0;i<this->players.size();i++){
                this->names = this->names + this->players[i]->name;
                if(i<this->players.size()-1){
                    this->names = this->names + ",";
                }
            }
        }
};

class Game {
    public:
        Team *teamA;
        Team *teamB;
        float quality;

        void calcQuality(){
            this->quality = round(abs((float)this->teamA->average - (float)this->teamB->average));
        }

};

Player* formatInp(string inp) {
    Player *obj = new Player;
    obj->name = inp.substr(0, inp.find(" "));
    obj->score = stoi(inp.substr(inp.find(" "), inp.length()));
    return obj;
}

void combine(vector<Team*> &teams, vector<Player*> &tmp, vector<Player*> inp, int n, int left, int k){
    if(k==0) {
        Team *team = new Team;
        team->players = tmp;
        teams.push_back(team);
        return;
    }

    for(int i=left;i<n;i++) {
        tmp.push_back(inp[i]);
        combine(teams, tmp, inp, n, i+1, k-1);
        tmp.pop_back();
    }

}

vector<Team*> makeCombinations(vector<Player*> inp, int n, int k){
    vector<Team*> teams;
    vector<Player*> tmp;
    combine(teams, tmp, inp, n, 0, k);
    return teams;
}

vector<Game*> makeGames(vector<Team*> &teams){
    vector<Game*> games;
    for(int k=0;k<teams.size();k++){
        teams[k]->makeMap();
        teams[k]->calcAverage();
        teams[k]->concatNames();
    }
    for(int i=0;i<teams.size();i++){
        for(int j=i+1;j<teams.size();j++){
            if(i!=j){
                if(!teams[i]->isPresent(teams[j]->players)){
                    Game *game = new Game;
                    game->teamA = teams[i];
                    game->teamB = teams[j];
                    game->calcQuality();
                    games.push_back(game);
                }
            }
        }
    }
    return games;
}

bool compareQuality(Game *g1, Game *g2) {
    return (g1->quality)<(g2->quality);
}

void manualInput(){
    vector<Player*> inp;
    string tempInp;
    int k = 1;
    cout<<"Enter single input followed by enter [Format: <Name of player> <Score>]"<<"\n";
    while(true){
        getline(cin, tempInp);
        if(tempInp.length() == 0){
            break;
        }
        try{
            Player *obj = formatInp(tempInp);
            inp.push_back(obj);
        }catch(...) {
            cout<<"Wrong input format, please enter again..."<<"\n";
        }
    }
    cout<<"Enter number of player per team"<<endl;
    while(true){
        cin>>k;
        if(k>inp.size()/2){
            cout<<"Please enter team size =< total players / 2"<<endl;
        }
        else {
            break;
        }
    }
    vector<Team*> teams = makeCombinations(inp, inp.size(), k);
    vector<Game*> games = makeGames(teams);
    sort(games.begin(), games.end(), compareQuality);
    cout<<"Result:"<<endl;
    for(int i=0;i<games.size();i++){
        cout<<games[i]->teamA->names<<"("<<games[i]->teamA->average<<")"<<" vs "
            <<games[i]->teamB->names<<"("<<games[i]->teamB->average<<")"<<endl;
    }
}

int main()
{
    manualInput();
}
