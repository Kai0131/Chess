#include "computer.h"
#include "iostream"
#include<ctime>
using namespace std;
computer::computer(chessboard* board,bool side): board{board},side{side} {
    level = 1;
    updatechesses();
}

void computer::setlevel(int i) {
    if(i >= 3 || i <= 1){
        level = 1;
    }else {
        level = i;
    }
}

void computer::move() {
    string s;
    if(cin>>s) {
        if (s == "move") {
            if (level == 1) {
                level1();
            } else if (level == 2) {
                level2();
            }
        }
    }
    board->printboard();
}

void computer::updatechesses(){
    allchesses.clear();
    for(int i=0; i<width; i++) {
        for (int j=0; j<width;j++) {
            if(board->getchess({i,j}) != nullptr) {
                if(board->getside({i,j}) == side) {
                    allchesses.push_back(board->getchess({i,j}));
                }
            }
        }
    }
}

void computer::level1() {
    updatechesses();
    vector<chess*> canmove;
    for(auto val: allchesses) {
        val->updatelegal();
        if (val->level1count() != 0) {
            canmove.push_back(val);
        }
    }
    unsigned long length = canmove.size();
    srand((unsigned) time(0));;
    int ran = rand()%length;
    canmove.at(ran)->level1();
}

void computer::level2() {
    updatechesses();
    vector<chess*> capcheck;
    for(auto val: allchesses) {
        val->updatelegal();
        if(val->level2count() != 0) {
            capcheck.push_back(val);
        }
    }

    if (capcheck.size() == 0) {
        level1();
        return;
    }

    unsigned long length = capcheck.size();
    srand((unsigned) time(0));;
    int ran = rand()%length;
    capcheck.at(ran)->level2();
}

