#include "rook.h"
#include <iostream>
using namespace std;


rook::rook(chessboard* board,coordinate coor, bool side): chess{board},
    side{side},coor{coor} {
        moved = false;
    }

bool rook::getside() {
    return side;
}

bool rook::getmoved(){
    return moved;
}

char rook::gettype() {
    if (side == true) {
        return 'R';
    } else {
        return 'r';
    }
}

void rook::setcoor(coordinate c) {
    coor.x = c.x;
    coor.y = c.y;
}

coordinate rook::getcoor() {
    return coor;
}


void rook::move(coordinate target){
    for(auto val: nextsteps) {
            if (target.equal(val)) {
            if(board->getchess(target)) {
                board->removechess(target);
            }
            board->placechess(this,target);
            board->removechess(coor);
            coor.assign(target);
            moved = true;
            UpdateNext(true);

            for(auto val:threaten) {
                if(side == true && board->getchesstype(val) == 'k') {
                    cout<< "Black is in check."<<endl;
                }

                if(side == false && board->getchesstype(val) == 'K') {
                    cout<< "White is in check" << endl;
                }
            }
            return;
        }
    }
    throw "You are not allowed to make this move";
}

void rook::pushsteps(coordinate direction) {
    coordinate c = coor.add(direction);
    while(board->getchess(c) == nullptr) {
        if(c.valid() == false) {
            return;
        }
        nextsteps.push_back(c);
        threaten.push_back(c);
        c = c.add(direction);
    }

    if (c.valid() == true) {
        if(board->getside(c) != side) {
            nextsteps.push_back(c);
            threaten.push_back(c);
        }
    }
}

void rook::UpdateNext(bool testing) {
    threaten.clear();
    nextsteps.clear();

    coordinate case1 = {0,1}; // upwards
    coordinate case2 = {0,-1}; // downward;
    coordinate case3 = {1,0}; // right;
    coordinate case4 = {-1,0}; //left;

    pushsteps(case1);
    pushsteps(case2);
    pushsteps(case3);
    pushsteps(case4);
}

chess* rook::isthreatenby(coordinate c) {
    for(auto val:threaten) {
        if (c.equal(val)){
            return this;
        }
    }
    return nullptr;
}

