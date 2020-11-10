#include<iostream>
#include<sstream>
#include "chessboard.h"
#include "chess.h"
#include "pawn.h"
#include "king.h"
#include "computer.h"
using namespace std;

void movecommand(chessboard& cb, bool side, string cmd) {
    if(cmd == "resign") {
        int i = 1;
        if(side == true) { // white resign;
            throw i; // black resign
        } else {
            i = 2;
            throw i;
        }

    } else if (cmd != "move") {
        throw "Invalid command";
    }

    coordinate c1, c2;
    if(!(cin>>c1>>c2)) throw EOF;
    if(cb.getchess(c1) == nullptr) {
        throw "No chess here!";
    }

    if(side != cb.getside(c1)) {
        throw "You can not move your opponent's chess";
    }

    if(cb.legalmove(c1,c2,cb.getside(c1)) == false) {
        throw "You are placing your king in check!";
    }

    cb.move(c1,c2);
}

void human(chessboard& cb, bool side) {
    string cmd;
    while(cin>> cmd) {
        if(side == true) {
            try{
                movecommand(cb,true,cmd);
                cb.printboard();
                return;
            }catch(const char* s) {
                cb.printboard();
                cout<<s<<endl;
                continue;
            }catch(king* k) { // winner appear.
                cb.printboard();
                cout<<"Checkmate! White wins!"<<endl;
                throw k;
            }catch(int& i) { // resign
                cout<<"Black wins!"<<endl;
                throw i;
            }catch(chessboard* cb) { // stalemate
                cout<<"Stalemate!"<<endl;
                throw cb;
            }
        } else {
            try{
                movecommand(cb,false,cmd);
                cb.printboard();
                return;
            } catch(const char* s) {
                cb.printboard();
                cout<<s<<endl;
                continue;
            } catch(king* k) {
                cb.printboard();
                cout<<"Checkmate! Black wins!"<<endl;
                throw k;
            } catch(int& i) {
                cout<<"White wins!"<<endl;
                throw i;
            }catch(chessboard* cb) {
                cout<<"Stalemate!"<<endl;
                throw cb;
            }
        }
    }
    throw EOF;
}


void human_human(chessboard& cb, float& white, float& black) {
    while(1) {
        try {
            if(cb.starting == true) {
                human(cb,true);
                human(cb,false);
            } else {
                human(cb,false);
                human(cb,true);
            }
        } catch(exception e) {
            throw EOF;
        } catch (king* k) {
            cb.printboard();
            if(k->getside() == true) {
                black++;
            } else {
                white++;
            }
            return;
        } catch (int& i) {
            cb.printboard();
            if(i == 1) {
                black++;
            } else {
                white++;
            }
            return;
        }catch(chessboard* cb) {
            white += 0.5;
            black += 0.5;
            return;
        }
    }
}

void human_computer(chessboard& board,string comp, bool humanside,float& white,float& black) {
    computer c1(&board,!humanside);
    if(comp == "computer[2]") {
        c1.setlevel(2);
    } else {
        c1.setlevel(1);
    }

    board.printboard();
    try{
        if((board.starting == true && humanside == true) ||
                (board.starting == false && humanside == false)){
            while(1) {
                human(board, humanside);
                c1.move();
            }
        }else {
            while(1){
                c1.move();
                human(board, humanside);
            }
        }
    } catch(exception e) {
        throw EOF;
    } catch (king* k) {
        board.printboard();
        if(k->getside() == true) {
            black++;
        } else {
            white++;
        }
        return;
    } catch (int& i) {
        board.printboard();
        if(i == 1) {
            black++;
        } else {
            white++;
        }
        return;
    }catch(chessboard* cb) {
        white += 0.5;
        black += 0.5;
        return;
    }
}

void computer_computer(chessboard& board,string com1,string com2,float& white,float& black) {
    computer c1 = computer(&board, true);
    computer c2 = computer(&board,false);
    board.printboard();
    if(com1 == "computer[2]") {
        c1.setlevel(2);
    } else {
        c1.setlevel(1);
    }

    if(com2 == "computer[2]") {
        c2.setlevel(2);
    } else {
        c2.setlevel(1);
    }

    try{
        if(board.starting == true ){
            while(1) {
                c1.move();
                c2.move();
            }
        }else {
            while(1){
                c2.move();
                c1.move();
            }
        }
    } catch(exception e) {
        throw EOF;
    } catch (king* k) {
        board.printboard();
        if(k->getside() == true) {
            black++;
        } else {
            white++;
        }
        return;
    } catch (int& i) {
        board.printboard();
        if(i == 1) {
            black++;
        } else {
            white++;
        }
        return;
    }catch(chessboard* cb) {
        white += 0.5;
        black += 0.5;
        return;
    }
}


int main() {
    float whitescore = 0;
    float blackscore = 0;
    string s;
    chessboard board;
    board.initialize();
    cout<<"Enter \"setup\" to setup a game"<<endl;
    cout<<"Enter \"game white-player black-player \" to start a new game"<<endl;
    while(cin>>s) {
        if(s == "setup") {
            board.setup();
            continue;
        }
        if (s == "game") {
            string s1,s2;
            cin>>s1>>s2;
            if((s1 == "human") && (s2 == "human")) {
                board.printboard();
                human_human(board,whitescore,blackscore);
            } else if(s1 == "human") {
                human_computer(board,s2,true,whitescore,blackscore);
            } else if(s2 == "human")   {
                human_computer(board,s1,false,whitescore,blackscore);
            } else {
                computer_computer(board,s1,s2,whitescore,blackscore);
            }
        }
        cout<<"Enter \"setup\" to setup a game"<<endl;
        cout<<"Enter \"game white-player black-player \" to start a new game"<<endl;
    }
    cout<<"Final Score:"<<endl;
    cout<<"White: " << whitescore<<endl;
    cout<<"Black " <<blackscore<<endl;
}
