#include "king.h"
#include"iostream"
using namespace std;


king::king(chessboard* board,coordinate coor, bool side): chess{board}, side{side},coor{coor} {
    moved = false;
}

bool king::getside() {
    return side;
}

bool king::getmoved(){
    return moved;
}

char king::gettype() {
    if (side == true) {
        return 'K';
    } else {
        return 'k';
    }
}

coordinate king::getcoor() {
    return coor;
}

void king::setcoor(coordinate c) {
    coor.assign(c);
}

void king::move(coordinate target){
    for(auto val: nextsteps) {
        if (target.equal(val)) {
            if(board->getchess(target)) {
                board->removechess(target);
            }
            board->placechess(this,target);
            board->removechess(coor);
            coordinate original = coor;
            coor.assign(target);
            moved = true;

            if(original.x - coor.x == 2) {//long castling
                chess* r = board->getchess({0,original.y});
                board->placechess(r,{original.x-1,original.y});
                r->setcoor({original.x-1,original.y});
                board->removechess({0,original.y});
            } else if(original.x - coor.x == -2) {
                chess* r = board->getchess({7,original.y});
                board->placechess(r,{original.x+1,original.y});
                r->setcoor({original.x+1,original.y});
                board->removechess({7,original.y});
            }
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


void king::UpdateNext(bool testing) {
    nextsteps.clear();
    threaten.clear();
    for(int i=-1; i<= 1;i++) {
        for(int j=-1; j<= 1; j++) {
            if(i == 0 && j == 0) continue;
            coordinate case1 = coor.add({i,j});
            if(case1.valid()) {
                threaten.push_back(case1);

                if((board->getchess(case1) == nullptr)) {
                    if (board->issafe(case1,side) == true) {
                        nextsteps.push_back(case1);
                    }
                } else {
                    if ((board->getside(case1) != side)&&(board->issafe(case1,side) == true)) {
                        nextsteps.push_back(case1);
                    }
                }
            }
        }
    }


    if(moved == false && board->getchess(coor.add({-4,0})) != nullptr ) {// long castling:
        if(board->getchess(coor.add({-4,0}))->getmoved() == false) {
            if ((board->getchess(coor.add({-3,0})) == nullptr) &&
                    (board->getchess(coor.add({-2,0})) == nullptr) &&
                    (board->getchess(coor.add({-1,0})) == nullptr)) {
                if(board->issafe(coor.add({-2,0}),side) &&
                        board->issafe(coor.add({-1,0}),side) &&
                        board->issafe(coor,side)){
                    nextsteps.push_back(coor.add({-2,0}));
                }
            }
        }
    }

    if(moved == false && board->getchess(coor.add({3,0})) != nullptr) {// short castling:
        if(board->getchess(coor.add({3,0}))->getmoved() == false) {
            if ((board->getchess(coor.add({2,0})) == nullptr) &&
                    (board->getchess(coor.add({1,0})) == nullptr)) {
                if(board->issafe(coor.add({2,0}),side) &&
                        board->issafe(coor.add({1,0}),side) &&
                        board->issafe(coor,side)) {
                    nextsteps.push_back(coor.add({2,0}));
                }
            }
        }
    }
    if(board->iskingsafe(coor,side) == false) {
        if(nextsteps.size() == 0) {
            throw this;
        }
    }
}

chess* king::isthreatenby(coordinate c){
    for(auto val:threaten) {
        if (c.equal(val)){
            return this;
        }
    }
    return nullptr;
}


