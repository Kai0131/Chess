#include "chess.h"
#include<sstream>
#include<iostream>
using namespace std;

coordinate coordinate::add(const coordinate& c) {
    return {x + c.x, y +c.y};
}

bool coordinate::equal(const coordinate& c) {
    return c.x==x && c.y == y;
}

void coordinate::assign(const coordinate& c){
    x = c.x;
    y = c.y;
}

bool coordinate::valid() {
    return x<= 7 && x >=0 && y >= 0 && y<=7;
}


istream &operator>>(istream &in, coordinate& coor) {
    string s;
    in>>s;
    stringstream ss{s};
    char newx;
    int newy;
    ss>>newx>>newy;
    coor.x = newx-'a';
    coor.y = newy-1;
    return in;
}

ostream &operator<<(ostream &out, coordinate& coor) {
    char a = coor.y - 'a';
    out<<coor.x+1<<a;
    return out;
}

chess::chess(chessboard* board): board{board}{}

void chess::updatelegal(){
    legalsteps.clear();
    checkcapture.clear();
    for(auto val: nextsteps) {
        if(board->legalmove(getcoor(),val,getside()) == true) {
            legalsteps.push_back(val);
            if(board->checkmove(getcoor(),val,getside()) == true) {
                checkcapture.push_back(val);
            }
            if(board->getchess(val) != nullptr) {
                if(board->getside(val) != getside()) {
                    checkcapture.push_back(val);
                }
            }
        }
    }
}

int chess::level1count() {
    return legalsteps.size();
}

int chess::level2count() {
    return checkcapture.size();
}

void chess::level1() {
    int count = level1count();
    int ran = rand()%count;
    board->move(getcoor(), legalsteps.at(ran));
}

void chess::level2() {
    int count = level2count();
    int ran = rand()%count;
    board->move(getcoor(), checkcapture.at(ran));
}
