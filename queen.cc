#include "queen.h"
#include "chess.h"
#include <iostream>
using namespace std;


queen::queen(chessboard* board,coordinate coor, bool side):
    chess{board},side{side},coor{coor} {
        moved = false;
    }

bool queen::getside() {
    return side;
}

bool queen::getmoved(){
    return moved;
}

char queen::gettype() {
    if (side == true) {
        return 'Q';
    } else {
        return 'q';
    }
}

coordinate queen::getcoor() {
    return coor;
}

void queen::setcoor(coordinate c) {
    coor.assign(c);
}

void queen::move(coordinate target){
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
                if (board->getchess(val) != nullptr) {
                    if(side == true && board->getchesstype(val) == 'k') {
                        cout<< "Black is in check."<<endl;
                    }

                    if(side == false && board->getchesstype(val) == 'K') {
                        cout<< "White is in check" << endl;
                    }
                }
            }
            return;
        }
    }
    throw "You are not allowed to make this move";
}

void queen::pushsteps(coordinate direction) {
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

void queen::UpdateNext(bool testing) {
    threaten.clear();
    nextsteps.clear();

    coordinate case1 = {0,1}; // upwards
    coordinate case2 = {0,-1}; // downward;
    coordinate case3 = {1,0}; // right;
    coordinate case4 = {-1,0}; //left;
    coordinate case5 = {1,1}; //right-up;
    coordinate case6 = {1,-1}; //right-down;
    coordinate case7 = {-1,1}; //left-up
    coordinate case8 = {-1,-1}; //left-down;

    pushsteps(case1);
    pushsteps(case2);
    pushsteps(case3);
    pushsteps(case4);
    pushsteps(case5);
    pushsteps(case6);
    pushsteps(case7);
    pushsteps(case8);

}

chess* queen::isthreatenby(coordinate c) {
    for(auto val:threaten) {
        if (c.equal(val)){
            return this;
        }
    }
    return nullptr;
}

