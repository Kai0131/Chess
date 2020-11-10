#include "knight.h"
#include <iostream>
using namespace std;


knight::knight(chessboard* board,coordinate coor, bool side):
    chess{board},coor{coor},side{side}{
        moved = false;
    }

bool knight::getside() {
    return side;
}

bool knight::getmoved(){
    return moved;
}

char knight::gettype() {
    if (side == true) {
        return 'N';
    } else {
        return 'n';
    }
}

void knight::setcoor(coordinate c) {
    coor.assign(c);
}

coordinate knight::getcoor() {
    return coor;
}

void knight::move(coordinate target){
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

void knight::pushsteps(coordinate c) {
    if (c.valid() == true) {
        if(board->getchess(c) == nullptr) {
            nextsteps.push_back(c);
            threaten.push_back(c);
        } else if (board->getside(c) != side) {
            nextsteps.push_back(c);
            threaten.push_back(c);
        }
    }
}

void knight::UpdateNext(bool testing) {
    threaten.clear();
    nextsteps.clear();

    coordinate case1 = {-2,-1};
    coordinate case2 = {-2,1};
    coordinate case3 = {2,1};
    coordinate case4 = {2,-1};
    coordinate case5 = {1,2};
    coordinate case6 = {1,-2};
    coordinate case7 = {-1,2};
    coordinate case8 = {-1,-2};

    pushsteps(coor.add(case1));
    pushsteps(coor.add(case2));
    pushsteps(coor.add(case3));
    pushsteps(coor.add(case4));
    pushsteps(coor.add(case5));
    pushsteps(coor.add(case6));
    pushsteps(coor.add(case7));
    pushsteps(coor.add(case8));

}

chess* knight::isthreatenby(coordinate c) {
    for(auto val:threaten) {
        if (c.equal(val)){
            return this;
        }
    }
    return nullptr;
}

