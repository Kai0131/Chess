#include "pawn.h"
#include<iostream>
#include "chess.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
using namespace std;

pawn::pawn(chessboard* board,coordinate coor, bool side):
    chess{board},side{side},coor{coor} {
        moved = false;
    }

char pawn::gettype() {
    if (side == true) {
        return 'P';
    } else {
        return 'p';
    }
}

bool pawn::getside() {
    return side;
}

bool pawn::getmoved(){
    return moved;
}

coordinate pawn::getcoor() {
    return coor;
}

void pawn::setcoor(coordinate c) {
    coor.assign(c);
}

void pawn::move(coordinate target){
    for(auto val: nextsteps) {
        if (target.equal(val)) {
            if(board->getchess(target)) {
                board->removechess(target);
            }
            board->placechess(this,target);
            board->removechess(coor);
            coor.assign(target);
            moved = true;

            if(side == true && target.y == width-1) {
                char s;
                board->removechess(target);
                cin>>s;
                if(s == 'Q') {
                    board->placechess(new queen(board,target,true),target);
                } else if(s == 'R') {
                    board->placechess(new rook(board,target,true),target);
                } else if(s == 'N') {
                    board->placechess(new knight(board,target,true),target);
                } else if(s == 'B') {
                    board->placechess(new bishop(board,target,true),target);
                }


            } else if (side == false && target.y == 0) {
                char s;
                cin>>s;
                if(s == 'q') {
                    board->placechess(new queen(board,target,false),target);
                } else if(s == 'r') {
                    board->placechess(new rook(board,target,false),target);
                } else if(s == 'n') {
                    board->placechess(new knight(board,target,false),target);
                } else if(s == 'b') {
                    board->placechess(new bishop(board,target,false),target);
                }
            }

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

void pawn::UpdateNext(bool testing) {
    threaten.clear();
    nextsteps.clear();
    coordinate case1;
    coordinate case2;
    coordinate case3;
    coordinate case4;
    if(side == true) { //white
        case1 = {coor.x,coor.y+1};
        case2 = {coor.x,coor.y+2};
        case3 = {coor.x-1,coor.y+1};
        case4 = {coor.x+1,coor.y+1};
    } else { // black
        case1 = {coor.x,coor.y-1};
        case2 = {coor.x,coor.y-2};
        case3 = {coor.x-1,coor.y-1};
        case4 = {coor.x+1,coor.y-1};
    }

    if(case1.valid()) {
        if(board->getchess(case1) == nullptr ) {
            nextsteps.push_back(case1);
        }
    }

    if(moved == false && !board->getchess({case2})) {
        nextsteps.push_back({case2});
    }

    if (case3.valid()) {
        threaten.push_back(case3);
        if(board->getchess(case3) != nullptr) {
            if(board->getside(case3) != side) {
                nextsteps.push_back(case3);
            }
        }
    }

    if (case4.valid()) {
        threaten.push_back(case4);
        if(board->getchess(case4) != nullptr) {
            if(board->getside(case4) != side) {
                nextsteps.push_back(case4);
            }
        }
    }
}

chess* pawn::isthreatenby(coordinate c) {
    for(auto val:threaten) {
        if (c.equal(val)){
            return this;
        }
    }
    return nullptr;
}
