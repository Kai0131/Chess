#include "chessboard.h"
#include "chess.h"
#include "pawn.h"
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include <iostream>
using namespace std;

chessboard::chessboard(const chessboard& cb) {
    for(int i=0; i<width; i++) {
        for (int j=0; j<width;j++) {
            if(cb.getchess({i,j}) == nullptr) {
                board[j][i] = nullptr;
                continue;
            }
            char c = cb.getchesstype({i,j});
            if(c == 'K') {
                board[j][i] = new king(this,{i,j},true);
            }else if(c == 'k') {
                board[j][i] = new king(this,{i,j},false);
            }else if(c == 'P') {
                board[j][i] = new pawn(this,{i,j},true);
            }else if(c == 'p') {
                board[j][i] = new pawn(this,{i,j},false);
            }else if(c == 'Q') {
                board[j][i] = new queen(this,{i,j},true);
            }else if(c == 'q') {
                board[j][i] = new queen(this,{i,j},false);
            }else if(c == 'R') {
                board[j][i] = new rook(this,{i,j},true);
            }else if(c == 'r') {
                board[j][i] = new rook(this,{i,j},false);
            }else if(c == 'B') {
                board[j][i] = new bishop(this,{i,j},true);
            }else if(c == 'b') {
                board[j][i] = new bishop(this,{i,j},false);
            }else if(c == 'N'){
                board[j][i] = new knight(this,{i,j},true);
            }else if(c == 'n') {
                board[j][i] = new knight(this,{i,j},false);
            }
        }
    }
}

chessboard::chessboard() {
    starting = true; //  by default, white starts first.
    for(int i=0; i<width; i++) {
        for (int j=0; j<width;j++) {
            board[j][i] = nullptr;
        }
    }
}

chess* chessboard::getchess(coordinate c) const {
    if(c.valid() == false) {
        return nullptr;
    } else {
        return board[c.y][c.x];
    }
}

char chessboard::getchesstype(coordinate c)const {
    if(this->getchess(c) != nullptr){
        return board[c.y][c.x]->gettype();
    }
    return '$'; //just for safety, hope this line will never be excuted.
}

bool chessboard::getside(coordinate c) {
    return getchess(c)->getside();
}

void chessboard::move(coordinate c,coordinate target) {
    if(board[c.y][c.x] == nullptr) {
        throw "No chess here!";
    }
    board[c.y][c.x]->move(target);
    UpdateAllChess(false);

}

void chessboard::placechess(chess* chess,coordinate target) {
    board[target.y][target.x] = chess;
}

void chessboard::removechess(coordinate c) {
    board[c.y][c.x] = nullptr;
}

void chessboard::UpdateAllChess(bool testing){
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(board[j][i] != nullptr) {
                try {
                    board[j][i]->UpdateNext(testing);
                } catch (king* k) {  // a winner appears
                    throw k;
                } catch (chessboard* cb) { // stalemate
                    throw cb;
                }
            }
        }
    }
    if(testing == false) checkallsteps();
}

bool chessboard::legalmove(coordinate c, coordinate target,bool side) {
    chessboard testboard = *this;
    coordinate whiteking;
    coordinate blackking;

    testboard.placechess(testboard.getchess(c),target);
    testboard.getchess(c)->setcoor(target);
    testboard.removechess(c);
    testboard.UpdateAllChess(true);

    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(testboard.getchesstype({i,j}) == 'K') whiteking = {i,j};
            if(testboard.getchesstype({i,j}) == 'k') blackking = {i,j};
        }
    }

    bool result;
    if(side == true) {
        result =  testboard.issafe(whiteking,true);
    } else {
        result =  testboard.issafe(blackking,false);
    }
    return result;
}

bool chessboard::checkmove(coordinate c, coordinate target,bool side) {
    chessboard testboard = *this;
    coordinate whiteking;
    coordinate blackking;
    testboard.placechess(testboard.getchess(c),target);
    testboard.getchess(c)->setcoor(target);
    testboard.removechess(c);
    testboard.UpdateAllChess(true);
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(testboard.getchesstype({i,j}) == 'K') whiteking = {i,j};
            if(testboard.getchesstype({i,j}) == 'k') blackking = {i,j};
        }
    }

    bool result;
    if(side == true) {
        result = !testboard.issafe(blackking,false);
    } else {
        result = !testboard.issafe(whiteking,true);
    }
    return result;
}

void chessboard::checkallsteps() {
    bool checkblack = true;
    bool checkwhite = true;
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(board[j][i] != nullptr) {
                if(board[j][i]->getside() == true) {
                    board[j][i]->updatelegal();
                    if(board[j][i]->level1count()> 0){
                        checkwhite = false;
                        i=9;
                        break;
                    }
                }
            }
        }
    }
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(board[j][i] != nullptr) {
                if(board[j][i]->getside() == false) {
                    board[j][i]->updatelegal();
                    if(board[j][i]->level1count()> 0){
                        checkblack = false;
                        i=9;
                        break;
                    }
                }
            }
        }
    }
    if(checkblack || checkwhite) {
        throw this;
    }
}

bool chessboard::issafe(coordinate c,bool colour) {
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(board[j][i] != nullptr) {
                if(board[j][i]->getside() != colour) {
                    if(board[j][i]->isthreatenby(c) != nullptr ) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

bool chessboard::iskingsafe(coordinate c, bool colour) {
    int threatcount = 0;
    coordinate threat;
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(board[j][i] != nullptr) {
                if(board[j][i]->getside() != colour) {
                    if(board[j][i]->isthreatenby(c) != nullptr ) {
                        threatcount++;
                        threat.x=i;
                        threat.y=j;
                    }
                }
            }
        }
    }
    if (threatcount == 0) {
        return true;
    } else if(threatcount == 1 && issafe(threat,getside(threat)) == false) {;
        return true;
    } else {
        return false;
    }
}

void chessboard::initialize() {
    for(int i=0;i<width; i++) {  //pawn initialize
        coordinate a = coordinate(i,1);
        coordinate b = coordinate(i,6);
        pawn* whitepawn= new pawn(this,a,true);
        pawn* blackpawn= new pawn(this,b,false);
        board[1][i] = whitepawn;
        board[6][i] = blackpawn;
    }

    board[0][4] = new king(this,{4,0},true);
    board[7][4] = new king(this,{4,7},false);

    board[0][3] = new queen(this,{3,0},true);
    board[7][3] = new queen(this,{3,7},false);

    board[0][0] = new rook(this,{0,0},true);
    board[0][7] = new rook(this,{7,0},true);
    board[7][0] = new rook(this,{0,7},false);
    board[7][7] = new rook(this,{7,7},false);

    board[0][2] = new bishop(this,{2,0},true);
    board[0][5] = new bishop(this,{5,0},true);
    board[7][2] = new bishop(this,{2,7},false);
    board[7][5] = new bishop(this,{5,7},false);

    board[0][1] = new knight(this,{1,0},true);
    board[0][6] = new knight(this,{6,0},true);
    board[7][1] = new knight(this,{1,7},false);
    board[7][6] = new knight(this,{6,7},false);
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if(board[j][i] != nullptr) {
                allchesses.push_back(board[j][i]);
            }
        }
    }
    UpdateAllChess(false);
}

bool chessboard::checksetup() {
    for(int i=0; i<width;i++) {
        if(getchesstype({i,0}) == 'p' ||
                getchesstype({i,0}) == 'P' ||
                getchesstype({i,7}) == 'p' ||
                getchesstype({i,7}) == 'P') {
            cout<<"Pawn is on the first or last row! Please reset"<<endl;
            return false;
        }
    }//check if there is only one king for both side;

    coordinate blackking;
    coordinate whiteking;
    int blackkingcount = 0;
    int whitekingcount = 0;
    for (int i=0; i<width; i++) {
        for(int j=0; j<width; j++) {
            if (getchesstype({i,j}) == 'K'){
                whitekingcount++;
                whiteking = {i,j};
            }else if(getchesstype({i,j}) == 'k'){
                blackkingcount++;
                blackking = {i,j};
            }
        }
    }

    if(blackkingcount != 1 || whitekingcount != 1) {
        cout<<"There should be one black and one white king! Please reset" << endl;
        return false;
    }
    if(issafe(blackking,false) == false || issafe(whiteking,true) == false) {
        cout<<"king is in check! Please reset"<<endl;
        return false;
    }

    return true;
}

void chessboard::setup() {
    for(int i=0; i<width; i++) {
        for (int j=0; j<width;j++) {
            board[j][i] = nullptr;
        }
    }
    string type;
    printboard();
    while(cin>>type){
        if(type == "+") {
            char c;
            coordinate coor;
            cin>>c>>coor;
            if(c == 'K') {
                board[coor.y][coor.x] = new king(this,coor,true);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'k') {
                board[coor.y][coor.x] = new king(this,coor,false);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'P') {
                board[coor.y][coor.x] = new pawn(this,coor,true);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'p') {
                board[coor.y][coor.x] = new pawn(this,coor,false);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'Q') {
                board[coor.y][coor.x] = new queen(this,coor,true);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'q') {
                board[coor.y][coor.x] = new queen(this,coor,false);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'R') {
                board[coor.y][coor.x] = new rook(this,coor,true);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'r') {
                board[coor.y][coor.x] = new rook(this,coor,false);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'B') {
                board[coor.y][coor.x] = new bishop(this,coor,true);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'b') {
                board[coor.y][coor.x] = new bishop(this,coor,false);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'N'){
                board[coor.y][coor.x] = new knight(this,coor,true);
                allchesses.push_back(board[coor.y][coor.x]);
            }else if(c == 'n') {
                board[coor.y][coor.x] = new knight(this,coor,false);
                allchesses.push_back(board[coor.y][coor.x]);
            }
        } else if(type == "-") {
            coordinate coor;
            cin>>coor;
            removechess(coor);
        } else if(type == "=") {
            string colour;
            cin>>colour;
            if(colour == "white") {
                starting = true;
            } else if(colour == "black") {
                starting = false;
            }
        } else if(type == "done") {
            UpdateAllChess(true);
            if(checksetup() == true) {
                cout<<"Enter \"game white-player black-player \" to start the game"<<endl;
                return;
            }
        }
        printboard();
    }
}

void chessboard::printboard() {
    cout<<"  abcdefgh"<<endl<<endl;
    for(int i=width-1; i>= 0; i--) {
        cout<<i+1<<" ";
        for (int j=0; j<width;j++) {
            if (board[i][j] == nullptr) {
                if((i+j)%2 == 0) {
                    cout<<"_";
                } else {
                    cout<<" ";
                }
            } else {
                cout<< board[i][j]->gettype();
            }
        }
        cout<<endl;
    }
    cout<<endl<<"  "<<"abcdefgh"<<endl;
}


chessboard::~chessboard() {
    for(auto val: allchesses){
        delete val;
    }
}


