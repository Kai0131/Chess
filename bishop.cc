#include "bishop.h"
#include <iostream>
using namespace std;


bishop::bishop(chessboard* board,coordinate coor,bool side):chess{board},
    side{side},coor{coor} {
        moved = false;
    }

bool bishop::getside() {
    return side;
}

bool bishop::getmoved(){
    return moved;
}

char bishop::gettype() {
    if (side == true) {
        return 'B';
    } else {
        return 'b';
    }
}

coordinate bishop::getcoor() {
    return coor;
}

void bishop::setcoor(coordinate c) {
    coor.assign(c);
}

void bishop::move(coordinate target){
    for(auto val: nextsteps) {
          if (target.equal(val)) {
            if(board->getchess(target)) {
                board->removechess(target);
            }
            board->placechess(this,target);
            board->removechess(coor);
            coor.assign(target);
            moved = true;
            UpdateNext(false);

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

void bishop::pushsteps(coordinate direction) {
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

void bishop::UpdateNext(bool testing) {
    threaten.clear();
    nextsteps.clear();

    coordinate case5 = {1,1}; //right-up;
    coordinate case6 = {1,-1}; //right-down;
    coordinate case7 = {-1,1}; //left-up
    coordinate case8 = {-1,-1}; //left-down;

    pushsteps(case5);
    pushsteps(case6);
    pushsteps(case7);
    pushsteps(case8);

}

chess* bishop::isthreatenby(coordinate c) {
    for(auto val:threaten) {
        if (c.equal(val)){
            return this;
        }
    }
    return nullptr;
}
