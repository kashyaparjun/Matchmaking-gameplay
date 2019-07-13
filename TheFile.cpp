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
        int average;

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
            this->average = 0;
            for(int i=0;i<this->players.size();i++){
                this->average+=this->players[i]->score;
            }
            this->average = (int)round(this->average/this->players.size());
        }
};

class Game {
    public:
        Team teamA;
        Team teamB;
        int quality;

        void calcQuality(){
            this->quality = (int)round(abs(this->teamA.average - this->teamB.average));
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

    for(int i=left;i<=n;i++) {
        tmp.push_back(inp[i]);
        combine(teams, tmp, inp, n, i+1, k-1);
        tmp.pop_back();
    }

}

vector<Team*> makeCombinations(vector<Player*> inp, int n, int k){
    vector<Team*> teams;
    vector<Player*> tmp;
    combine(teams, tmp, inp, n, 1, k);
    return teams;
}





int main()
{
    vector<Player*> inp;
    string tempInp;
    cout<<"Enter input followed by enter"<<"\n";
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
    vector<Team*> teams = makeCombinations(inp, inp.size(), 2);
    for(int i=0;i<teams.size();i++) {
        cout<<"team"<<endl;
        for(int j=0;j<teams[i]->players.size();j++){
            cout<<teams[i]->players[j]->name<<endl;
        }
    }
}
