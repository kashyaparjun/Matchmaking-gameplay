#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Player {
    public:
        string name;
        int score;
};

class Game {
    public:
        vector<Player*> teamA;
        vector<Player*> teamB;
        int playersPerTeam;
        int teamAScore;
        int teamBScore;
        int absDiff;
};

Player* formatInp(string inp) {
    Player *obj = new Player;
    obj->name = inp.substr(0, inp.find(" "));
    obj->score = stoi(inp.substr(inp.find(" "), inp.length()));
    return obj;
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
    for(int i=0;i<inp.size();i++){
        cout<<inp[i]->name<<"";
    }
}
